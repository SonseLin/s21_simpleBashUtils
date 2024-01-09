cc = gcc -Wall -Werror -Wextra

s21_grep: 
	$(cc) -o s21_grep s21_grep.c grep_worker.c

all: rebuild

clean:
	rm -f s21_grep

rebuild: clean s21_grep
