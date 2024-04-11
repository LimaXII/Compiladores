IDIR = ./
CC = gcc
CFLAGS = -I$(IDIR)

ODIR = ./
LDIR = ./

_OBJ = main.o lex.yy.o parser.tab.o 
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

all: etapa2

# Bison command for parser
$(ODIR)/parser.tab.c $(ODIR)/parser.tab.h: parser.y
	bison -d $< -o $(ODIR)/parser.tab.c

# Pattern rule for .o files
$(ODIR)/%.o: %.c
	$(CC) -c -o $@ $< $(CFLAGS)

# Flex command for scanner
$(ODIR)/lex.yy.c: scanner.l 
	flex -o $@ $^

$(ODIR)/parser.tab.o: $(ODIR)/parser.tab.c
	$(CC) -c $< -o $@ $(CFLAGS)

$(ODIR)/lex.yy.o: $(ODIR)/lex.yy.c
	$(CC) -c $< -o $@ $(CFLAGS)

# Ensure main.c depends on parser.tab.h
$(ODIR)/main.o: main.c $(ODIR)/parser.tab.h
	$(CC) -c -o $@ $< $(CFLAGS)

etapa2: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~ etapa2 $(ODIR)/lex.yy.c $(ODIR)/parser.tab.c $(ODIR)/parser.tab.h