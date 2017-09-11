#declare the variable
CC=gcc
# -c = compilation -Wall = giving warning
CFLAGS=-c -Wall -g

all: main

main: main.o sort.o
	$(CC) -o main main.o sort.o

main.o: main.c
	$(CC) $(CFLAGS) main.c

sort.o: sort.c
	$(CC) $(CFLAGS) sort.c

clean:
	rm -rf *o main
