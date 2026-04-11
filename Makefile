CC = gcc
CFLAGS = -Wall

all: g18_cp

g18_cp: src/g18_cp.c
	$(CC) $(CFLAGS) src/g18_cp.c -o bin/g18_cp

clean:
	rm -f bin/*

