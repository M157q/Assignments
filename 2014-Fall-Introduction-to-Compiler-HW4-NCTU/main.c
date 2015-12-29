#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "header.h"
#include "symtab.h"
#include "codegen.h"

extern int yyparse();
extern FILE* yyin;
extern struct SymTable *symbolTable;
extern struct PType *funcReturn;
extern __BOOLEAN semError; 

char fileName[256];
char className[256];
FILE *output;


void getFileName(char* str)
{
    char *pch, *old_pch;
    pch = strtok(str, "/");
    while (pch != NULL)
    {
        old_pch = pch;
        pch = strtok(NULL, "/");
    }

    strncpy(fileName, old_pch, sizeof(fileName));
    char *lastdot = strrchr(fileName, '.');
    if (lastdot != NULL)
        *lastdot = '\0';

    #ifdef DEBUG
        printf("%s\n", fileName);
    #endif

    return;
}

int main( int argc, char **argv )
{
	if( argc == 1 )
	{
		yyin = stdin;
	}
	else if( argc == 2 )
	{
		FILE *fp = fopen( argv[1], "r" );
		if( fp == NULL ) {
				fprintf( stderr, "Open file error\n" );
				exit(-1);
		}
		yyin = fp;
	}
	else
	{
	  	fprintf( stderr, "Usage: ./parser [filename]\n" );
   		exit(0);
 	} 

	symbolTable = (struct SymTable *)malloc(sizeof(struct SymTable));
	initSymTab( symbolTable );

    getFileName(argv[1]);
    strncpy(className, fileName, sizeof(className));
    output = fopen(strncat(fileName, ".j", 2), "w");
    if (!output) {
        puts("[-] file open error");
        exit(1);
    }


	yyparse();	/* primary procedure of parser */

	if(semError == __TRUE){	
		fprintf( stdout, "\n|--------------------------------|\n" );
		fprintf( stdout, "|  There is no syntactic error!  |\n" );
		fprintf( stdout, "|--------------------------------|\n" );
	}
	else{
		fprintf( stdout, "\n|-------------------------------------------|\n" );
		fprintf( stdout, "| There is no syntactic and semantic error! |\n" );
		fprintf( stdout, "|-------------------------------------------|\n" );
	}

    fclose(output);
	exit(0);
}

