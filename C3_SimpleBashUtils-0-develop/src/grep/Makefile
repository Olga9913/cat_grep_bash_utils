FLAGS = -std=c11 -Wall -Wextra -Werror

all: s21_grep

clean: 
	rm -f s21_grep s21_grep.o log.txt

s21_grep: s21_grep.o
	gcc $(FLAGS) s21_grep.o -o s21_grep

s21_grep.o:
	gcc $(FLAGS) -c s21_grep.c -o s21_grep.o