# declare the variable
CC=gcc
# -c = compilation -Wall = giving warning
CFLAGS=-c -Wall -g

all: main

main: main.o
	$(CC) -o main main.o

main.o: main.c
	$(CC) $(CFLAGS) main.c

clean:
	rm -rf *o main

