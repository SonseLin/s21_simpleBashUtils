cc = gcc -Wall -Werror -Wextra
test_input = "s21_cat.c"
out = s21_cat

all: rebuild

s21_cat:
	$(cc) -o $(out) s21_cat.c cat_worker.c cat_processing.c

d:	rebuild
	valgrind --tool=memcheck --leak-check=yes ./$(out) $(test_input)

n:	rebuild
	valgrind --tool=memcheck --leak-check=yes ./$(out) -n $(test_input)

b: rebuild
	valgrind --tool=memcheck --leak-check=yes ./$(out) -b $(test_input)

e: rebuild
	valgrind --tool=memcheck --leak-check=yes ./$(out) -e $(test_input)

s: rebuild
	valgrind --tool=memcheck --leak-check=yes ./$(out) -s $(test_input)

t: rebuild
	valgrind --tool=memcheck --leak-check=yes ./$(out) -t $(test_input)

clean:
	rm -f $(out)

rebuild: clean s21_cat
