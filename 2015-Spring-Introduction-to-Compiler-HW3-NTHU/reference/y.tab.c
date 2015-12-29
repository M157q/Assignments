
# line 7 "y2.y"
#include <stdio.h>
#include "code.h"
extern int lineno;
extern FILE *f_asm;
int    errcnt=0;
int    errline=0;
char   *install_symbol();

# line 17 "y2.y"
typedef union
#ifdef __cplusplus
	YYSTYPE
#endif
 { 
         int       token ;
         char      charv ;
         char      *ident;
       } YYSTYPE;
# define IDENTIFIER 257
# define INTEGER 258
# define FLOAT 259
# define SCSPEC 260
# define TYPESPEC 261
# define ENUM 262
# define STRUCT 263
# define UNION 264
# define TYPEMOD 265
# define CONSTANT 266
# define STRING 267
# define SIZEOF 268
# define IF 269
# define ELSE 270
# define WHILE 271
# define DO 272
# define FOR 273
# define SWITCH 274
# define CASE 275
# define DEFAULT_TOKEN 276
# define BREAK 277
# define CONTINUE 278
# define RETURN 279
# define GOTO 280
# define ASM 281
# define ASSIGN 282
# define OROR 283
# define ANDAND 284
# define EQCOMPARE 285
# define ARITHCOMPARE 286
# define LSHIFT 287
# define RSHIFT 288
# define UNARY 289
# define PLUSPLUS 290
# define MINUSMINUS 291
# define HYPERUNARY 292
# define POINTSAT 293

# line 78 "y2.y"
/* external function is defined here */
void error();
int TRACEON = 100;

#include <inttypes.h>

#ifdef __STDC__
#include <stdlib.h>
#include <string.h>
#define	YYCONST	const
#else
#include <malloc.h>
#include <memory.h>
#define	YYCONST
#endif

#include <values.h>

#if defined(__cplusplus) || defined(__STDC__)

#if defined(__cplusplus) && defined(__EXTERN_C__)
extern "C" {
#endif
#ifndef yyerror
#if defined(__cplusplus)
	void yyerror(YYCONST char *);
#endif
#endif
#ifndef yylex
	int yylex(void);
#endif
	int yyparse(void);
#if defined(__cplusplus) && defined(__EXTERN_C__)
}
#endif

#endif

#define yyclearin yychar = -1
#define yyerrok yyerrflag = 0
extern int yychar;
extern int yyerrflag;
YYSTYPE yylval;
YYSTYPE yyval;
typedef int yytabelem;
#ifndef YYMAXDEPTH
#define YYMAXDEPTH 150
#endif
#if YYMAXDEPTH > 0
int yy_yys[YYMAXDEPTH], *yys = yy_yys;
YYSTYPE yy_yyv[YYMAXDEPTH], *yyv = yy_yyv;
#else	/* user does initial allocation */
int *yys;
YYSTYPE *yyv;
#endif
static int yymaxdepth = YYMAXDEPTH;
# define YYERRCODE 256

# line 300 "y2.y"



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




static YYCONST yytabelem yyexca[] ={
-1, 0,
	0, 1,
	-2, 0,
-1, 1,
	0, -1,
	-2, 0,
-1, 2,
	0, 2,
	-2, 0,
	};
# define YYNPROD 36
# define YYLAST 248
static YYCONST yytabelem yyact[]={

    46,    43,    41,    43,    41,    35,     7,    19,    23,     8,
    47,    15,    12,    12,    36,    37,    13,    33,    45,    25,
    42,    43,    42,    43,    41,    24,    12,    18,    21,    22,
     5,    38,    14,    32,     3,    10,    17,     9,    16,    39,
    31,    27,    20,    11,     2,    34,     1,     0,     0,     0,
    26,    28,     0,    30,    29,     0,     0,     0,     0,    48,
    49,    50,    51,     0,     0,    40,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     6,     8,     0,     0,     0,     4,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,    44,     0,    44 };
