IDIR=./
CC=gcc
CFLAGS=-I$(IDIR)

ODIR=./
LDIR=./

_DEPS= tokens.h
DEPS=$(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ= main.o lex.yy.o parser.tab.o
OBJ=$(patsubst %,$(ODIR)/%,$(_OBJ))

$(ODIR)/%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

all: bison scanner etapa2

bison: parser.y
	bison -d parser.y
	gcc -c $(ODIR)/parser.tab.c

scanner: scanner.l 
	flex scanner.l
	gcc -c $(ODIR)/lex.yy.c -o $(ODIR)/lex.yy.o

etapa2: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

.PHONY:clean

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~ etapa2 $(ODIR)/lex.yy.c
