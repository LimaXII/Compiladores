IDIR=./
CC=gcc
CFLAGS=-I$(IDIR)

ODIR=./
LDIR=./

_DEPS= tokens.h
DEPS=$(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ= main.o lex.yy.o
OBJ=$(patsubst %,$(ODIR)/%,$(_OBJ))

$(ODIR)/%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

all: scanner etapa1

scanner:scanner.l 
	flex scanner.l
	gcc -c $(ODIR)/lex.yy.c -o $(ODIR)/lex.yy.o

etapa1: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

.PHONY:clean

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~ etapa1 $(ODIR)/lex.yy.c