static YYCONST yytabelem yypact[]={

   -53,-10000000,   -53,-10000000,  -248,   -14,   -43,-10000000,-10000000,-10000000,
   -27,  -112,  -254,-10000000,-10000000,  -253,   -16,   -25,-10000000,  -248,
-10000000,  -253,-10000000,  -248,-10000000,  -254,   -14,  -252,-10000000,   -28,
-10000000,  -252,-10000000,   -41,  -290,-10000000,-10000000,-10000000,-10000000,  -115,
-10000000,  -252,  -252,  -252,  -252,-10000000,-10000000,-10000000,   -21,   -39,
-10000000,   -19 };
static YYCONST yytabelem yypgo[]={

     0,    46,    30,    45,    17,    44,    34,    43,    42,    41,
    40,    39,    38,    36,    27,    33,    28,    29 };
static YYCONST yytabelem yyr1[]={

     0,     1,     1,     5,     5,     6,     7,     9,    11,     6,
     6,     6,     4,     4,     4,     4,     4,     3,     3,     3,
     3,     2,     2,    12,    12,    13,    13,    14,    10,    10,
    15,     8,     8,    16,    16,    17 };
static YYCONST yytabelem yyr2[]={

     0,     1,     3,     3,     5,     7,     1,     1,     1,    16,
     5,     3,     3,     7,     7,     7,     7,     3,     3,     3,
     5,     9,     3,     1,     3,     3,     7,     5,     3,     5,
     5,     1,     3,     3,     5,     7 };
static YYCONST yytabelem yychk[]={

-10000000,    -1,    -5,    -6,   261,    -2,   256,    59,   257,    -6,
    -2,    -7,    40,    59,    59,   123,   -12,   -13,   -14,   261,
    -8,   -16,   -17,   261,    41,    44,    -2,    -9,   -17,    -2,
   -14,   -10,   -15,    -4,    -3,   257,   266,   267,    59,   -11,
   -15,    43,    61,    42,   286,    59,   290,   125,    -4,    -4,
    -4,    -4 };
static YYCONST yytabelem yydef[]={

    -2,    -2,    -2,     3,     0,     6,     0,    11,    22,     4,
     0,     0,    23,    10,     5,    31,     0,    24,    25,     0,
     7,    32,    33,     0,    21,     0,    27,     0,    34,     0,
    26,     8,    28,     0,    12,    17,    18,    19,    35,     0,
    29,     0,     0,     0,     0,    30,    20,     9,    13,    14,
    15,    16 };
typedef struct
#ifdef __cplusplus
	yytoktype
#endif
{
#ifdef __cplusplus
const
#endif
char *t_name; int t_val; } yytoktype;
#ifndef YYDEBUG
#	define YYDEBUG	0	/* don't allow debugging */
#endif

#if YYDEBUG

yytoktype yytoks[] =
{
	"IDENTIFIER",	257,
	"INTEGER",	258,
	"FLOAT",	259,
	"SCSPEC",	260,
	"TYPESPEC",	261,
	"ENUM",	262,
	"STRUCT",	263,
	"UNION",	264,
	"TYPEMOD",	265,
	"CONSTANT",	266,
	"STRING",	267,
	"SIZEOF",	268,
	"IF",	269,
	"ELSE",	270,
	"WHILE",	271,
	"DO",	272,
	"FOR",	273,
	"SWITCH",	274,
	"CASE",	275,
	"DEFAULT_TOKEN",	276,
	"BREAK",	277,
	"CONTINUE",	278,
	"RETURN",	279,
	"GOTO",	280,
	"ASM",	281,
	";",	59,
	",",	44,
	"=",	61,
	"ASSIGN",	282,
	"?",	63,
	":",	58,
	"OROR",	283,
	"ANDAND",	284,
	"|",	124,
	"^",	94,
	"&",	38,
	"EQCOMPARE",	285,
	"ARITHCOMPARE",	286,
	">",	62,
	"<",	60,
	"LSHIFT",	287,
	"RSHIFT",	288,
	"+",	43,
	"-",	45,
	"*",	42,
	"/",	47,
	"%",	37,
	"UNARY",	289,
	"PLUSPLUS",	290,
	"MINUSMINUS",	291,
	"HYPERUNARY",	292,
	"POINTSAT",	293,
	".",	46,
	"-unknown-",	-1	/* ends search */
};

