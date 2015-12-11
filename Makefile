CC=gcc
CFLAGS=-std=c99 -Wall -Wextra tp6.c -lm -O2 -o tp6
NUM=5

all:
	$(CC) $(CFLAGS)

submit:
	$(CC) -DQ=$(NUM) -std=c99 -Wall -Wextra tp6trace.c -lm -O2 -o trace
	./trace

clean:
	rm -rf *.trace trace tp6 *.swp
