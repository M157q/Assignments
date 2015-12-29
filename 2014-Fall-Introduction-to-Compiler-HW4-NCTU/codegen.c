#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "header.h"
#include "symtab.h"
#include "codegen.h"

extern char fileName[256];
extern char className[256];
extern FILE *output;

char buffer[256];
int indentLevel = 0;

void emitComment(char *str)
{
    fprintf(output, "; %s\n", str);
    return;
}

void emitHead()
{
    emitComment(fileName);
    sprintf(buffer, ".class public %s", className);
    emitLine(buffer);
    emitLine(".super java/lang/Object");
    emitLineBreak();
    return;
}

void pushIndent()
{
    indentLevel++;
    return;
}

void popIndent()
{
    indentLevel--;
    return;
}

void emitLine(char *str)
{
    char s[256] = {0};
    char spaces[indentLevel*4];
    memset(spaces, ' ', indentLevel*4);
    spaces[indentLevel*4] = '\0';
    strncat(s, spaces, sizeof(s));
    strncat(s, str, sizeof(s));
    fprintf(output, "%s\n", s);
    return;
}

void emitLineBreak()
{
    fprintf(output, "\n");
    return;
}
