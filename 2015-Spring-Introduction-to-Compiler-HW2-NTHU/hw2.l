%{

#include <stdio.h>
#include "y.tab.h"

#define COMMENT {printf("#%d comment\n", yylineno);}

static void multi_comment(void);
extern char* yylval;

%}

letter                [a-zA-Z]
digit                 [0-9]
id                    {letter}({letter}|{digit}|"_")*
ws                    [ \t\v\f]+
newline               "\n"

int_constant          ({digit}|[1-9]{digit}+)
float_constant        (({digit}*\.{digit}+|{digit}+\.)([eE][+-]?{digit}+)?)|({digit}+[eE][+-]?{digit}+)
string_constant       (\"([^"\n])*\"|\'([^'\n])*\')

%option yylineno

%%

 /* keyword */
"auto"            {yylval = yytext; return AUTO;}
"break"           {yylval = yytext; return BREAK;}
"case"            {yylval = yytext; return CASE;}
"char"            {yylval = yytext; return CHAR;}
"const"           {yylval = yytext; return CONST;}
"continue"        {yylval = yytext; return CONTINUE;}
"default"         {yylval = yytext; return DEFAULT;}
"do"              {yylval = yytext; return DO;}
"double"          {yylval = yytext; return DOUBLE;}
"else"            {yylval = yytext; return ELSE;}
"enum"            {yylval = yytext; return ENUM;}
"extern"          {yylval = yytext; return EXTERN;}
"float"           {yylval = yytext; return FLOAT;}
"for"             {yylval = yytext; return FOR;}
"goto"            {yylval = yytext; return GOTO;}
"if"              {yylval = yytext; return IF;}
"int"             {yylval = yytext; return INT;}
"long"            {yylval = yytext; return LONG;}
"register"        {yylval = yytext; return REGISTER;}
"return"          {yylval = yytext; return RETURN;}
"short"           {yylval = yytext; return SHORT;}
"signed"          {yylval = yytext; return SIGNED;}
"sizeof"          {yylval = yytext; return SIZEOF;}
"static"          {yylval = yytext; return STATIC;}
"struct"          {yylval = yytext; return STRUCT;}
"switch"          {yylval = yytext; return SWITCH;}
"typedef"         {yylval = yytext; return TYPEDEF;}
"union"           {yylval = yytext; return UNION;}
"unsigned"        {yylval = yytext; return UNSIGNED;}
"void"            {yylval = yytext; return VOID;}
"volatile"        {yylval = yytext; return VOLATILE;}
"while"           {yylval = yytext; return WHILE;}

 /* op */
"+"               {yylval = yytext; return OP_ADD;}
"-"               {yylval = yytext; return OP_SUB;}
"*"               {yylval = yytext; return OP_MUL;}
"/"               {yylval = yytext; return OP_DIV;}
"="               {yylval = yytext; return OP_ASGN;}
"<"               {yylval = yytext; return OP_LT;}
"<="              {yylval = yytext; return OP_LTE;}
">"               {yylval = yytext; return OP_GT;}
">="              {yylval = yytext; return OP_GTE;}
"!="              {yylval = yytext; return OP_NE;}
"=="              {yylval = yytext; return OP_EQ;}
"&&"              {yylval = yytext; return OP_LAND;}
"||"              {yylval = yytext; return OP_LOR;}
"!"               {yylval = yytext; return OP_LNOT;}
"%"               {yylval = yytext; return OP_MOD;}
">>="             {yylval = yytext; return OP_RSASGN;}
"<<="             {yylval = yytext; return OP_LSASGN;}
"+="              {yylval = yytext; return OP_ADDASGN;}
"-="              {yylval = yytext; return OP_SUBASGN;}
"*="              {yylval = yytext; return OP_MULASGN;}
"/="              {yylval = yytext; return OP_DIVASGN;}
"%="              {yylval = yytext; return OP_MODASGN;}
"&="              {yylval = yytext; return OP_ANDASGN;}
"^="              {yylval = yytext; return OP_XORASGN;}
"|="              {yylval = yytext; return OP_ORASGN;}
">>"              {yylval = yytext; return OP_RS;}
"<<"              {yylval = yytext; return OP_LS;}
"&"               {yylval = yytext; return OP_BAND;}
"~"               {yylval = yytext; return OP_BNOT;}
"^"               {yylval = yytext; return OP_XOR;}
"|"               {yylval = yytext; return OP_BOR;}
"++"              {yylval = yytext; return OP_ADDADD;}
"--"              {yylval = yytext; return OP_SUBSUB;}
"->"              {yylval = yytext; return OP_ARROW;}
"."               {yylval = yytext; return OP_DOT;}

 /* symbol */
","               {yylval = yytext; return COMMA;}
";"               {yylval = yytext; return SEMICOLON;}
":"               {yylval = yytext; return COLON;}
"?"               {yylval = yytext; return QUESTION;}
"("               {yylval = yytext; return LPAREN;}
")"               {yylval = yytext; return RPAREN;}
"["               {yylval = yytext; return LSQBRT;}
"]"               {yylval = yytext; return RSQBRT;}
"{"               {yylval = yytext; return LCUBRT;}
"}"               {yylval = yytext; return RCUBRT;}


"//"[^\n]+        COMMENT;
"/*"              multi_comment();

{id}              {yylval = yytext; return ID;}
{int_constant}    {yylval = yytext; return I_CONSTANT;}
{float_constant}  {yylval = yytext; return F_CONSTANT;}
{string_constant} {yylval = yytext; return S_CONSTANT;}

{newline}         ;
{ws}              ;

%%

static void multi_comment(void) {
    int c;

    COMMENT;
    while ((c = input()) != 0) {

        if (c == '\n') {
            COMMENT;
        }

        if (c == '*') {
            while ((c = input()) == '*')
                ;

            if (c == '/')
                return;

            if (c == 0)
                break;
        }
    }
    yyerror("unterminated comment");
}
