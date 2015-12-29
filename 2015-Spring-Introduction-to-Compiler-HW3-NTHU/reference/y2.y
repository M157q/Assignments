
/* This is a simpled gcc grammar */
/* Copyright (C) 1987 Free Software Foundation, Inc. */
/* BISON parser for a simplied C by Jenq-kuen Lee  Sep 20, 1993    */

%{
#include <stdio.h>
#include "code.h"
extern int lineno;
extern FILE *f_asm;
int    errcnt=0;
int    errline=0;
char   *install_symbol();
%}

%start program
%union { 
         int       token ;
         char      charv ;
         char      *ident;
       }
/* all identifiers   that are not reserved words
   and are not declared typedefs in the current block */
%token IDENTIFIER INTEGER FLOAT

/* reserved words that specify storage class.
   yylval contains an IDENTIFIER_NODE which indicates which one.  */
%token SCSPEC

/* reserved words that specify type.
   yylval contains an IDENTIFIER_NODE which indicates which one.  */
%token TYPESPEC ENUM STRUCT UNION

/* reserved words that modify type: "const" or "volatile".
   yylval contains an IDENTIFIER_NODE which indicates which one.  */
%token TYPEMOD

%token CONSTANT

/* String constants in raw form.
   yylval is a STRING_CST node.  */
%token STRING


/* the reserved words */
%token SIZEOF  IF ELSE WHILE DO FOR SWITCH CASE DEFAULT_TOKEN
%token BREAK CONTINUE RETURN GOTO ASM

%type <ident> notype_declarator IDENTIFIER primary expr_no_commas

%type <token> CONSTANT

/* Define the operator tokens and their precedences.
   The value is an integer because, if used, it is the tree code
   to use in the expression made from the operator.  */
%left  <charv> ';'
%left IDENTIFIER  SCSPEC TYPESPEC TYPEMOD
%left  <charv> ','
%right <charv> '='
%right <token> ASSIGN 
%right <charv> '?' ':'
%left <charv> OROR
%left <charv> ANDAND
%left <charv> '|'
%left <charv> '^'
%left <charv> '&'
%left <token> EQCOMPARE
%left <token> ARITHCOMPARE  '>' '<' 
%left <charv> LSHIFT RSHIFT
%left <charv> '+' '-'
%left <token> '*' '/' '%'
%right <token> UNARY PLUSPLUS MINUSMINUS 
%left HYPERUNARY 
%left <token> POINTSAT '.'


%{
/* external function is defined here */
void error();
int TRACEON = 100;
%}     


%%

program: /* empty */
          { if (TRACEON) printf("1\n ");}
	| extdefs
          { if (TRACEON) printf("2\n ");}
	;

extdefs:
          extdef
          { if (TRACEON) printf("3\n ");}
	| extdefs  extdef
          { if (TRACEON) printf("4\n ");}
	;

extdef:
	 TYPESPEC notype_declarator ';'
	  { if (TRACEON) printf("7 ");
            set_global_vars($2);
          }
        | notype_declarator
          	  { if (TRACEON) printf("10 ");
                    cur_scope++;
                    set_scope_and_offset_of_param($1);
		    code_gen_func_header($1);
                  }
          '{'  xdecls 
          	  { if (TRACEON) printf("10.5 ");
                    set_local_vars($1);
                  }
               stmts
		{
                  if (TRACEON) printf("11 ");
                  pop_up_symbol(cur_scope);
                  cur_scope--;
                  code_gen_at_end_of_function_body($1);
                }
           '}'
        | error ';'
	  { if (TRACEON) printf("8 "); }
	| ';'
	  { if (TRACEON) printf("9 "); }
	;

/* Must appear precede expr for resolve precedence problem */
/* A nonempty list of identifiers.  */

