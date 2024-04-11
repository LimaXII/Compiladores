IDIR = ./
CC = gcc
CFLAGS = -I$(IDIR)

ODIR = ./
LDIR = ./

_OBJ = main.o lex.yy.o parser.tab.o 
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

all: etapa2

# Comando do bison para gerar o parser.tab.c
$(ODIR)/parser.tab.c $(ODIR)/parser.tab.h: parser.y
	bison -d $< -o $(ODIR)/parser.tab.c

# Regra para arquivos .o
$(ODIR)/%.o: %.c
	$(CC) -c -o $@ $< $(CFLAGS)

# Comando flex para o scanner.l
$(ODIR)/lex.yy.c: scanner.l 
	flex -o $@ $^

$(ODIR)/parser.tab.o: $(ODIR)/parser.tab.c
	$(CC) -c $< -o $@ $(CFLAGS)

$(ODIR)/lex.yy.o: $(ODIR)/lex.yy.c
	$(CC) -c $< -o $@ $(CFLAGS)

# Faz questão de que o arquivo paser.tab.h já esteja compilcado antes do main.c.
$(ODIR)/main.o: main.c $(ODIR)/parser.tab.h
	$(CC) -c -o $@ $< $(CFLAGS)

etapa2: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

.PHONY: clean

# Remove todos os arquivos necessários.
clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~ etapa2 $(ODIR)/lex.yy.c $(ODIR)/parser.tab.c $(ODIR)/parser.tab.h