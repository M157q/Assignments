#ifndef _CODEGEN_H_
#define _CODEGEN_H_

void emitComment( char *str );
void emitHead();
void pushIndent();
void popIndent();
void emitLine(char *str);
void emitLineBreak();

#endif
