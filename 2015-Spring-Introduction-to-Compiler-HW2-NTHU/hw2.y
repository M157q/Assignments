%{

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define YYSTYPE char*
#define PTRACE(msg, s) {printf("#%d %s : %s\n", yylineno, msg, s);}

extern FILE *yyin;              /* declared in lex */
extern char *yytext;            /* declared in lex */
extern int yylineno;
extern int yyparse();           /* declared by yacc */
//int yydebug = 1;

%}

%token ID I_CONSTANT F_CONSTANT S_CONSTANT
%token AUTO BREAK CASE CHAR CONST CONTINUE DEFAULT DO DOUBLE ELSE ENUM EXTERN FLOAT FOR GOTO IF INT LONG REGISTER RETURN SHORT SIGNED SIZEOF STATIC STRUCT SWITCH TYPEDEF UNION UNSIGNED VOID VOLATILE WHILE
%token OP_ADD OP_SUB OP_MUL OP_DIV OP_ASGN OP_LT OP_LTE OP_GT OP_GTE OP_NE OP_EQ OP_LAND OP_LOR OP_LNOT OP_MOD OP_RSASGN OP_LSASGN OP_ADDASGN OP_SUBASGN OP_MULASGN OP_DIVASGN OP_MODASGN OP_ANDASGN OP_XORASGN OP_ORASGN OP_RS OP_LS OP_BAND OP_BNOT OP_BOR OP_XOR OP_ADDADD OP_SUBSUB OP_ARROW OP_DOT
%token COMMA SEMICOLON COLON QUESTION LPAREN RPAREN LSQBRT RSQBRT LCUBRT RCUBRT

/*%nonassoc ASSIGN LT LTE NEQ GT GTE EQ*/
/*%left  AND OR NOT ADD SUB MUL DIV MOD*/

%start program

%%

program
    : declaration_list definition_list
        {
            printf("program -> declaration_list definition_list\n");
        }
    ;

declaration_list
    : declaration
        {
            printf("declaration_list -> declaration\n");
        }
    | declaration_list declaration
        {
            printf("declaration_list -> declaration_list declaration\n");
        }
    ;

declaration
    : function_declaration SEMICOLON
        {
            printf("declaration -> function_declaration ';'\n");
        }
    | var_declaration SEMICOLON
        {
            printf("declaration -> var_declaration ';'\n");
        }
    ;

function_declaration
    : type ID LPAREN parameter_list RPAREN
        {
            PTRACE("data type", $5);
            printf("function_declaration -> type ID '(' parameter_list ')'\n");
        }
    ;

var_declaration
    : type ID
        {
            printf("var_declaration -> type ID\n");
        }
    | type ID OP_ASGN constant
        {
            printf("var_declaration -> type ID '=' constant\n");
        }
    ;

constant
    : I_CONSTANT
        {
            printf("constant -> I_CONSTANT\n");
        }
    | F_CONSTANT
        {
            printf("constant -> F_CONSTANT\n");
        }
    | S_CONSTANT
        {
            printf("constant -> S_CONSTANT\n");
        }

parameter_list
    : parameter
        {
            printf("parameter_list -> parameter\n");
        }
    | parameter_list COMMA parameter
        {
            printf("parameter_list -> parameter_list ',' parameter\n");
        }
    ;

parameter
    : type ID
        {
            printf("parameter -> type ID\n");
        }
    ;

type
    : INT { printf("type -> INT\n"); }
    | LONG { printf("type -> LONG\n"); }
    | FLOAT { printf("type -> FLAT\n"); }
    | DOUBLE { printf("type -> DOUBLE\n"); }
    | CHAR { printf("type -> CHAR\n"); }
    ;

definition_list
    : definition
        {
            printf("definition_list -> definition\n");
        }
    | definition_list definition
        {
            printf("definition_list -> definition_list definition\n");
        }
    ;

definition
    : type ID LPAREN RPAREN compound
        {
            printf("definition -> ID '(' ')' compound\n");
        }
    | type ID LPAREN parameter_list RPAREN compound
        {
            printf("definition -> ID '(' parameter_list ')' compound\n");
        }
    ;

compound
    : LCUBRT RCUBRT
        {
            printf("compound -> '{' '}'\n");
        }
    | LCUBRT statement_list RCUBRT
        {
            printf("compound -> '{' statement_list '}'\n");
        }
    | LCUBRT declaration_list RCUBRT
        {
            printf("compound -> '{' declaration_list '}'\n");
        }
    | LCUBRT declaration_list statement_list RCUBRT
        {
            printf("compound -> '{' declaration_list statement_list '}'\n");
        }
    ;

