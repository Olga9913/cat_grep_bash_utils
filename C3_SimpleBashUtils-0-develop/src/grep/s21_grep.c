// "Copyright 2022 fernando"

#include "s21_grep.h"

int s21_getopt_params(int argc, char **argv, struct Code_s *flags, char* e_buffer) {
    int res = 0, e_counter = 0;
    int index_option = 0;
    int checker = 0;
    while ((res = getopt_long(argc, argv, "e:ivcln", NULL, &index_option)) != EOF) {
    if (checker == -1) {
        break;
    } else {
    switch (res) {
        case 'e':
            if (e_counter > 0) {
              strcat(e_buffer, "|");
            }
            e_counter++;
            strcat(e_buffer, optarg);
            flags->e = true;
            break;
        case 'i':
            flags->i = true;
            break;
        case 'v':
            flags->v = true;
            break;
        case 'c':
            flags->c = true;
            break;
        case 'l':
            flags->l = true;
            break;
        case 'n':
            flags->n = true;
            break;
        default:
            printf("%s", "There is no such flag\n");
            checker = -1;
            break;
    }
    }
    }
    return checker;
}

int s21_grep(int argc, char **argv, struct Code_s *flags, char* e_buffer) {
    char *line = NULL;
    static char search_string[1024] = {0};
    int regflags = REG_EXTENDED;
    int l_counter = 0, c_counter = 0, n_counter = 0,
        match_check;
    size_t length = 0;
    regex_t regular;
    regmatch_t regmat[1];
    strcat(search_string, argv[optind]);
    if (flags->e) {
        memset(search_string, 0, 1023);
    }
    if (!flags->e) {
        optind++;
    }
    if (flags->e) {
        strcat(search_string, e_buffer);
    }
    if (flags->i) {
        regflags = REG_ICASE | REG_EXTENDED;
    }
    regcomp(&regular, search_string, regflags);
    int name_print = argc - optind;
    while (argc > optind) {
        FILE *main_file;
        main_file = fopen(argv[optind], "r");
        if (main_file != NULL) {
        while ((getline(&line, &length, main_file)) != -1) {
            n_counter++;
            match_check = regexec(&regular, line, 1, regmat, 0);
            if (match_check != REG_NOMATCH ) l_counter = 1;
            if (match_check != REG_NOMATCH && !flags->v && !flags->l) {
                if (flags->c) {
                c_counter++;
                continue;
                }
                if (name_print > 1 ) printf("%s:", argv[optind]);
                if (flags->n) printf("%d:", n_counter);
                if (strchr(line, '\n') == NULL) strcat(line, "\n");
                printf("%s", line);
            }
            if (match_check == REG_NOMATCH && flags->v && !flags->l) {
                if (flags->c) {
                c_counter++;
                continue;
                }
                if (name_print > 1 ) printf("%s:", argv[optind]);
                if (flags->n) printf("%d:", n_counter);
                if (strchr(line, '\n') == NULL) strcat(line, "\n");
                printf("%s", line);
            }
        }
        if (flags->c) {
        if (name_print > 1) printf("%s:", argv[optind]);
        if (flags->l) {
            if (c_counter > 0) {
            printf("%d\n", l_counter);
            } else {
            printf("%d\n", l_counter);
            }
        } else {
            printf("%d\n", c_counter);
        }
        c_counter = 0;
        }
        if (flags->l) {
        if (l_counter) printf("%s\n", argv[optind]);
        l_counter = 0;
        }
        fclose(main_file);
        } else {
        printf("%s%s%s", "grep: ", argv[optind], ": No such file or directory");
        }
        optind++;
        n_counter = 0;
    }
    free(line);
    regfree(&regular);
    return 0;
}

int main(int argc, char **argv) {
    Code_t code_params_t = {0};
    char e_buffer[BUFSIZ] = {0};
    if (s21_getopt_params(argc, argv, &code_params_t, e_buffer) == 0) {
        s21_grep(argc, argv, &code_params_t, e_buffer);
    }
    return 0;
}