#ifdef __cplusplus
const
#endif
char * yyreds[] =
{
	"-no such reduction-",
	"program : /* empty */",
	"program : extdefs",
	"extdefs : extdef",
	"extdefs : extdefs extdef",
	"extdef : TYPESPEC notype_declarator ';'",
	"extdef : notype_declarator",
	"extdef : notype_declarator '{' xdecls",
	"extdef : notype_declarator '{' xdecls stmts",
	"extdef : notype_declarator '{' xdecls stmts '}'",
	"extdef : error ';'",
	"extdef : ';'",
	"expr_no_commas : primary",
	"expr_no_commas : expr_no_commas '+' expr_no_commas",
	"expr_no_commas : expr_no_commas '=' expr_no_commas",
	"expr_no_commas : expr_no_commas '*' expr_no_commas",
	"expr_no_commas : expr_no_commas ARITHCOMPARE expr_no_commas",
	"primary : IDENTIFIER",
	"primary : CONSTANT",
	"primary : STRING",
	"primary : primary PLUSPLUS",
	"notype_declarator : notype_declarator '(' parmlist ')'",
	"notype_declarator : IDENTIFIER",
	"parmlist : /* empty */",
	"parmlist : parms",
	"parms : parm",
	"parms : parms ',' parm",
	"parm : TYPESPEC notype_declarator",
	"stmts : stmt",
	"stmts : stmts stmt",
	"stmt : expr_no_commas ';'",
	"xdecls : /* empty */",
	"xdecls : decls",
	"decls : decl",
	"decls : decls decl",
	"decl : TYPESPEC notype_declarator ';'",
};
#endif /* YYDEBUG */
# line	1 "/usr/ccs/bin/yaccpar"
/*
 * Copyright (c) 1993 by Sun Microsystems, Inc.
 */

#pragma ident	"@(#)yaccpar	6.16	99/01/20 SMI"

/*
** Skeleton parser driver for yacc output
*/

/*
** yacc user known macros and defines
*/
#define YYERROR		goto yyerrlab
#define YYACCEPT	return(0)
#define YYABORT		return(1)
#define YYBACKUP( newtoken, newvalue )\
{\
	if ( yychar >= 0 || ( yyr2[ yytmp ] >> 1 ) != 1 )\
	{\
		yyerror( "syntax error - cannot backup" );\
		goto yyerrlab;\
	}\
	yychar = newtoken;\
	yystate = *yyps;\
	yylval = newvalue;\
	goto yynewstate;\
}
#define YYRECOVERING()	(!!yyerrflag)
#define YYNEW(type)	malloc(sizeof(type) * yynewmax)
#define YYCOPY(to, from, type) \
	(type *) memcpy(to, (char *) from, yymaxdepth * sizeof (type))
#define YYENLARGE( from, type) \
	(type *) realloc((char *) from, yynewmax * sizeof(type))
#ifndef YYDEBUG
#	define YYDEBUG	1	/* make debugging available */
#endif

/*
** user known globals
*/
int yydebug;			/* set to 1 to get debugging */

/*
** driver internal defines
*/
#define YYFLAG		(-10000000)

/*
** global variables used by the parser
*/
YYSTYPE *yypv;			/* top of value stack */
int *yyps;			/* top of state stack */

int yystate;			/* current state */
int yytmp;			/* extra var (lasts between blocks) */

int yynerrs;			/* number of errors */
int yyerrflag;			/* error recovery flag */
int yychar;			/* current input token number */



#ifdef YYNMBCHARS
#define YYLEX()		yycvtok(yylex())
/*
** yycvtok - return a token if i is a wchar_t value that exceeds 255.
**	If i<255, i itself is the token.  If i>255 but the neither 
**	of the 30th or 31st bit is on, i is already a token.
*/
#if defined(__STDC__) || defined(__cplusplus)
int yycvtok(int i)
#else
int yycvtok(i) int i;
#endif
{
	int first = 0;
	int last = YYNMBCHARS - 1;
	int mid;
	wchar_t j;

	if(i&0x60000000){/*Must convert to a token. */
		if( yymbchars[last].character < i ){
			return i;/*Giving up*/
		}
		while ((last>=first)&&(first>=0)) {/*Binary search loop*/
			mid = (first+last)/2;
			j = yymbchars[mid].character;
			if( j==i ){/*Found*/ 
				return yymbchars[mid].tvalue;
			}else if( j<i ){
				first = mid + 1;
			}else{
				last = mid -1;
			}
		}
		/*No entry in the table.*/
		return i;/* Giving up.*/
	}else{/* i is already a token. */
		return i;
	}
}
#else/*!YYNMBCHARS*/
#define YYLEX()		yylex()
#endif/*!YYNMBCHARS*/

