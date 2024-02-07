CC=gcc
COMLFAGS=-Wall -Werror -Wextra -std=c11 -pedantic -g
FILES=$(wildcard s21_matrix.c s21_matrix_func.c s21_matrix_arithmetics.c)
GCOVFLAGS =--coverage

TESTFLAGS2 = -lcheck -lm -lpthread -lrt -lsubunit -g

ifeq ($(shell uname), Linux)
OPEN_CMD = xdg-open
  TFLAGS += -lm -lptread -lsubunit -lcheck
else
OPEN_CMD = open
 TFLAGS += -lcheck 
endif

.PHONY: all clean s21_matrix.a format test gcov_report

all: s21_matrix.a test gcov_report 

s21_matrix.a:
	$(CC) $(COMLFAGS) -c $(FILES)
	ar rcs s21_matrix.a *.o
	-rm -rf *.o
 
test: s21_matrix.a
	@$(CC) $(COMLFAGS) -o test $(FILES) s21_test_matrix.c $(TFLAGS)
	./test

gcov_report: clean

	@${CC} $(GCOVFLAGS) $(FILES) s21_test_matrix.c $(TFLAGS) -o test_report $(LIBS)
	@./test_report
	@lcov -t test_report -o test.info -c -d .
	@genhtml -o report test.info
	@open ./report/index-sort-f.html


clean:
	rm -rf test *.gcda *.gcno *.o *.info *.a *.h.gch tests/*.gcno report 
	rm -rf s21_test_matrix.dSYM s21_test_matrix
	rm -rf tests/*.h.gch 

style:
	clang-format -n -style=google *.h *.c $(ALL_FUNC) $(SOURCE_TESTS_FUNC)
	@rm -rf .clang-format

style_repair:
	@cp ../materials/linters/.clang-format ../src  
	@clang-format -i -style=google *.h *.c $(ALL_FUNC) $(SOURCE_TESTS_FUNC)

leaks:
	leaks -atExit -- ./s21_test_matrix

install_brew:
	cd ~
	curl -fsSL https://rawgit.com/kube/42homebrew/master/install.sh | zsh
	brew install lcov
