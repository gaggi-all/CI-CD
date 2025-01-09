FLAGS = -Wall -Wextra -Werror -std=c11

s21_grep: Makefile s21_grep.h s21_grep.c
	gcc $(FLAGS) s21_grep.c -o s21_grep

clean:
	rm -f s21_cat s21_grep

rebuild: clean s21_grep

