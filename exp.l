%{
#include <stdio.h>
#include "exp.tab.h"
void yyerror(const char* s);
#define YY_DECL extern int yylex()
%}
		 // creating defintions 
digit [0-9]+ 	
char [a-zA-Z]
op [+\-*/%]

		// these are the tokens we use for grammar 

%%
{digit}	printf("%s",yytext); return (DIGIT);
{char}	printf("%s",yytext); return (CHAR);
{op}	printf("%s",yytext); return (OP);
"("	printf("%s",yytext); return (LEFT_PAR);
")"	printf("%s",yytext); return (RIGHT_PAR);
";"	printf("%s",yytext); return (SEMICOLON);
"="	printf("%s",yytext); return (EQUAL);
" "	printf("%s",yytext); return (SPACE);
"\n"	printf("%s",yytext); return (NEWLINE);
.	yyerror("unexpected token"); return OTHER;
%%

		// error message 

void ERROR(){
	printf(" OTHER");
}
