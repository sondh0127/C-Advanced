EXECUTABLES = phonebook
SRCS= phonebook.c

IDIR =../include
CFLAGS= -g -Wall -I$(IDIR)
CC=gcc

ODIR=obj
LDIR =../lib
LIBS = libfdr.a

DEPS = fields.h jrb.h jval.h dllist.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ= $(SRCS:.c=.o)
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))
#action
all: $(EXECUTABLES)

$(ODIR)/%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)
#change here
phonebook: $(ODIR)/phonebook.o
	$(CC) -o $@ $^ $(CFLAGS) $(LDIR)/$(LIBS)
.PHONY: clean

clean:
	rm -f $(ODIR)/*.o core $(EXECUTABLES)
