%{
int count=1;
%}
%(write the start conditions here)

%%
/*Add the rules here*/

\n						count++; //Record lines here
int	printf("#%d: Find : %s\n",count,yytext);
.

%%
int main(){
	yylex();
	return 0;
}