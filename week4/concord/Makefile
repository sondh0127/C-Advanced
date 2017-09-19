EXECUTABLES = concord1 concord2 concord3
SRCS= concord1.c concord2.c concord3.c

IDIR =../include/libfdr
CFLAGS= -g -Wall -I$(IDIR)
CC=gcc

ODIR=obj
LDIR =../lib
LIBS = libfdr.a

DEPS = fields.h jrb.h jval.h dllist.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ= $(SRCS:.c=.o)
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

all: $(EXECUTABLES)

$(ODIR)/%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

concord1: $(ODIR)/concord1.o
	$(CC) -o $@ $^ $(CFLAGS) $(LDIR)/$(LIBS)

concord2: $(ODIR)/concord2.o
	$(CC) -o $@ $^ $(CFLAGS) $(LDIR)/$(LIBS)

concord3: $(ODIR)/concord3.o
	$(CC) -o $@ $^ $(CFLAGS) $(LDIR)/$(LIBS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o core $(EXECUTABLES)