statement_list
    : statement
        {
            printf("statement_list -> statement\n");
        }
    | statement_list statement
        {
            printf("statement_list -> statement_list statement\n");
        }
    ;

statement
    : expression_statement
        {
            printf("statement -> expression_statement\n");
        }
    | jump_statement
        {
            printf("statement_list -> jump_statement\n");
        }
    ;

expression_statement
    : SEMICOLON
        {
            printf("expression_statement -> ';'\n");
        }
    | expression SEMICOLON
        {
            printf("expression_statement -> expression ';'\n");
        }
    ;

expression
    : assignment_expression
        {
            printf("expression -> assignment_expression\n");
        }
    | expression COMMA assignment_expression
        {
            printf("expression -> expression ',' assignment_expression\n");
        }
    ;

assignment_expression
    : conditional_expression 
        {
            printf("assignment_expression -> conditional_expression\n");
        }
    | ID OP_ASGN conditional_expression
        {
            printf("assignment_expression -> ID '=' conditional_expression\n");
        }
    | ID OP_ASGN ID LPAREN argument_list RPAREN
        {
            printf("assignment_expression -> ID '(' argument_list ')'\n");
        }
    ;

argument_list
    : cast_expression
        {
            printf("argument_list -> cast_expression\n");
        }
    | argument_list COMMA cast_expression
        {
            printf("argument_list -> argument_list ',' cast_expression\n");
        }
    ;

conditional_expression
    : logical_or_expression
    | logical_or_expression QUESTION expression COLON conditional_expression
    ;

logical_or_expression
    : logical_and_expression
    | logical_or_expression OP_LOR logical_and_expression
    ;

logical_and_expression
    : inclusive_or_expression
    | logical_and_expression OP_LAND inclusive_or_expression
    ;

inclusive_or_expression
    : exclusive_or_expression
    | inclusive_or_expression OP_BOR exclusive_or_expression
    ;

exclusive_or_expression
    : and_expression
    | exclusive_or_expression OP_XOR and_expression
    ;

and_expression
    : equality_expression
    | and_expression OP_BAND equality_expression
    ;

equality_expression
    : relational_expression
    | equality_expression OP_EQ relational_expression
    | equality_expression OP_NE relational_expression
    ;

relational_expression
    : shift_expression
    | relational_expression OP_LT shift_expression
    | relational_expression OP_GT shift_expression
    | relational_expression OP_LTE shift_expression
    | relational_expression OP_GTE shift_expression
    ;

shift_expression
    : additive_expression
    | shift_expression OP_LS additive_expression
    | shift_expression OP_RS additive_expression
    ;

additive_expression
    : multiplicative_expression
    | additive_expression OP_ADD multiplicative_expression
        {
            printf("additive_expression -> additive_expression '+' multiplicative_expression\n");
        }
    | additive_expression OP_SUB multiplicative_expression
        {
            printf("additive_expression -> additive_expression '-' multiplicative_expression\n");
        }
    ;

multiplicative_expression
    : cast_expression
    | multiplicative_expression OP_MUL cast_expression
        {
            printf("multiplicative_expression -> multiplicative_expression '*' cast_expression\n");
        }
    | multiplicative_expression OP_DIV cast_expression
        {
            printf("multiplicative_expression -> multiplicative_expression '/' cast_expression\n");
        }
    | multiplicative_expression OP_MOD cast_expression
        {
            printf("multiplicative_expression -> multiplicative_expression '%%' cast_expression\n");
        }
    ;

cast_expression
    : ID
        {
            printf("cast_expression -> ID\n");
        }
    | constant
        {
            printf("cast_expression -> constant\n");
        }
    | LPAREN expression  RPAREN
        {
            printf("cast_expression -> '(' expression ')'\n");
        }
    ;

jump_statement
    : GOTO ID SEMICOLON
    | CONTINUE SEMICOLON 
    | BREAK SEMICOLON 
    | RETURN SEMICOLON
        {
            printf("jump_statement -> 'return' ';'\n");
        }
    | RETURN expression SEMICOLON 
        {
            printf("jump_statement -> 'return' expression ';'\n");
        }
    ;
    

%%

void yyerror(const char *str)
{
    fprintf(stderr, "error: %s\n", str);
    fprintf(stderr, "in line %d: \"%s\"\n", yylineno, yytext);
}

int main(void) {
    yyparse();
}
