#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#ifndef s21_cat_h
#define s21_cat_h

#define N 80

struct flags {
  int pN;
  int pB;
  int pS;
  int pV;
  int pe;
  int pt;
  int pE;
  int pT;
};

void output(FILE *file, struct flags *flag_check);
void getoptions(int argc, char *argv[], struct flags *flag_check,
                const struct option long_options[]);
int v_function(int c);

#endif