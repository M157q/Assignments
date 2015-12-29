%{
#include <stdio.h>
#include <stdlib.h>

extern int linenum;             /* declared in lex.l */
extern FILE *yyin;              /* declared by lex */
extern char *yytext;            /* declared by lex */
extern char buf[256];           /* declared in lex.l */

int Opt_p = 1;
#define PTRACE(t) {if(Opt_p) printf("<%s>\n",#t);}
%}

%token INT DOUBLE FLOAT STRING BOOL                  /* data type  */
%token WHILE DO IF ELSE TRUE FALSE FOR PRINT         /* keywords   */
%token READ BOOLEAN VOID CONTINUE BREAK RETURN       /* keywords   */
%token SEMICOLON COMMA LPAREN RPAREN                 /* symbol     */
%token LSQBRT RSQBRT LCUBRT RCUBRT                   /* symbol     */
%token ADD SUB MUL DIV MOD                           /* op         */
%token ID                                            /* identifier */
%token ASSIGN LT LTE NEQ GT GTE EQ                   /* relational */
%token AND OR NOT                                    /* boolean op */

%nonassoc ASSIGN LT LTE NEQ GT GTE EQ
%left  AND OR NOT ADD SUB MUL DIV MOD
%%

program
    : decl_and_def_list { PTRACE(reduce to program); }
    ;

decl_and_def_list
    : decl_and_def_list declaration_list
    | decl_and_def_list definition_list
    ;

declaration_list
    : declaration_list const_decl
    | declaration_list var_decl
    | declaration_list funct_decl
    ;

const_decl
    : CONST scalar_type identifier_list SEMICOLON
    ;

var_decl
    : scalar_type identifier_list SEMICOLON
    ;

funct_decl
    : type ID funct_arg SEMICOLON
    ;

funct_arg
    : LPAREN RPAREN
    : LPAREN arg_list RPAREN
    ;

arg_list
    : arg_list COMMA scalar_type ID
    : scalar_type ID
    ;

definition_list
    : definition_list funct_def
    : funct_def
    ;

funct_def
    : type ID funct_arg compound
    ;

compound
    : LCUBRT declaration_list RETURN SEMICOLON RCUBRT
    : LCUBRT declaration_list RETURN ID SEMICOLON RCUBRT
    ;

type
    : VOID   { PTRACE(reduce to type void); }
    : INT    { PTRACE(reduce to type int); }
    : DOUBLE { PTRACE(reduce to type double); }
    : FLOAT  { PTRACE(reduce to type float); }
    : STRING { PTRACE(reduce to type string); }
    : BOOL   { PTRACE(reduce to type bool); }
    ;

scalar_type
    : INT    { PTRACE(reduce to scalar_type int); }
    : DOUBLE { PTRACE(reduce to scalar_type double); }
    : FLOAT  { PTRACE(reduce to scalar_type float); }
    : STRING { PTRACE(reduce to scalar_type string); }
    : BOOL   { PTRACE(reduce to scalar_type bool); }
    ;

identifier_list
    : identifer_list COMMA ID { PTRACE(reduce to identifier_list 1); }
    : ID                      { PTRACE(reduce to identifier_list 2); }
    ;

%%

int yyerror( char *msg ) {
    fprintf( stderr, "\n|--------------------------------------------------------------------------\n" );
    fprintf( stderr, "| Error found in Line #%d: %s\n", linenum, buf );
    fprintf( stderr, "|\n" );
    fprintf( stderr, "| Unmatched token: %s\n", yytext );
    fprintf( stderr, "|--------------------------------------------------------------------------\n" );
    exit(-1);
}

#include <stdio.h>
#include <stdlib.h>

extern int yyparse();	/* declared by yacc */
extern FILE* yyin;	    /* declared by lex */

int main( int argc, char **argv ) {
    if( argc != 2 ) {
        fprintf( stdout,  "Usage:  ./parser  [filename]\n" );
        exit(0);
    }

    FILE *fp = fopen( argv[1], "r" );

    if( fp == NULL ) {
        fprintf( stdout, "Open  file  error\n" );
        exit(-1);
    }

    yyin = fp;
    yyparse();

    fprintf( stdout, "\n" );
    fprintf( stdout, "|--------------------------------|\n" );
    fprintf( stdout, "|  There is no syntactic error!  |\n" );
    fprintf( stdout, "|--------------------------------|\n" );
    exit(0);
}
