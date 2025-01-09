#include "s21_grep.h"

int main(int argc, char* argv[]) {
  arguments arg = parser(argc, argv);
  output(arg, argc, argv);
  return 0;
}

arguments parser(int argc, char* argv[]) {
  arguments arg = {0};
  int opt = 0;
  while ((opt = getopt(argc, argv, "e:ivclnhsf:o")) != -1) {
    switch (opt) {
      case 'e':
        arg.e = 1;
        add_pattern(&arg, optarg);
        break;
      case 'i':
        arg.i = REG_ICASE;
        break;
      case 'v':
        arg.v = 1;
        break;
      case 'c':
        arg.c = 1;
        break;
      case 'l':
        arg.l = 1;
        break;
      case 'n':
        arg.n = 1;
        break;
      case 'h':
        arg.h = 1;
        break;
      case 'f':
        arg.f = 1;
        add_reg_from_file(&arg, optarg);
        break;
      case 'o':
        arg.o = 1;
        break;
      case 's':
        arg.s = 1;
        break;
    }
  }
  if (arg.len_pattern == 0) {
    add_pattern(&arg, argv[optind]);
    optind++;
  }
  if (argc - optind == 1) {
    arg.h = 1;
  }
  return arg;
}

void processFile(arguments arg, char* path, regex_t* reg) {
  FILE* f = fopen(path, "r");
  if (f == NULL) {
    if (!arg.s) perror(path);
    exit(1);
  }
  char* line = NULL;
  size_t memlen = 0;
  int read = 0;
  int line_count = 1;
  int c = 0;
  read = getline(&line, &memlen, f);
  while (read != -1) {
    int result = regexec(reg, line, 0, NULL, 0);
    if ((result == 0 && !arg.v) || (arg.v && result != 0)) {
      if (!arg.c && !arg.l) {
        if (!arg.h) printf("%s:", path);
        if (arg.n) printf("%d:", line_count);
        if (arg.o && !arg.v) {
          output_match(reg, line);
        } else {
          output_line(line, read);
        }
      }
      c++;
    }
    read = getline(&line, &memlen, f);
    line_count++;
  }
  combo_check(arg, path, c);
  free(line);
  fclose(f);
}

void output_line(char* line, int n) {
  for (int i = 0; i < n; i++) {
    putchar(line[i]);
  }
  if (line[n - 1] != '\n') {
    putchar('\n');
  }
}

void add_pattern(arguments* arg, char* pattern) {
  if (arg->len_pattern != 0) {
    strcat(arg->pattern + arg->len_pattern, "|");
    arg->len_pattern++;
  }
  arg->len_pattern += sprintf(arg->pattern + arg->len_pattern, "(%s)", pattern);
}

void add_reg_from_file(arguments* arg, char* path) {
  FILE* f = fopen(path, "r");
  if (f == NULL) {
    perror(path);
    exit(1);
  }
  char* line = NULL;
  size_t memlen = 0;
  int read = 0;
  read = getline(&line, &memlen, f);
  while (read != -1) {
    if (line[read - 1] == '\n') line[read - 1] = '\0';
    add_pattern(arg, line);
    read = getline(&line, &memlen, f);
  }
  free(line);
  fclose(f);
}

void output_match(regex_t* reg, char* line) {
  regmatch_t math;
  int offset = 0;
  while (1) {
    int result = regexec(reg, line + offset, 1, &math, 0);
    if (result != 0) {
      break;
    }
    for (int i = math.rm_so; i < math.rm_eo; i++) {
      putchar(line[i]);
    }
    putchar('\n');
    offset += math.rm_eo;
  }
}

void output(arguments arg, int argc, char** argv) {
  regex_t reg;
  int error = regcomp(&reg, arg.pattern, REG_EXTENDED | arg.i);
  if (error != 0) perror("Error");
  for (int i = optind; i < argc; i++) {
    processFile(arg, argv[i], &reg);
  }
  regfree(&reg);
}

void combo_check(arguments arg, char* path, int c) {
  if (arg.c && !arg.l) {
    if (!arg.h) {
      printf("%s:", path);
    }
    printf("%d\n", c);
  }
  if (arg.v) {
    if (arg.l && arg.c) {
      if (!arg.h) {
        printf("%s:1\n", path);
      } else
        printf("1\n");
    }
  }
  if (arg.l && arg.c && !arg.v) {
    if (!arg.h) printf("%s:", path);
    if (c < 1) printf("0\n");
    if (c > 0) printf("1\n");
  }
  if (arg.l && c > 0) {
    printf("%s\n", path);
  }
}