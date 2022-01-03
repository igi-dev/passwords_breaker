IDIR =../include
CC=gcc
CFLAGS=-I$(IDIR) -lcrypto -lssl -g

ODIR=obj
LDIR =../lib

LIBS=-lm -lcrypto -lpthread

_DEPS = StringConversion.h Producer.h Utilities.h Consumer.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = main.o StringConversion.o Producer.o Utilities.o Consumer.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

$(ODIR)/%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

icebreaker: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

.PHONY: clean check

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~

check:
	valgrind --leak-check=full --show-leak-kinds=all ./icebreaker