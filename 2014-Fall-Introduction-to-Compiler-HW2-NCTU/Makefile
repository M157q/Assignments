# Makefile for parser and scanner
RM = rm -f
CC = gcc
CFLAGS = -ly -ll
LEX = lex
YACC = yacc
YACCFLAGS = -d -v

LEX_SOURCE = lex.l
SCANNER_SOURCE = lex.yy.c
YACC_SOURCE = parser.y
PARSER_SOURCE = y.tab.c
PARSER_HEADER = y.tab.h
PARSER_TABLE = y.output
PARSER_NAME = parser

CORRECT_TEST_FILES = testcases/correct/*
WRONG_TEST_FILES = testcases/wrong/*

all: parser

parser: scanner yacc
	$(CC) -o $(PARSER_NAME) $(SCANNER_SOURCE) $(PARSER_SOURCE) $(CFLAGS)

scanner:
	$(LEX) $(LEX_SOURCE)

yacc:
	$(YACC) $(YACCFLAGS) $(YACC_SOURCE)

test:
	./$(PARSER_NAME) $(CORRECT_TEST_FILES)
	./$(PARSER_NAME) $(WRONG_TEST_FILES)

clean:
	$(RM) $(SCANNER_SOURCE) $(PARSER_SOURCE) $(PARSER_NAME) $(PARSER_HEADER) $(PARSER_TABLE)
