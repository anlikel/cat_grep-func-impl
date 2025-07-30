# Makefile

# Compiler and flags

CC = gcc
CFLAGS = -std=c11 -Wall -Wextra -Werror -I.

all: s21_grep

s21_grep: grep.o grep_func.o grep_args.o
	$(CC) $^ -o s21_grep

grep.o: grep.c grep.h grep_args.h
	$(CC) $(CFLAGS) -c $< -o $@

grep_func.o: grep_func.c grep.h
	$(CC) $(CFLAGS) -c $< -o $@

grep_args.o: grep_args.c grep_args.h
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: test clean rebuild

test: s21_grep
	chmod +x tests
	./tests

clean:
	rm -rf *.o *.exe s21_grep 1.txt 2.txt ./test_files

rebuild:
	rm -rf *.o **/*.o
	rm 	/*
