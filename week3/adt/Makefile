#declare the variable
CC=gcc
# -c = compilation -Wall = giving warning -g  =gdb Debugging
CFLAGS=-c -Wall -g

all: main

main: main.o adt.o
	$(CC) -o main main.o adt.o

main.o: main.c
	$(CC) $(CFLAGS) main.c

adt.o: adt.c
	$(CC) $(CFLAGS) adt.c

clean:
	rm -rf *o main

