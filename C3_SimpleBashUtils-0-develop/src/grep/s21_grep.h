// "Copyright 2022 <fernando>"
#ifndef SRC_GREP_S21_GREP_H_
#define SRC_GREP_S21_GREP_H_
#define  _GNU_SOURCE
#include <stdio.h>
#include <getopt.h>
#include <stdbool.h>
#include <stdlib.h>
#include <regex.h>
#include <string.h>

struct Code_s {
    bool e;
    bool i;
    bool v;
    bool c;
    bool l;
    bool n;
};

typedef struct Code_s Code_t;

int s21_getopt_params(int argc, char **argv, struct Code_s *flags, char* e_buffer);
int s21_grep(int argc, char **argv, struct Code_s *flags, char* e_buffer);

#endif  //  SRC_GREP_S21_GREP_H_
