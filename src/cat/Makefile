CC= gcc -std=c11
CFLAGS= -Wall -Wextra -Werror
CAT= s21_cat.c s21_cat.h


s21_cat:
	$(CC) $(CFLAGS) $(CAT) -o s21_cat

clean:
	rm -rf s21_cat
	rm -rf *.a *.out *.o *.dSYM
rebuild: clean s21_cat	