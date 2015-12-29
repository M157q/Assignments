%{
#include "y.tab.h"
#include <string.h>

#define MAX_LINE_LENGTH 257
#define MAX_ID_LENGTH 257
#define MAX_STRING_LENGTH 257
#define LIST                strlcat(buf, yytext, MAX_LINE_LENGTH)
#define token(t)            {LIST; if (Opt_Token) printf("<%s>\n", #t);}
#define tokenInteger(t, i)  {LIST; if (Opt_Token) printf("<%s:%d>\n", t, i);}
#define tokenString(t, s)   {LIST; if (Opt_Token) printf("<%s:%s>\n", t, s);}

int Opt_Source = 1;
int Opt_Token = 1;
int Opt_Statistic =1;
int linenum = 1;
int Last_State = 0;
char buf[MAX_LINE_LENGTH];
char strContent[MAX_STRING_LENGTH];
typedef struct ids{
    char id_name[MAX_ID_LENGTH];
    int freq;
    struct ids *next;
} id;
id *id_head;
void set(id **, char *);
id *new_id();

%}

whitespace  [ \t]+

digit       [0-9]
integer     [1-9]{digit}*|[0]
octal       [0][0-7]+
float       {integer}[\.]{digit}+
scientific  ({integer}|{float})[eE][\+\-]?[0-9]+

%x PRAGMA
%x SOURCE
%x TOKEN
%x STATISTIC
%x OTHER
%x STR
%x STR_ESCAPE
%x COMMENT

%%
<INITIAL>{whitespace}     { LIST; }

^#pragma                { LIST; BEGIN PRAGMA;    }
<PRAGMA>"source"        { LIST; BEGIN SOURCE;    }
<PRAGMA>"token"         { LIST; BEGIN TOKEN;     }
<PRAGMA>"statistic"     { LIST; BEGIN STATISTIC; }
<PRAGMA>{whitespace}    { LIST; }
<PRAGMA>[^\t ]          { fprintf(stderr, "Error at line %d: %s\n", linenum, yytext); exit(1); }

<SOURCE>"on"            { LIST; Opt_Source = 1; BEGIN OTHER; }
<SOURCE>"off"           { LIST; Opt_Source = 0; BEGIN OTHER; }
<SOURCE>{whitespace}    { LIST; }
<SOURCE>[^\t ]          { fprintf(stderr, "Error at line %d: %s\n", linenum, yytext); exit(1); }

<TOKEN>"on"             { LIST; Opt_Token = 1; BEGIN OTHER; }
<TOKEN>"off"            { LIST; Opt_Token = 0; BEGIN OTHER; }
<TOKEN>{whitespace}     { LIST; }
<TOKEN>[^\t ]           { fprintf(stderr, "Error at line %d: %s\n", linenum, yytext); exit(1); }

<STATISTIC>"on"         { LIST; Opt_Statistic = 1; BEGIN OTHER; }
<STATISTIC>"off"        { LIST; Opt_Statistic = 0; BEGIN OTHER; }
<STATISTIC>{whitespace} { LIST; }
<STATISTIC>[^\t ]       { fprintf(stderr, "Error at line %d: %s\n", linenum, yytext); exit(1); }

<OTHER>\/\/.*           { LIST; BEGIN INITIAL; }
<OTHER>"/*"             { LIST; Last_State = OTHER; BEGIN COMMENT; }
<OTHER>[^\n]            { fprintf(stderr, "Error at line %d: %s\n", linenum, yytext); exit(1); }
<OTHER>\n {
    LIST;
    if (Opt_Source) printf("%d:%s\n", linenum, buf);
    linenum++;
    buf[0] = '\0';
    BEGIN INITIAL;
}


;delimiter
"(" { tokenString("delim", "("); return LPAREN;     }
")" { tokenString("delim", ")"); return RPAREN;     }
"," { tokenString("delim", ","); return COMMA;      }
";" { tokenString("delim", ";"); return SEMICOLON;  }
"[" { tokenString("delim", "["); return LSQBRT;     }
"]" { tokenString("delim", "]"); return RSQBRT;     }
"{" { tokenString("delim", "{"); return LCUBRT;     }
"}" { tokenString("delim", "}"); return RCUBRT;     }

;op
"+"  { token("+");  return ADD;    }
"-"  { token("-");  return SUB;    }
"*"  { token("*");  return MUL;    }
"/"  { token("/");  return DIV;    }
"%"  { token("%");  return MOD;    }
"="  { token("=");  return ASSIGN; }
"<"  { token("<");  return LT;     }
"<=" { token("<="); return LTE;    }
"!=" { token("!="); return NE;     }
">=" { token(">="); return GTE;    }
">"  { token(">");  return GT;     }
"==" { token("=="); return EQ;     }
"&&" { token("&&"); return AND;    }
"||" { token("||"); return OR;     }
"!"  { token("!");  return NOT;    }

