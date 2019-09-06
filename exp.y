%{
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#define YYSTYPE double
extern char * yytext;
extern  int yylex();
extern  FILE *yyin;
char errortok;
const char * firsterror;
int main(int argc, char **argv);
void yyerror(const char* s);

%}

// declaring the tokens
%token DIGIT CHAR SPACE OP LEFT_PAR RIGHT_PAR SEMICOLON EQUAL OTHER NEWLINE ID 


%start input


 // the start of grammar rules
%%
input:
	validline
      	|input validline	
        ;
 		 // these are correct grammar statements
validline:	assignment NEWLINE		{printf("Correct Statement \n\n" );}
		| assignment SPACE NEWLINE	{printf("Correct Statement \n\n" );}
                | expression NEWLINE 		{printf("Correct Statement \n\n" );} 
		| expression SPACE NEWLINE	{printf("Correct Statement \n\n" );}
		| NEWLINE			{printf("Correct Statement \n\n" );}
                | error NEWLINE  		{printf("Fail invalid statement: %s wrong token: %c \n\n",firsterror, errortok );} 		
                ;
assignment:	id SPACE EQUAL SPACE expression SPACE SEMICOLON
		;
		
		// these are combinations that are applicable 

expression:	id SPACE OP SPACE id
		| expression SPACE OP SPACE id 
                | LEFT_PAR expression RIGHT_PAR SPACE OP SPACE id
		| LEFT_PAR SPACE expression SPACE RIGHT_PAR SPACE OP SPACE id
		| LEFT_PAR SPACE expression SPACE RIGHT_PAR SPACE OP SPACE LEFT_PAR SPACE expression SPACE RIGHT_PAR
		| LEFT_PAR expression RIGHT_PAR OP LEFT_PAR SPACE OP SPACE LEFT_PAR expression RIGHT_PAR
		| id SPACE OP SPACE LEFT_PAR expression RIGHT_PAR
		| id SPACE OP SPACE LEFT_PAR expression SPACE RIGHT_PAR
		| id SPACE OP SPACE LEFT_PAR SPACE expression SPACE RIGHT_PAR  
                ;
	// defining id
id:     CHAR		
	| id CHAR
        | id DIGIT
        ;
%%

	// make the error message saved as global variable 
void yyerror(const char *s){
	firsterror = s;
	errortok = yytext[0];	// mark the token there is 
}

extern int yywrap(){
	return(1==1);
}
 		// main function which opens file 
int main(int argc, char **argv){
        FILE *myfile = fopen("ex.txt", "r");
        if(!myfile){			// if not file print out error
                printf("file couldnt be opened \n");
                return -1;
                }
                yyin = myfile; 
		yyparse(); 		// parse through the file
               while(yylex());
}

