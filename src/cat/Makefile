# Makefile

# Compiler and flags

CC = gcc
CFLAGS = -std=c11 -Wall -Wextra -Werror -I.

all: s21_cat

s21_cat: cat.o cat_func.o cat_args.o
	$(CC) $^ -o s21_cat

cat.o: cat.c cat.h cat_args.h
	$(CC) $(CFLAGS) -c $< -o $@

cat_func.o: cat_func.c cat.h
	$(CC) $(CFLAGS) -c $< -o $@

cat_args.o: cat_args.c cat_args.h
	$(CC) $(CFLAGS) -c $< -o $@
	
.PHONY: test clean rebuild

test: s21_cat
	chmod +x tests
	./tests

clean:
	rm -rf *.o *.exe s21_cat 1.txt 2.txt ./test_files

rebuild:
	rm -rf *.o **/*.o
	rm 	/*