/* modified */
expr_no_commas:
	primary
           { if (TRACEON) printf("15 ") ;
 	     $$= $1;
           }
	| expr_no_commas '+' expr_no_commas
		{ 
                  if (TRACEON) printf("16 ") ; 

                  fprintf(f_asm,"        pop  cx\n");
                  fprintf(f_asm,"        pop  bx\n");
                  fprintf(f_asm,"        add  bx, cx\n");
                  fprintf(f_asm,"        push bx\n");
		  $$= NULL;
                }
	| expr_no_commas '=' expr_no_commas
		{ char *s;
		  int index;

		  if (TRACEON) printf("17 ") ;
		  s= $1;
		  if (!s) err("improper expression at LHS");
		  index = look_up_symbol(s);
                  fprintf(f_asm,"        pop  bx\n");
                  fprintf(f_asm,"        pop  cx\n");
		  switch(table[index].mode) {
                  case ARGUMENT_MODE:
		    fprintf(f_asm,"        mov  word ptr [bp-%d], bx\n",table[index].offset*2+2);
		    fprintf(f_asm,"        push bx\n");		    
                    break;
		  case LOCAL_MODE:
		    fprintf(f_asm,"        mov  word ptr [bp+%d], bx\n",table[index].offset*2);
		    fprintf(f_asm,"        push bx\n");		    
                    break;
		  default: /* Global Vars */
		    fprintf(f_asm,"        mov  word ptr DGROUP:_%s,0, bx\n",table[index].name);
		    fprintf(f_asm,"        push bx\n");		                       
		  }
                }
	| expr_no_commas '*' expr_no_commas
		{ if (TRACEON) printf("18 ") ;

                  fprintf(f_asm,"        pop  cx\n");
                  fprintf(f_asm,"        pop  bx\n");
                  fprintf(f_asm,"        mul  bx, cx\n");
                  fprintf(f_asm,"        push bx\n");
		  $$= NULL;
                }
	| expr_no_commas ARITHCOMPARE expr_no_commas
		{ if (TRACEON) printf("19 ") ; }
	;


/* modified */
primary:
        IDENTIFIER
  	{    	  int index;

                  if (TRACEON) printf("20 ") ;
                  
		  index =look_up_symbol($1);
		  switch(table[index].mode) {
                  case ARGUMENT_MODE:
		    fprintf(f_asm,"        mov  bx, word ptr [bp-%d]\n",table[index].offset*2+2);
		    fprintf(f_asm,"        push bx\n");		    
                    break;
		  case LOCAL_MODE:
		    fprintf(f_asm,"        mov  bx, word ptr [bp+%d]\n",table[index].offset*2);
		    fprintf(f_asm,"        push bx\n");		    
                    break;
		  default: /* Global Vars */
		    fprintf(f_asm,"        mov  bx, word ptr DGROUP:_%s,0\n",table[index].name);
		    fprintf(f_asm,"        push bx\n");		                       
		  }
		  $$=$1;
         }
	| CONSTANT
                { if (TRACEON) printf("21 ") ;
		  fprintf(f_asm,"        mov  bx, %d\n",$1);
		  fprintf(f_asm,"        push bx\n",$1);
                }
	| STRING
		{ 
		  if (TRACEON) printf("22 ") ;
                }
	| primary PLUSPLUS
		{ 
		  if (TRACEON) printf("23 ") ;
                }

        ;

notype_declarator:
	  notype_declarator '(' parmlist ')'  %prec '.'
		{   if (TRACEON) printf("24 ") ;
		    $$=$1;
                }                  
        | IDENTIFIER
		{   if (TRACEON) printf("25 ") ;
                    $$=install_symbol($1);
                }                  
	;

/* This is what appears inside the parens in a function declarator.
   Is value is represented in the format that grokdeclarator expects.  */
parmlist:  /* empty */
               { if (TRACEON) printf("26 ") ; }
		
	| parms
  		{ if (TRACEON) printf("27 ") ;  }
		
	;

/* A nonempty list of parameter declarations or type names.  */
parms:	
	parm
  		{ if (TRACEON) printf("28 ") ;  }
	| parms ',' parm
  		{ if (TRACEON) printf("29 ") ;  }
	;

parm:
	  TYPESPEC notype_declarator
  		{ if (TRACEON) printf("30 ") ;  }
   ;


/* at least one statement, the first of which parses without error.  */
/* stmts is used only after decls, so an invalid first statement
   is actually regarded as an invalid decl and part of the decls.  */

stmts:
	stmt
               { if (TRACEON) printf("31 ") ;  }
	| stmts stmt
               { if (TRACEON) printf("32 ") ;  }
	;


/* modified */
stmt:
	 expr_no_commas ';'
	{
	  fprintf(f_asm,"        pop  cx\n");
	  fprintf(f_asm,"   ;\n");
        }
	;


xdecls:
	/* empty */
           { if (TRACEON) printf("102 ") ; }
	| decls
           { if (TRACEON) printf("103 ") ; }
	;

decls:
	decl
           { if (TRACEON) printf("104 ") ;
           }
	| decls decl
           { if (TRACEON) printf("106 ") ;
           }
	;

decl:	 TYPESPEC notype_declarator ';'
            { if (TRACEON) printf("110 ") ;}

%%


/*
 *	  s - the error message to be printed
 */
void 
yyerror(s)
	char   *s;
{
	err(s);
}


err(s)
char   *s;
{
	if (! errcnt++)
		errline = lineno;
         fprintf(stderr,"Error on line %d \n",lineno);
	
	exit(1);
}




