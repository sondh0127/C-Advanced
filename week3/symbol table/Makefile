#declare the variable
CC=gcc
# -c = compilation -Wall = giving warning -g  =gdb Debugging
CFLAGS=-c -Wall -g

all: main

main: main.o symtable.o
	$(CC) -o main main.o symtable.o

main.o: main.c
	$(CC) $(CFLAGS) main.c

symtable.o: symtable.c
	$(CC) $(CFLAGS) symtable.c

clean:
	rm -rf *o main

