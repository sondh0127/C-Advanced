EXECUTABLES = strsort strisort strusort strrsort1 strrsort2 nsort nsort2 nsort3
SRCS= strsort.c strisort.c strusort.c strrsort1.c strrsort2.c nsort.c nsort2.c nsort3.c

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
strsort: $(ODIR)/strsort.o
	$(CC) -o $@ $^ $(CFLAGS) $(LDIR)/$(LIBS)

strisort: $(ODIR)/strisort.o
	$(CC) -o $@ $^ $(CFLAGS) $(LDIR)/$(LIBS)

strusort: $(ODIR)/strusort.o
	$(CC) -o $@ $^ $(CFLAGS) $(LDIR)/$(LIBS)

strrsort1: $(ODIR)/strrsort1.o
	$(CC) -o $@ $^ $(CFLAGS) $(LDIR)/$(LIBS)

strrsort2: $(ODIR)/strrsort2.o
	$(CC) -o $@ $^ $(CFLAGS) $(LDIR)/$(LIBS)

nsort: $(ODIR)/nsort.o
	$(CC) -o $@ $^ $(CFLAGS) $(LDIR)/$(LIBS)

nsort2: $(ODIR)/nsort2.o
	$(CC) -o $@ $^ $(CFLAGS) $(LDIR)/$(LIBS)

nsort3: $(ODIR)/nsort3.o
	$(CC) -o $@ $^ $(CFLAGS) $(LDIR)/$(LIBS)
.PHONY: clean

clean:
	rm -f $(ODIR)/*.o core $(EXECUTABLES)
