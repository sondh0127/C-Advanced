# +mkmake+ -- Everything after this line is automatically generated
EXECUTABLES = concord1 concord2 concord3
CFLAGS = -g -I/home/sonstephendo/Downloads/libfdr
LIB = /home/sonstephendo/Downloads/libfdr/libfdr.a
CC = gcc

all: $(EXECUTABLES)

clean:
	rm -f core *.o $(EXECUTABLES) a.out

.SUFFIXES: .c .o
.c.o:
	$(CC) $(CFLAGS) -c $*.c


concord1: concord1.o
	$(CC) $(CFLAGS) -o concord1 concord1.o $(LIB)

concord2: concord2.o
	$(CC) $(CFLAGS) -o concord2 concord2.o $(LIB)

concord3: concord3.o
	$(CC) $(CFLAGS) -o concord3 concord3.o $(LIB)
