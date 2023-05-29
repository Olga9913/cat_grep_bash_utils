FLAGS = -std=c11 -Wall -Wextra -Werror

all: s21_cat

clean: 
	rm -f s21_cat s21_cat.o log.txt

s21_grep: s21_cat.o
	gcc $(FLAGS) s21_cat.o -o s21_cat
	
s21_grep.o:
	gcc $(FLAGS) -c s21_cat.c -o s21_cat.o