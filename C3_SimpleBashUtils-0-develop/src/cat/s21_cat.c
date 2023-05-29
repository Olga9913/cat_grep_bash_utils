// "Copyright 2022 fernando"

#include "./s21_cat.h"

int s21_getopt_flags(int argc, char **argv, struct Code_s *flags);
int cat(int argc, char **argv, struct Code_s *flags);

int main(int argc, char **argv) {
    Code_t code_params_t = {0};
    if (s21_getopt_flags(argc, argv, &code_params_t) == 0) {
        cat(argc, argv, &code_params_t);
    }
    return 0;
}

int s21_getopt_flags(int argc, char **argv, struct Code_s *flags) {
    int checker = 0;
    int res, index_option = 0;
    while ((res = getopt_long(argc, argv, "bnsvet", long_flags, &index_option)) != -1) {
    if (checker == -1) {
        break;
    } else {
        switch (res) {
        case 'b':
            flags->b = true;
            break;
        case 'e':
            flags->e = true;
            flags->v = true;
            break;
        case 'n':
            flags->n = true;
            break;
        case 's':
            flags->s = true;
            break;
        case 't':
            flags->t = true;
            flags->v = true;
            break;
        case 'v':
            flags->v = true;
            break;
        default:
            printf("usage: cat [-benstuv] [file ...]\n");
            checker = -1;
            break;
    }
    }
    }
    return checker;
}

int cat(int argc, char **argv, struct Code_s *flags) {
    int sym;
    int counter = 0, new_line = 0, previous_symbol = 1, number_of_flags = 0,
      no_print = 1;
    if (flags->b) {
        flags->n = 0;
    }
    while (*argv[1] == '-') {
    number_of_flags++;
    argv++;
    }
    argv++;
    argc--;
    while (argc > number_of_flags) {
        FILE *my_file = fopen(*argv, "r");
        if (NULL != my_file) {
            while ((sym = getc(my_file)) != EOF) {
                if (flags->s) {
                    if (sym == '\n') {
                        previous_symbol++;
                        if (previous_symbol == 3) {
                            previous_symbol--;
                            continue;
                        }
                    } else {
                        previous_symbol = 0;
                    }
                }
                if (flags->b) {
                    if (sym != '\n') {
                        if (new_line == 0) {
                            printf("%6d\t", ++counter);
                            new_line = 1;
                        }
                    } else {
                        new_line = 0;
                    }
                }
                if (flags->n) {
                    if (new_line == 0) {
                        printf("%6d\t", ++counter);
                        new_line = 1;
                    }
                if (sym == '\n') {
                new_line = 0;
                }
                }
                if (flags->e) {
                    if (sym == '\n') {
                    printf("%c", '$');
                    }
                }
                if (flags->t) {
                    if (sym == '\t') {
                        printf("^I");
                        no_print = 0;
                    }
                }
                if (flags->v) {
                    if (sym <= 31 && sym != 9 && sym != 10) {
                        printf("^%c", sym + 64);
                        no_print = 0;
                    }
                    if (sym > 126) {
                        printf("^%c", sym - 64);
                        no_print = 0;
                    }
                }
                if (no_print == true) {
                printf("%c", sym);
                }
                no_print = 1;
            }
            argc--;
            argv++;
            counter = 0;
            previous_symbol = 1;
            fclose(my_file);
        } else {
            printf("\n%s%s%s", "cat: ", *argv, " No such file or directory");
            argc--;
            argv++;
        }
    }
    return 0;
}
