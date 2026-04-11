CC=gcc
CFLAGS=-Wall

all: g18-wc shell

g18-wc:
	$(CC) $(CFLAGS) src/utils/g18-wc.c -o bin/g18-wc

shell:
	$(CC) $(CFLAGS) src/shell/main_shell.c -o bin/g18-shell

clean:
	rm -f bin/*
