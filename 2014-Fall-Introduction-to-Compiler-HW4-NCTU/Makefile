TARGET = parser
OBJECT = lex.yy.c y.tab.c y.tab.o lex.yy.o y.output parser y.tab.h main.o semcheck.o symtab.o codegen.o *.j
CC = gcc -g
LEX = flex
YACC = yacc -v
YACCFLAG = -d
LIBS = -lfl

all: $(TARGET)

parser: y.tab.o lex.yy.o main.o semcheck.o symtab.o codegen.o
	$(CC) -o $(TARGET) y.tab.o lex.yy.o main.o semcheck.o symtab.o codegen.o $(LIBS)

y.tab.o: y.tab.c
	$(CC) -c y.tab.c

y.tab.c: parser.y
	$(YACC) $(YACCFLAG) parser.y

lex.yy.o: lex.yy.c
	$(CC) -c lex.yy.c

lex.yy.c: lex.l
	$(LEX) lex.l

main.o: main.c
	$(CC) -c main.c

semcheck.o: semcheck.c
	$(CC) -c semcheck.c

symtab.o: symtab.c
	$(CC) -c symtab.c

codegen.o: codegen.c
	$(CC) -c codegen.c

clean:
	rm -f $(TARGET) $(OBJECT)

vim:
	vim -p main.c parser.y codegen.c semcheck.c symtab.c
