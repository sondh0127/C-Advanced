#declare the variable
CC=g++
# -c = compilation -Wall = giving warning
CFLAGS=-c -Wall

all: main

main: main.o func.o
	$(CC) -o main main.o func.o

main.o:
func.o:
	$(CC) $(CFLAGS) func.cpp

clean:
	rm -rf *o main