;keywords
read        { tokenString("KW", yytext); return READ;       }
boolean     { tokenString("KW", yytext); return BOOLEAN;    }
while       { tokenString("KW", yytext); return WHILE;      }
do          { tokenString("KW", yytext); return DO;         }
if          { tokenString("KW", yytext); return IF;         }
else        { tokenString("KW", yytext); return ELSE;       }
true        { tokenString("KW", yytext); return TRUE;       }
false       { tokenString("KW", yytext); return FALSE;      }
for         { tokenString("KW", yytext); return FOR;        }
int         { tokenString("KW", yytext); return INT;        }
print       { tokenString("KW", yytext); return PRINT;      }
bool        { tokenString("KW", yytext); return BOOL;       }
void        { tokenString("KW", yytext); return VOID;       }
float       { tokenString("KW", yytext); return FLOAT;      }
double      { tokenString("KW", yytext); return DOUBLE;     }
string      { tokenString("KW", yytext); return STRING;     }
continue    { tokenString("KW", yytext); return CONTINUE;   }
break       { tokenString("KW", yytext); return BREAK;      }
return      { tokenString("KW", yytext); return RETURN;     }
const       { tokenString("KW", yytext); return CONST;     }

{integer}       { tokenString("integer", yytext);    return INT;    }
{float}         { tokenString("float", yytext);      return FLOAT;  }
{scientific}    { tokenString("scientific", yytext); return SCIENT; }

;string
"\""            { LIST; strContent[0] = '\0'; BEGIN STR; }
<STR>"\\"       { LIST; BEGIN STR_ESCAPE; }
<STR_ESCAPE>\"  { LIST; strlcat (strContent, "\"", MAX_STRING_LENGTH); BEGIN STR; }
<STR_ESCAPE>n   { LIST; strlcat( strContent, "\n", MAX_STRING_LENGTH); BEGIN STR; }
<STR_ESCAPE>t   { LIST; strlcat( strContent, "\t", MAX_STRING_LENGTH); BEGIN STR; }
<STR_ESCAPE>\\  {
        LIST;
        strlcat( strContent, "\\", MAX_STRING_LENGTH);
        BEGIN STR;
}
<STR_ESCAPE>\n  { fprintf(stderr, "Error at line %d: %s\n", linenum, yytext); exit(1); }
<STR_ESCAPE>[^\"nt\\] {
        LIST;
        strlcat( strContent, "\\", MAX_STRING_LENGTH);
        strlcat( strContent, yytext, MAX_STRING_LENGTH);
        BEGIN STR;
    }
<STR>"\n"       { fprintf(stderr,"Error at line %d: %s\n",linenum,yytext); exit(1); }
<STR>\"         { tokenString("string", strContent); BEGIN INITIAL; return STRING;  }
<STR>[^\\\n\"]  { LIST; strlcat( strContent, yytext, MAX_STRING_LENGTH);            }

;comment
"/*"            { LIST; Last_State = INITIAL; BEGIN COMMENT; }
<COMMENT>"\n"   { LIST; if (Opt_Source) printf("%d:%s\n", linenum, buf); linenum++; buf[0] = '\0'; }
<COMMENT>.      { LIST; }
<COMMENT>"*/"   { LIST; BEGIN Last_State; }
\/\/.*          { LIST; }

;other
\n  { LIST; if (Opt_Source) printf("%d:%s\n", linenum, buf); linenum++; buf[0] = '\0'; }

[a-zA-Z_][a-zA-Z0-9_]{0,255} {
        if(Opt_Statistic) {
            set(&id_head, yytext);
        }
        tokenString("id", yytext);
        return ID;
}
.   { fprintf(stderr,"Error at line %d: %s\n",linenum, yytext); exit(1); }

%%

int main( int argc, char **argv )
{

    if( argc == 1 ) {
        yyin = stdin;
    }
    else if( argc == 2 ) {
        FILE *fp = fopen( argv[1], "r" );
        if( fp == NULL ) {
                fprintf( stderr, "Open file error\n" );
                exit(-1);
        }
        yyin = fp;
    }
    else {
        fprintf( stderr, "Usage: ./scanner [filename]\n" );
        exit(0);
    }

    id_head = NULL;
    yylex();

    if(Opt_Statistic) {
        printf("frequencies of identifiers:\n");
        id *offset = id_head;
        while(offset) {
                printf("%s\t%d\n",offset->id_name, offset->freq);
                offset = offset->next;
        }
    }
    exit(0);
}

void set(id **head, char *yytext) {
    id *offset = *head;
    id *prev = NULL;
    if(offset == NULL) {
        *head = new_id();
        strncpy((*head)->id_name, yytext,strlen(yytext));
        (*head)->freq = 1;
    }
    else {
        while(offset) {
            if(!strncmp(offset->id_name, yytext,
                ( strlen(yytext) >= strlen(offset->id_name)
                ? strlen(yytext)
                : strlen(offset->id_name) ))
            ) {
                offset->freq+=1;
                break;
            }
            prev = offset;
            offset = offset -> next;
        }
        if(!offset) {
            prev->next = new_id();
            strncpy(prev->next->id_name, yytext, strlen(yytext));
            prev->next->freq+=1;
        }
    }
}

id *new_id() {
    id *temp = (id *)malloc(sizeof(id));
    temp->next = NULL;
    memset(temp->id_name, 0, 256);
    temp->freq = 0;
    return temp;
}
