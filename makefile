IDIR = ./include
CC = gcc
CFLAGS = -I$(IDIR)

ODIR = ./src
HDIR = ./include
LDIR = ./
TESTDIR = ./test

_OBJ = main.o lex.yy.o parser.tab.o valor_lexico.o ast_tree.o table.o asm.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

all: etapa6

# Comando do bison para gerar o parser.tab.c
$(ODIR)/parser.tab.c $(HDIR)/parser.tab.h: $(ODIR)/parser.y
	bison -d $< -o $(ODIR)/parser.tab.c

# Regra para arquivos .o
$(ODIR)/%.o: $(ODIR)/%.c
	$(CC) -c -o $@ $< $(CFLAGS)

# Comando flex para o scanner.l
$(ODIR)/lex.yy.c: $(ODIR)/scanner.l 
	flex -o $@ $^

$(ODIR)/parser.tab.o: $(ODIR)/parser.tab.c
	$(CC) -c $< -o $@ $(CFLAGS)

$(ODIR)/lex.yy.o: $(ODIR)/lex.yy.c
	$(CC) -c $< -o $@ $(CFLAGS)

# Faz questão de que o arquivo parser.tab.h já esteja compilado antes do main.c.
$(ODIR)/main.o: $(ODIR)/main.c $(HDIR)/parser.tab.h
	$(CC) -c -o $@ $< $(CFLAGS)

# Regra para compilar table.o
$(ODIR)/table.o: $(ODIR)/table.c $(HDIR)/table.h
	$(CC) -c -o $@ $< $(CFLAGS)

# Regra para compilar asm.o
$(ODIR)/asm.o: $(ODIR)/asm.c $(HDIR)/asm.h
	$(CC) -c -o $@ $< $(CFLAGS)

etapa6: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

.PHONY: clean

# Remove todos os arquivos necessários.
clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~ etapa6 $(ODIR)/lex.yy.c $(ODIR)/parser.tab.c $(ODIR)/parser.tab.h