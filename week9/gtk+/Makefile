MKDIR_P = mkdir -p
# change application name here (executable output name)
TARGET=main

# compiler
CC=gcc
# compiling flags here
CFLAGS= -g -Wall

# define any directories containing header file other then /usr/include
INCLUDES = -I../../lib/include

LFLAGS = -lfdr -lbt -lm
LIBS = -L../../lib/implementation

GTKLIB =`pkg-config --cflags --libs gtk+-3.0`
LDFLAGS= $(GTKLIB) -export-dynamic

SRCS = $(wildcard *.c)
ODIR = obj
_OBJS = $(SRCS:.c=.o)
OBJS = $(patsubst %,$(ODIR)/%,$(_OBJS))

.PHONY: clean
#action
all: $(TARGET)

# This uses Suffix Replacement within a macro:
#   $@ = left-part of ":" ( == $(TARGET))
# 
$(ODIR)/%.o: %.c $(DEPS)
	@mkdir -p obj
	$(CC) $(CFLAGS) $(GTKLIB) $(INCLUDES) -c $< -o $@
	@echo "Compiled "$<" successfully!"

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ $^ $(LIBS) $(LFLAGS) $(LDFLAGS)
	@echo "Linking complete!"
	
clean:
	rm -f core $(ODIR)/*.o *~ $(TARGET)
	@echo "Cleanup complete!"
