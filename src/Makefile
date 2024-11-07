CC = g++
CFLAGS = -Wall -Wextra -Werror -std=c++17 --coverage
LDFLAGS = -lgtest -lgtest_main -pthread --coverage
INFO= coverage.info
FILES = tests/*.cpp
test : clean
	$(CC) -Wall -Wextra -Werror -std=c++17 $(FILES) -lgtest -lgtest_main -pthread -o test
gcov_report : clean
	$(CC) $(CFLAGS) -o gcov_report ./$(FILES) $(LDFLAGS)
	./gcov_report
	lcov -t "gcov_report" -o $(INFO) -c -d . --no-external
	genhtml -o coverage $(INFO)
	open coverage/index.html
clean:
	rm -rf a.out test gcov_report *.gcda *.gcno coverage coverage.info