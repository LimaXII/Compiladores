IDIR = ./
CC = gcc
CFLAGS = -I$(IDIR)

ODIR = ./
LDIR = ./

_OBJ = main.o lex.yy.o parser.tab.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

all: etapa2

$(ODIR)/%.o: %.c
	$(CC) -c -o $@ $< $(CFLAGS)

$(ODIR)/parser.tab.c: parser.y
	bison -d $^ -o $@

$(ODIR)/lex.yy.c: scanner.l
	flex -o $@ $^

$(ODIR)/parser.tab.o: $(ODIR)/parser.tab.c
	$(CC) -c $^ -o $@ $(CFLAGS)

$(ODIR)/lex.yy.o:$(ODIR)/lex.yy.c
	$(CC) -c $^ -o $@ $(CFLAGS)
         
etapa2: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~ etapa2 $(ODIR)/lex.yy.c