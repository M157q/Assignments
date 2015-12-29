%{
#include "y.tab.h"

#define LIST                { strncat(buf, yytext, sizeof(buf) - strlen(buf) - 1); }
#define token(t)            { LIST; if (Opt_Token) printf("<\"%s\">\n", t); }
#define tokenString(t, s)   { LIST; if (Opt_Token) printf("<%s:%s>\n", t, s); }
#define MAX_LINE_LENGTH 257
#define MAX_ID_LENGTH 257
#define ID_TABLE_SIZE 1000

int Opt_Source = 1;
int Opt_Token = 1;
int Opt_Statistic = 1;
int linenum = 1;
char buf[MAX_LINE_LENGTH];

struct id_node{
     char name[(MAX_ID_LENGTH-1)];
     int counter;
} id_table[ID_TABLE_SIZE] ;
int id_count = 1;
int lookupIDTable(char* name);
void insertIDTable(char* name, int id_offset);
void printIDTable();
%}

WHITESPACE [ \t]+
DIGIT      [0-9]
LETTER     [a-zA-Z]
ID         {LETTER}({LETTER}|{DIGIT}|"_")*
DELIMITER  (,|;|\(|\)|\[|\]|\{|\})
STRING     "\""([^"\\]|\\.)*"\""
OPERATOR   (\+|\-|\*|\/|%|=|<|<=|!=|>=|>|==|&&|\|\||!)
INT        ({DIGIT}|[1-9]{DIGIT}+)
FLOAT      {DIGIT}+\.{DIGIT}+
EXP        ([eE][+-]?{DIGIT}+)
SCIENTIFIC (({FLOAT}?{EXP})|{DIGIT}+{EXP})
KEYWORD (while|do|if|else|true|false|for|int|print|const|read|boolean|bool|void|float|double|string|continue|break|return)

%Start PRAGMA
%Start COMMENT
%Start MULTI_COMMENT
%Start STRING

%%

 /* parse pragma */
<INITIAL>"#pragma " {
    LIST;
    BEGIN PRAGMA;
}
<PRAGMA>"source off" {
    Opt_Source = 0;
    LIST;
    BEGIN INITIAL;
}
<PRAGMA>"source on" {
    Opt_Source = 1;
    LIST;
    BEGIN INITIAL;
}
<PRAGMA>"token off" {
    Opt_Token = 0;
    LIST;
    BEGIN INITIAL;
}
<PRAGMA>"token on" {
    Opt_Token = 1;
    LIST;
    BEGIN INITIAL;
}
<PRAGMA>"statistic off" {
    Opt_Statistic = 0;
    LIST;
    BEGIN INITIAL;
}
<PRAGMA>"statistic on" {
    Opt_Statistic = 1;
    LIST;
    BEGIN INITIAL;
}

 /* single line comment */
<INITIAL>"//" {
    LIST;
    BEGIN COMMENT;
}
<COMMENT>. LIST;
<COMMENT>"\n" {
    BEGIN INITIAL;
    REJECT;
}

 /* multi line comments */
<INITIAL>"/*" {
    LIST;
    BEGIN MULTI_COMMENT;
}
<MULTI_COMMENT>. LIST;
<MULTI_COMMENT>"*/" {
    LIST;
    BEGIN INITIAL;
}

 /* keyword */
<INITIAL>{KEYWORD} {
    tokenString("KW", yytext);
}

 /* identifier */
<INITIAL>{ID} {
    tokenString("id", yytext);
    int id_offset = lookupIDTable(yytext);
    if (id_offset) {
        strcpy(id_table[id_offset].name, yytext);
        id_table[id_offset].counter += 1;
    }
    else {
        insertIDTable(yytext, id_count);
        id_count += 1;
    }
}

 /* delimiter */
<INITIAL>{DELIMITER} {
    tokenString("delim", yytext);
}

 /* string */
<INITIAL>{STRING} {
    char _yytext[256];
    char str[256];
    char *token;
    char *s = "\\\"";
    strcpy(_yytext, yytext);
    strcpy(str, "");
    token = strtok(_yytext, s);
    while (token != NULL) {
        strcat(str, token);
        strcat(str, "\"");
        token = strtok(NULL, s);
    }
    str[strlen(str)-1] = '\0';
    tokenString("string", str);
}

 /* operator */
<INITIAL>{OPERATOR} {
    token(yytext);
}

 /* integer */
<INITIAL>{INT} {
    tokenString("integer", yytext);
}

 /* scientific */
<INITIAL>{SCIENTIFIC} {
    tokenString("scientific", yytext);
}

 /* float */
<INITIAL>{FLOAT} {
    tokenString("float", yytext);
}


 /* line feed */
\n {
    LIST;
    if (Opt_Source)
        printf("%d:%s\n", linenum, buf);
    ++linenum;
    buf[0] = '\0';
}

<INITIAL>{WHITESPACE} LIST;

 /* Unrecognized charater */
. {
    fprintf(stderr, "Error at line %d: %s\n", linenum, yytext);
    exit(1);
}

%%

int main(int argc, char **argv) {
    if (argc >= 2) {
        yyin = fopen(argv[1], "r");
        if (NULL == yyin) {
            fprintf(stderr, "Cannot open: %s\n", argv[1]);
            exit(-1);
        }
    }
    else {
        yyin = stdin;
    }

    yylex();

    if (Opt_Statistic) {
        printIDTable();
    }

    exit(0);
}

int lookupIDTable(char *id_name) {
    int i;
    for (i = 1; i < ID_TABLE_SIZE; i++) {
        if (strcmp(id_table[i].name, id_name) == 0)
            return i;
    }
    return 0;
}

void insertIDTable(char *id_name, int id_offset) {
    struct id_node n;
    strcpy(n.name, id_name);
    n.counter = 1;
    id_table[id_offset] = n;
}

void printIDTable() {
    printf("frequencies of identifiers:\n");
    int i;
    for (i = 1; i < ID_TABLE_SIZE; i++) {
        if (id_table[i].counter == 0) break;
        printf("%s\t%d\n", id_table[i].name, id_table[i].counter);
    }
}
