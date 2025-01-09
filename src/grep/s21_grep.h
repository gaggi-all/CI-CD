#include <getopt.h>
#include <regex.h>
#include <stdbool.h>
#define _GNU_SOURCE
#include <stdio.h>
ssize_t getline(char **lineptr, size_t *n, FILE *stream);
#include <stdlib.h>
#include <string.h>

#ifndef s21_grep_h
#define s21_grep_h

typedef struct arguments {
  int e, i, v, c, l, n, h, s, f, o;
  char pattern[1024];
  int len_pattern;
} arguments;

arguments parser(int argc, char *argv[]);
void output_line(char *line, int n);
void add_pattern(arguments *arg, char *pattern);
void add_reg_from_file(arguments *arg, char *path);
void output_match(regex_t *reg, char *line);
void processFile(arguments arg, char *path, regex_t *reg);
void output(arguments arg, int argc, char **argv);
void combo_check(arguments arg, char *path, int c);

#endif