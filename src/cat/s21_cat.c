#include "s21_cat.h"

int main(int argc, char *argv[]) {
  struct flags flag_check = {0, 0, 0, 0, 0, 0, 0, 0};
  const struct option long_options[] = {{"number-nonblank", 0, NULL, 'b'},
                                        {"number", 0, NULL, 'n'},
                                        {"squeeze-blank", 0, NULL, 's'},
                                        {NULL, 0, NULL, 0}};
  for (int i = 1; i < argc; i++) {
    if (argv[i][0] != '-') {
      char *fileName = argv[i];
      FILE *file = fopen(fileName, "r");
      if (file != NULL) {
        getoptions(argc, argv, &flag_check, long_options);
        output(file, &flag_check);
        fclose(file);
      } else {
        fprintf(stderr, "cat: %s: No such file or directory\n", fileName);
      }
    }
  }
  return 0;
}

void getoptions(int argc, char *argv[], struct flags *flag_check,
                const struct option long_options[]) {
  int rez = 0;
  while ((rez = getopt_long(argc, argv, "bnstveET", long_options, NULL)) !=
         -1) {
    switch (rez) {
      case 'n':
        flag_check->pN = 1;
        break;
      case 'b':
        flag_check->pB = 1;
        break;
      case 's':
        flag_check->pS = 1;
        break;
      case 'v':
        flag_check->pV = 1;
        break;
      case 'e':
        flag_check->pe = 1;
        flag_check->pV = 1;
        break;
      case 't':
        flag_check->pt = 1;
        flag_check->pV = 1;
        break;
      case 'E':
        flag_check->pE = 1;
        break;
      case 'T':
        flag_check->pT = 1;
        break;
      case '?':
        perror("ERROR");
        exit(1);
        break;
      default:
        break;
    }
    if (flag_check->pB && flag_check->pN) {
      flag_check->pN = 0;
    }
  }
}

void output(FILE *file, struct flags *flag_check) {
  int c = 0;
  int line_number = 1;
  int nonEmptyLine_number = 1;
  char buf = '\n';
  char prev_buf = 'a';
  while ((c = fgetc(file)) != EOF) {
    if (flag_check->pS) {
      if (c == '\n') {
        if ((prev_buf == '\n' && buf == '\n')) {
          prev_buf = buf;
          buf = c;
          continue;
        }
      }
    }
    if (flag_check->pB && (c != '\n' && buf == '\n')) {
      printf("%6d\t", nonEmptyLine_number);
      nonEmptyLine_number++;
    }
    if (flag_check->pN && buf == '\n') {
      printf("%6d\t", line_number);
      line_number++;
    }
    if (flag_check->pe || flag_check->pE) {
      if (c == 10) printf("$\n");
    }
    if (flag_check->pt || flag_check->pT) {
      if (c == 9) printf("^I");
    }
    if ((flag_check->pe && c != 10) || (flag_check->pt && c != 9) ||
        (flag_check->pV)) {
      c = v_function(c);
    }
    if (!(((flag_check->pT || flag_check->pt) && c == 9) ||
          ((flag_check->pE || flag_check->pe) && c == 10))) {
      printf("%c", c);
    }
    prev_buf = buf;
    buf = c;
  }
}

int v_function(int c) {
  if (c < 32 && c != 9 && c != 10) {
    printf("^");
    c = c + 64;
  } else if (c > 127 && c < 160) {
    printf("M-^");
    c = c - 64;
  } else if (c == 127) {
    printf("^");
    c = c - 64;
  }
  return c;
}

// hello