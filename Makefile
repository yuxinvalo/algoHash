CC=gcc
CFLAGS=-std=c99 -Wall -Wextra tp6.c -lm -O2 -g -o tp6
NUM=8

all:
	$(CC) $(CFLAGS)

submit:
	$(CC) -DQ=$(NUM) -std=c99 -Wall -Wextra tp6trace.c -lm -O2 -o trace
	./trace

clean:
	rm -rf *.trace trace tp6 .*.swp