/*
** yyparse - return 0 if worked, 1 if syntax error not recovered from
*/
#if defined(__STDC__) || defined(__cplusplus)
int yyparse(void)
#else
int yyparse()
#endif
{
	register YYSTYPE *yypvt = 0;	/* top of value stack for $vars */

#if defined(__cplusplus) || defined(lint)
/*
	hacks to please C++ and lint - goto's inside
	switch should never be executed
*/
	static int __yaccpar_lint_hack__ = 0;
	switch (__yaccpar_lint_hack__)
	{
		case 1: goto yyerrlab;
		case 2: goto yynewstate;
	}
#endif

	/*
	** Initialize externals - yyparse may be called more than once
	*/
	yypv = &yyv[-1];
	yyps = &yys[-1];
	yystate = 0;
	yytmp = 0;
	yynerrs = 0;
	yyerrflag = 0;
	yychar = -1;

#if YYMAXDEPTH <= 0
	if (yymaxdepth <= 0)
	{
		if ((yymaxdepth = YYEXPAND(0)) <= 0)
		{
			yyerror("yacc initialization error");
			YYABORT;
		}
	}
#endif

	{
		register YYSTYPE *yy_pv;	/* top of value stack */
		register int *yy_ps;		/* top of state stack */
		register int yy_state;		/* current state */
		register int  yy_n;		/* internal state number info */
	goto yystack;	/* moved from 6 lines above to here to please C++ */

		/*
		** get globals into registers.
		** branch to here only if YYBACKUP was called.
		*/
	yynewstate:
		yy_pv = yypv;
		yy_ps = yyps;
		yy_state = yystate;
		goto yy_newstate;

		/*
		** get globals into registers.
		** either we just started, or we just finished a reduction
		*/
	yystack:
		yy_pv = yypv;
		yy_ps = yyps;
		yy_state = yystate;

		/*
		** top of for (;;) loop while no reductions done
		*/
	yy_stack:
		/*
		** put a state and value onto the stacks
		*/
#if YYDEBUG
		/*
		** if debugging, look up token value in list of value vs.
		** name pairs.  0 and negative (-1) are special values.
		** Note: linear search is used since time is not a real
		** consideration while debugging.
		*/
		if ( yydebug )
		{
			register int yy_i;

			printf( "State %d, token ", yy_state );
			if ( yychar == 0 )
				printf( "end-of-file\n" );
			else if ( yychar < 0 )
				printf( "-none-\n" );
			else
			{
				for ( yy_i = 0; yytoks[yy_i].t_val >= 0;
					yy_i++ )
				{
					if ( yytoks[yy_i].t_val == yychar )
						break;
				}
				printf( "%s\n", yytoks[yy_i].t_name );
			}
		}
#endif /* YYDEBUG */
		if ( ++yy_ps >= &yys[ yymaxdepth ] )	/* room on stack? */
		{
			/*
			** reallocate and recover.  Note that pointers
			** have to be reset, or bad things will happen
			*/
			long yyps_index = (yy_ps - yys);
			long yypv_index = (yy_pv - yyv);
			long yypvt_index = (yypvt - yyv);
			int yynewmax;
#ifdef YYEXPAND
			yynewmax = YYEXPAND(yymaxdepth);
#else
			yynewmax = 2 * yymaxdepth;	/* double table size */
			if (yymaxdepth == YYMAXDEPTH)	/* first time growth */
			{
				char *newyys = (char *)YYNEW(int);
				char *newyyv = (char *)YYNEW(YYSTYPE);
				if (newyys != 0 && newyyv != 0)
				{
					yys = YYCOPY(newyys, yys, int);
					yyv = YYCOPY(newyyv, yyv, YYSTYPE);
				}
				else
					yynewmax = 0;	/* failed */
			}
			else				/* not first time */
			{
				yys = YYENLARGE(yys, int);
				yyv = YYENLARGE(yyv, YYSTYPE);
				if (yys == 0 || yyv == 0)
					yynewmax = 0;	/* failed */
			}
#endif
			if (yynewmax <= yymaxdepth)	/* tables not expanded */
			{
				yyerror( "yacc stack overflow" );
				YYABORT;
			}
			yymaxdepth = yynewmax;

			yy_ps = yys + yyps_index;
			yy_pv = yyv + yypv_index;
			yypvt = yyv + yypvt_index;
		}
		*yy_ps = yy_state;
		*++yy_pv = yyval;

		/*
		** we have a new state - find out what to do
		*/
	yy_newstate:
		if ( ( yy_n = yypact[ yy_state ] ) <= YYFLAG )
			goto yydefault;		/* simple state */
#if YYDEBUG
		/*
		** if debugging, need to mark whether new token grabbed
		*/
		yytmp = yychar < 0;
#endif
		if ( ( yychar < 0 ) && ( ( yychar = YYLEX() ) < 0 ) )
			yychar = 0;		/* reached EOF */
#if YYDEBUG
		if ( yydebug && yytmp )
		{
			register int yy_i;

			printf( "Received token " );
			if ( yychar == 0 )
				printf( "end-of-file\n" );
			else if ( yychar < 0 )
				printf( "-none-\n" );
			else
			{
				for ( yy_i = 0; yytoks[yy_i].t_val >= 0;
					yy_i++ )
				{
					if ( yytoks[yy_i].t_val == yychar )
						break;
				}
				printf( "%s\n", yytoks[yy_i].t_name );
			}
		}
#endif /* YYDEBUG */
		if ( ( ( yy_n += yychar ) < 0 ) || ( yy_n >= YYLAST ) )
			goto yydefault;
		if ( yychk[ yy_n = yyact[ yy_n ] ] == yychar )	/*valid shift*/
		{
			yychar = -1;
			yyval = yylval;
			yy_state = yy_n;
			if ( yyerrflag > 0 )
				yyerrflag--;
			goto yy_stack;
		}

	yydefault:
		if ( ( yy_n = yydef[ yy_state ] ) == -2 )
		{
#if YYDEBUG
			yytmp = yychar < 0;
#endif
			if ( ( yychar < 0 ) && ( ( yychar = YYLEX() ) < 0 ) )
				yychar = 0;		/* reached EOF */
#if YYDEBUG
			if ( yydebug && yytmp )
			{
				register int yy_i;

				printf( "Received token " );
				if ( yychar == 0 )
					printf( "end-of-file\n" );
				else if ( yychar < 0 )
					printf( "-none-\n" );
				else
				{
					for ( yy_i = 0;
						yytoks[yy_i].t_val >= 0;
						yy_i++ )
					{
						if ( yytoks[yy_i].t_val
							== yychar )
						{
							break;
						}
					}
					printf( "%s\n", yytoks[yy_i].t_name );
				}
			}
#endif /* YYDEBUG */
			/*
			** look through exception table
			*/
			{
				register YYCONST int *yyxi = yyexca;

				while ( ( *yyxi != -1 ) ||
					( yyxi[1] != yy_state ) )
				{
					yyxi += 2;
				}
				while ( ( *(yyxi += 2) >= 0 ) &&
					( *yyxi != yychar ) )
					;
				if ( ( yy_n = yyxi[1] ) < 0 )
					YYACCEPT;
			}
		}

		/*
		** check for syntax error
		*/
		if ( yy_n == 0 )	/* have an error */
		{
			/* no worry about speed here! */
			switch ( yyerrflag )
			{
			case 0:		/* new error */
				yyerror( "syntax error" );
				goto skip_init;
			yyerrlab:
				/*
				** get globals into registers.
				** we have a user generated syntax type error
				*/
				yy_pv = yypv;
				yy_ps = yyps;
				yy_state = yystate;
			skip_init:
				yynerrs++;
				/* FALLTHRU */
			case 1:
			case 2:		/* incompletely recovered error */
					/* try again... */
				yyerrflag = 3;
				/*
				** find state where "error" is a legal
				** shift action
				*/
				while ( yy_ps >= yys )
				{
					yy_n = yypact[ *yy_ps ] + YYERRCODE;
					if ( yy_n >= 0 && yy_n < YYLAST &&
						yychk[yyact[yy_n]] == YYERRCODE)					{
						/*
						** simulate shift of "error"
						*/
						yy_state = yyact[ yy_n ];
						goto yy_stack;
					}
					/*
					** current state has no shift on
					** "error", pop stack
					*/
#if YYDEBUG
#	define _POP_ "Error recovery pops state %d, uncovers state %d\n"
					if ( yydebug )
						printf( _POP_, *yy_ps,
							yy_ps[-1] );
#	undef _POP_
#endif
					yy_ps--;
					yy_pv--;
				}
				/*
				** there is no state on stack with "error" as
				** a valid shift.  give up.
				*/
				YYABORT;
			case 3:		/* no shift yet; eat a token */
#if YYDEBUG
				/*
				** if debugging, look up token in list of
				** pairs.  0 and negative shouldn't occur,
				** but since timing doesn't matter when
				** debugging, it doesn't hurt to leave the
				** tests here.
				*/
				if ( yydebug )
				{
					register int yy_i;

					printf( "Error recovery discards " );
					if ( yychar == 0 )
						printf( "token end-of-file\n" );
					else if ( yychar < 0 )
						printf( "token -none-\n" );
					else
					{
						for ( yy_i = 0;
							yytoks[yy_i].t_val >= 0;
							yy_i++ )
						{
							if ( yytoks[yy_i].t_val
								== yychar )
							{
								break;
							}
						}
						printf( "token %s\n",
							yytoks[yy_i].t_name );
					}
				}
#endif /* YYDEBUG */
				if ( yychar == 0 )	/* reached EOF. quit */
					YYABORT;
				yychar = -1;
				goto yy_newstate;
			}
		}/* end if ( yy_n == 0 ) */
		/*
		** reduction by production yy_n
		** put stack tops, etc. so things right after switch
		*/
#if YYDEBUG
		/*
		** if debugging, print the string that is the user's
		** specification of the reduction which is just about
		** to be done.
		*/
		if ( yydebug )
			printf( "Reduce by (%d) \"%s\"\n",
				yy_n, yyreds[ yy_n ] );
#endif
		yytmp = yy_n;			/* value to switch over */
		yypvt = yy_pv;			/* $vars top of value stack */
		/*
		** Look in goto table for next state
		** Sorry about using yy_state here as temporary
		** register variable, but why not, if it works...
		** If yyr2[ yy_n ] doesn't have the low order bit
		** set, then there is no action to be done for
		** this reduction.  So, no saving & unsaving of
		** registers done.  The only difference between the
		** code just after the if and the body of the if is
		** the goto yy_stack in the body.  This way the test
		** can be made before the choice of what to do is needed.
		*/
		{
			/* length of production doubled with extra bit */
			register int yy_len = yyr2[ yy_n ];

			if ( !( yy_len & 01 ) )
			{
				yy_len >>= 1;
				yyval = ( yy_pv -= yy_len )[1];	/* $$ = $1 */
				yy_state = yypgo[ yy_n = yyr1[ yy_n ] ] +
					*( yy_ps -= yy_len ) + 1;
				if ( yy_state >= YYLAST ||
					yychk[ yy_state =
					yyact[ yy_state ] ] != -yy_n )
				{
					yy_state = yyact[ yypgo[ yy_n ] ];
				}
				goto yy_stack;
			}
			yy_len >>= 1;
			yyval = ( yy_pv -= yy_len )[1];	/* $$ = $1 */
			yy_state = yypgo[ yy_n = yyr1[ yy_n ] ] +
				*( yy_ps -= yy_len ) + 1;
			if ( yy_state >= YYLAST ||
				yychk[ yy_state = yyact[ yy_state ] ] != -yy_n )
			{
				yy_state = yyact[ yypgo[ yy_n ] ];
			}
		}
					/* save until reenter driver code */
		yystate = yy_state;
		yyps = yy_ps;
		yypv = yy_pv;
	}
	/*
	** code supplied by user is placed in this switch
	*/
	switch( yytmp )
	{
		
case 1:
# line 87 "y2.y"
{ if (TRACEON) printf("1\n ");} break;
case 2:
# line 89 "y2.y"
{ if (TRACEON) printf("2\n ");} break;
case 3:
# line 94 "y2.y"
{ if (TRACEON) printf("3\n ");} break;
case 4:
# line 96 "y2.y"
{ if (TRACEON) printf("4\n ");} break;
case 5:
# line 101 "y2.y"
{ if (TRACEON) printf("7 ");
            set_global_vars(yypvt[-1].ident);
          } break;
case 6:
# line 105 "y2.y"
{ if (TRACEON) printf("10 ");
                    cur_scope++;
                    set_scope_and_offset_of_param(yypvt[-0].ident);
		    code_gen_func_header(yypvt[-0].ident);
                  } break;
case 7:
# line 111 "y2.y"
{ if (TRACEON) printf("10.5 ");
                    set_local_vars(yypvt[-3].ident);
                  } break;
case 8:
# line 115 "y2.y"
{
                  if (TRACEON) printf("11 ");
                  pop_up_symbol(cur_scope);
                  cur_scope--;
                  code_gen_at_end_of_function_body(yypvt[-5].ident);
                } break;
case 10:
# line 123 "y2.y"
{ if (TRACEON) printf("8 "); } break;
case 11:
# line 125 "y2.y"
{ if (TRACEON) printf("9 "); } break;
case 12:
# line 134 "y2.y"
{ if (TRACEON) printf("15 ") ;
 	     yyval.ident= yypvt[-0].ident;
           } break;
case 13:
# line 138 "y2.y"
{ 
                  if (TRACEON) printf("16 ") ; 

                  fprintf(f_asm,"        pop  cx\n");
                  fprintf(f_asm,"        pop  bx\n");
                  fprintf(f_asm,"        add  bx, cx\n");
                  fprintf(f_asm,"        push bx\n");
		  yyval.ident= NULL;
                } break;
case 14:
# line 148 "y2.y"
{ char *s;
		  int index;

		  if (TRACEON) printf("17 ") ;
		  s= yypvt[-2].ident;
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
                } break;
case 15:
# line 172 "y2.y"
{ if (TRACEON) printf("18 ") ;

                  fprintf(f_asm,"        pop  cx\n");
                  fprintf(f_asm,"        pop  bx\n");
                  fprintf(f_asm,"        mul  bx, cx\n");
                  fprintf(f_asm,"        push bx\n");
		  yyval.ident= NULL;
                } break;
case 16:
# line 181 "y2.y"
{ if (TRACEON) printf("19 ") ; } break;
case 17:
# line 188 "y2.y"
{    	  int index;

                  if (TRACEON) printf("20 ") ;
                  
		  index =look_up_symbol(yypvt[-0].ident);
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
		  yyval.ident=yypvt[-0].ident;
         } break;
case 18:
# line 209 "y2.y"
{ if (TRACEON) printf("21 ") ;
		  fprintf(f_asm,"        mov  bx, %d\n",yypvt[-0].token);
		  fprintf(f_asm,"        push bx\n",yypvt[-0].token);
                } break;
case 19:
# line 214 "y2.y"
{ 
		  if (TRACEON) printf("22 ") ;
                } break;
case 20:
# line 218 "y2.y"
{ 
		  if (TRACEON) printf("23 ") ;
                } break;
case 21:
# line 226 "y2.y"
{   if (TRACEON) printf("24 ") ;
		    yyval.ident=yypvt[-3].ident;
                } break;
case 22:
# line 230 "y2.y"
{   if (TRACEON) printf("25 ") ;
                    yyval.ident=install_symbol(yypvt[-0].ident);
                } break;
case 23:
# line 238 "y2.y"
{ if (TRACEON) printf("26 ") ; } break;
case 24:
# line 241 "y2.y"
{ if (TRACEON) printf("27 ") ;  } break;
case 25:
# line 248 "y2.y"
{ if (TRACEON) printf("28 ") ;  } break;
case 26:
# line 250 "y2.y"
{ if (TRACEON) printf("29 ") ;  } break;
case 27:
# line 255 "y2.y"
{ if (TRACEON) printf("30 ") ;  } break;
case 28:
# line 265 "y2.y"
{ if (TRACEON) printf("31 ") ;  } break;
case 29:
# line 267 "y2.y"
{ if (TRACEON) printf("32 ") ;  } break;
case 30:
# line 274 "y2.y"
{
	  fprintf(f_asm,"        pop  cx\n");
	  fprintf(f_asm,"   ;\n");
        } break;
case 31:
# line 283 "y2.y"
{ if (TRACEON) printf("102 ") ; } break;
case 32:
# line 285 "y2.y"
{ if (TRACEON) printf("103 ") ; } break;
case 33:
# line 290 "y2.y"
{ if (TRACEON) printf("104 ") ;
           } break;
case 34:
# line 293 "y2.y"
{ if (TRACEON) printf("106 ") ;
           } break;
case 35:
# line 298 "y2.y"
{ if (TRACEON) printf("110 ") ;} break;
# line	531 "/usr/ccs/bin/yaccpar"
	}
	goto yystack;		/* reset registers in driver code */
}

