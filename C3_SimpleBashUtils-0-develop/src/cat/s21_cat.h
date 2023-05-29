// "Copyright 2022 fernando"

#ifndef SRC_CAT_S21_CAT_H_
#define SRC_CAT_S21_CAT_H_

#include <stdio.h>
#include <getopt.h>
#include <stdbool.h>
#include <unistd.h>
#include <stdlib.h>

static struct option long_flags[] = {
        {"number-nonblank", 0, 0, 'b'},
        {"number", 0, 0, 'n'},
        {"squeeze-blank", 0, 0, 's'},
        {NULL, 0, NULL, 0},
};

struct Code_s {
    bool b;
    bool e;
    bool n;
    bool s;
    bool t;
    bool v;
};

typedef struct Code_s Code_t;

int s21_getopt_flags(int argc, char **argv, struct Code_s *flags);
int s21_cat(int argc, char **argv, struct Code_s *flags);

#endif  //  SRC_CAT_S21_CAT_H_
