IDIR=./include
CC=gcc
UNAME_S := $(shell uname -s)

ifeq ($(UNAME_S), Linux)
	CFLAGS=-lbsd -lm -I$(IDIR)
else
	CFLAGS=-I$(IDIR)
endif

ODIR=obj
SRCDIR =./src

_DEPS = shamir.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = shamir.o 
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

$(ODIR)/%.o: src/%.c $(DEPS) objdir
	$(CC) -c -o $@ $< $(CFLAGS)

shamir: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

objdir:
	mkdir -p obj

.PHONY: clean

clean:
	rm -rf $(ODIR) *~ shamir $(IDIR)/*~ 
