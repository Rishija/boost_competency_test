CC = g++
CFLAGS = -std=c++14

all: generate tree test

generate:
	cd generate_cases; $(CC) $(CFLAGS) generate_testcases.cpp -o generate; ./generate

tree:
	$(CC) $(CFLAGS) main.cpp -o tree

test:
	 $(CC) $(CFLAGS) test.cpp -o test -lboost_unit_test_framework-mt

clean:
	find . -type f -name '*.o' -delete
	find . -type f -name '*.out' -delete
	find . -type f -name '*.txt' -delete
	rm test tree ./generate_cases/generate