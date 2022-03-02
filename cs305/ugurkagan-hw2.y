%{

#include <stdio.h>
void yyerror (const char *s) /* Called by yyparse on error */
{}

%}

%token tSTRING tNUM tPRINT tGET tSET tFUNCTION tRETURN tIDENT tEQUALITY tIF tGT tLT tGEQ tLEQ tINC tDEC
%start begin

%%
begin:  '[' lstmt ']'
;

stmt:		expr
	|	'[' tSET ',' tIDENT ',' expr ']'
	|       '[' tIF ',' cndt ',' '[' lstmt ']' ']'
	|       '[' tIF ',' cndt ',' '[' lstmt ']' '[' lstmt ']' ']'
	|	'[' tPRINT ',' '[' expr ']' ']'
	|	'[' tINC ',' tIDENT ']'
	|	'[' tDEC ',' tIDENT ']'
	|	'[' tRETURN ']'
	|	'[' tRETURN ',' expr ']'
;

cndt:		'[' tEQUALITY ',' expr ',' expr ']'
	|	'[' tGT ',' expr ',' expr ']'
	|	'[' tLT ',' expr ',' expr ']'
	|	'[' tGEQ ',' expr ',' expr ']'
	|	'[' tLEQ ',' expr ',' expr ']'
;

expr:		tNUM
	|	tSTRING
	|	cndt
	|	'[' tGET ',' tIDENT ']'
	|	'[' tGET ',' tIDENT ',' '[' lexpr ']' ']'
	|       '[' tFUNCTION ',' '[' lpara ']' ',' '[' lstmt ']' ']'
	|	'[' '\"' '+' '\"' ',' expr ',' expr ']'
	|	'[' '\"' '-' '\"' ',' expr ',' expr ']'
	|	'[' '\"' '*' '\"' ',' expr ',' expr ']'
	|	'[' '\"' '/' '\"' ',' expr ',' expr ']'
;

lpara:		
	|	lpara1
;

lpara1:		tIDENT 
	|	lpara1 ',' tIDENT
;

lstmt:		
	|	lstmt1
;

lstmt1:		stmt 
	|	lstmt1 stmt
;

lexpr:		
	|	lexpr1
;

lexpr1:		expr 
	|	lexpr1 ',' expr
;

%%
int main ()
{
	if (yyparse())
	{
		// parse error
		printf("ERROR\n");
		return 1;
	}
	else
	{
		// successful parsing
		printf("OK\n");
		return 0;
	}
}
