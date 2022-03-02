%{
#include <stdio.h>
#include "ugurkagan-hw3.h"

TreeNode * mkEXPR3 ( TreeNode *, TreeNode *, OpType);    
TreeNode * mkEXPR1 ( TreeValue *, ConstType );   
void printTree ( TreeNode *);
TreeValue * mkTypeStr ( info_str );
TreeValue * mkTypeInt ( info_int );
TreeValue * mkTypeReal ( info_real );
TreeValue * mkTypeError ( int );

void yyerror (const char *s) 
{}
%}

%union {
		info_int value;
		info_real real_value;
		info_str str_value;
		TreeNode *treePtr;
	}

%token tADD tSUB tMUL tDIV tSTRING tREAL tINT tPRINT tGET tSET tFUNCTION tRETURN tIDENT tEQUALITY tIF tGT tLT tGEQ tLEQ tINC tDEC

%start prog

%type<value> tINT
%type<real_value> tREAL 
%type<str_value> tSTRING
%type<treePtr> const_expr

%%
prog:		'[' stmtlst ']'
;

stmtlst:	stmtlst stmt |
;

stmt:		setStmt | if | print | unaryOperation | expr | returnStmt
;

getExpr:	'[' tGET ',' tIDENT ',' '[' exprList ']' ']'
		| '[' tGET ',' tIDENT ',' '[' ']' ']'
		| '[' tGET ',' tIDENT ']'
;

setStmt:	'[' tSET ',' tIDENT ',' expr ']'
;

if:		'[' tIF ',' condition ',' '[' stmtlst ']' ']'
		| '[' tIF ',' condition ',' '[' stmtlst ']' '[' stmtlst ']' ']'
;

print:		'[' tPRINT ',' '[' expr ']' ']'
;

operation:	'[' tADD ',' nonConstExpr ',' nonConstExpr ']'
		| '[' tSUB ',' nonConstExpr ',' nonConstExpr ']'
		| '[' tMUL ',' nonConstExpr ',' nonConstExpr ']'
		| '[' tDIV ',' nonConstExpr ',' nonConstExpr ']'
		| '[' tADD ',' const_expr ',' nonConstExpr ']'
                | '[' tSUB ',' const_expr ',' nonConstExpr ']'		
                | '[' tMUL ',' const_expr ',' nonConstExpr ']'	
                | '[' tDIV ',' const_expr ',' nonConstExpr ']'		
		| '[' tADD ',' nonConstExpr ',' const_expr ']'		
		| '[' tSUB ',' nonConstExpr ',' const_expr ']'		
		| '[' tMUL ',' nonConstExpr ',' const_expr ']'		
		| '[' tDIV ',' nonConstExpr ','	const_expr ']'		
;	
nonConstExpr:	getExpr | function | operation | condition
;

unaryOperation: '[' tINC ',' tIDENT ']'
		| '[' tDEC ',' tIDENT ']'
;

expr:		const_expr { printTree( $1 ); } 
		| nonConstExpr
;

function:	 '[' tFUNCTION ',' '[' parametersList ']' ',' '[' stmtlst ']' ']'
		| '[' tFUNCTION ',' '[' ']' ',' '[' stmtlst ']' ']'
;

condition:	'[' tEQUALITY ',' expr ',' expr ']'
		| '[' tGT ',' expr ',' expr ']'
		| '[' tLT ',' expr ',' expr ']'
		| '[' tGEQ ',' expr ',' expr ']'
		| '[' tLEQ ',' expr ',' expr ']'
;

returnStmt:	'[' tRETURN ',' expr ']'
		| '[' tRETURN ']'
;

parametersList: parametersList ',' tIDENT | tIDENT
;

exprList:	exprList ',' expr | expr
;

const_expr:	tSTRING		{ 	TreeValue * temp = mkTypeStr( $1 );
					$$ = mkEXPR1 ( temp, STR ); }
		| tINT		{       TreeValue * temp = mkTypeInt( $1 );
					$$ = mkEXPR1 ( temp, INT ); }
		| tREAL		{       TreeValue * temp = mkTypeReal( $1 );
					$$ = mkEXPR1 ( temp, REAL ); } 
		| '[' tADD ',' const_expr ',' const_expr ']'	{ $$ = mkEXPR3 ( $4 , $6 , ADD ); }
                | '[' tSUB ',' const_expr ',' const_expr ']'	{ $$ = mkEXPR3 ( $4 , $6 , SUB ); }
                | '[' tMUL ',' const_expr ',' const_expr ']'	{ $$ = mkEXPR3 ( $4 , $6 , MUL ); }
                | '[' tDIV ',' const_expr ',' const_expr ']'    { $$ = mkEXPR3 ( $4 , $6 , DIV ); }
%%

void printTree ( TreeNode * t) {
	
     	if ( (t->thisNodeType == EXPR3) && (t->exprNodePtr->expr3.type == ERROR) ) {
                printf("Type mismatch on %d \n", t->exprNodePtr->expr3.value->infoNodePtr->error_line);
	}
	if (t->thisNodeType==EXPR1)
		;
	else {
		if( t->exprNodePtr->expr3.type == INT ){
			printf("Result of expression on %d is (%d)\n", t->exprNodePtr->expr3.value->infoNodePtr->infInt.line_no, t->exprNodePtr->expr3.value->infoNodePtr->infInt.value);
		}
		else if( t->exprNodePtr->expr3.type == REAL ){
			float temp = t->exprNodePtr->expr3.value->infoNodePtr->infReal.value * 10;
			int floor = (int)(t->exprNodePtr->expr3.value->infoNodePtr->infReal.value * 10);
			int dec_point = floor % 10;
			if(dec_point >= 0){
				if( temp - (float)floor < 0.5)
					printf("Result of expression on %d is (%d.%d)\n", t->exprNodePtr->expr3.value->infoNodePtr->infReal.line_no, (int) (floor) / 10, dec_point);
				else{
					dec_point++;
					printf("Result of expression on %d is (%d.%d)\n", t->exprNodePtr->expr3.value->infoNodePtr->infReal.line_no, (int) (floor) / 10, dec_point);
				}
			}
			else{
				if( (float)floor - temp > 0.5){
					dec_point--;
					printf("Result of expression on %d is (%d.%d)\n", t->exprNodePtr->expr3.value->infoNodePtr->infReal.line_no, (int) (floor) / 10, -1 * dec_point);
				}
				else{
					printf("Result of expression on %d is (%d.%d)\n", t->exprNodePtr->expr3.value->infoNodePtr->infReal.line_no, (int) (floor) / 10, -1 * dec_point);
				}
			}
		}
		else if( t->exprNodePtr->expr3.type == STR ){
			printf("Result of expression on %d is (%s)\n",  t->exprNodePtr->expr3.value->infoNodePtr->infStr.line_no, t->exprNodePtr->expr3.value->infoNodePtr->infStr.value);		
		}
	}
}

TreeNode * mkEXPR3 ( TreeNode *left, TreeNode *right, OpType operator) {
	TreeNode * ret = (TreeNode *)malloc (sizeof(TreeNode));
	ret->thisNodeType = EXPR3;
	ret->exprNodePtr = (ExprNode *)malloc (sizeof(ExprNode));
	ret->exprNodePtr->expr3.operator = operator;
	ret->exprNodePtr->expr3.leftChild = left;
	ret->exprNodePtr->expr3.rightChild = right;
	ret->exprNodePtr->expr3.type = ERROR;
	ConstType left_type, right_type;
	float left_real, right_real;
	int left_int, right_int;
	char * left_str; 
	char * right_str;
	int line = 0;
	
	if (left->thisNodeType == EXPR1 && right->thisNodeType == EXPR1 ) {		
		if(left->exprNodePtr->expr1.type != ERROR && right->exprNodePtr->expr1.type != ERROR)
		{
			if( (left->exprNodePtr->expr1.type == INT) && (right->exprNodePtr->expr1.type == INT) ) {
				line = left->exprNodePtr->expr1.value->infoNodePtr->infInt.line_no;
				ret->exprNodePtr->expr3.type = INT;
				left_int = left->exprNodePtr->expr1.value->infoNodePtr->infInt.value;
				right_int = right->exprNodePtr->expr1.value->infoNodePtr->infInt.value;
				left_type = INT;
				right_type = INT;
			}
			else if( (left->exprNodePtr->expr1.type == INT) && (right->exprNodePtr->expr1.type == REAL) ){
				line = left->exprNodePtr->expr1.value->infoNodePtr->infInt.line_no;
				ret->exprNodePtr->expr3.type = REAL;
				left_int = left->exprNodePtr->expr1.value->infoNodePtr->infInt.value;
				right_real = right->exprNodePtr->expr1.value->infoNodePtr->infReal.value;
				left_type = INT;
				right_type = REAL;
			}
			else if( (left->exprNodePtr->expr1.type == REAL) && (right->exprNodePtr->expr1.type == INT) ) {
				line = left->exprNodePtr->expr1.value->infoNodePtr->infReal.line_no;
				ret->exprNodePtr->expr3.type = REAL;
				left_real = left->exprNodePtr->expr1.value->infoNodePtr->infReal.value;
				right_int = right->exprNodePtr->expr1.value->infoNodePtr->infInt.value;
				left_type = REAL;
				right_type = INT;
			}
			else if( (left->exprNodePtr->expr1.type == REAL) && (right->exprNodePtr->expr1.type == REAL) ) {
				line = left->exprNodePtr->expr1.value->infoNodePtr->infReal.line_no;
				ret->exprNodePtr->expr3.type = REAL;
				left_real = left->exprNodePtr->expr1.value->infoNodePtr->infReal.value;
				right_real = right->exprNodePtr->expr1.value->infoNodePtr->infReal.value;
				left_type = REAL;
				right_type = REAL;
			}	
			else if( (operator == ADD) && (left->exprNodePtr->expr1.type == STR) && (right->exprNodePtr->expr1.type == STR) ){
				line = left->exprNodePtr->expr1.value->infoNodePtr->infStr.line_no;
				ret->exprNodePtr->expr3.type = STR;
				left_str = left->exprNodePtr->expr1.value->infoNodePtr->infStr.value;
				right_str = right->exprNodePtr->expr1.value->infoNodePtr->infStr.value;
				left_type = STR;
				right_type = STR;
			}
			else if( (operator == MUL) && (left->exprNodePtr->expr1.type == INT) && (right->exprNodePtr->expr1.type == STR) ){
				line = left->exprNodePtr->expr1.value->infoNodePtr->infInt.line_no;
				ret->exprNodePtr->expr3.type = STR;
				left_int = left->exprNodePtr->expr1.value->infoNodePtr->infInt.value;
				right_str = right->exprNodePtr->expr1.value->infoNodePtr->infStr.value;
				left_type = INT;
				right_type = STR;
			}
		}
	}
	if (left->thisNodeType == EXPR1 && right->thisNodeType == EXPR3) {
		if(left->exprNodePtr->expr1.type != ERROR && right->exprNodePtr->expr3.type != ERROR)
		{
			if( (left->exprNodePtr->expr1.type == INT) && (right->exprNodePtr->expr3.type == INT) ) {
				line = left->exprNodePtr->expr1.value->infoNodePtr->infInt.line_no;
				ret->exprNodePtr->expr3.type = INT;
				left_int = left->exprNodePtr->expr1.value->infoNodePtr->infInt.value;
				right_int = right->exprNodePtr->expr3.value->infoNodePtr->infInt.value;
				left_type = INT;
				right_type = INT;
			}
			else if( (left->exprNodePtr->expr1.type == INT) && (right->exprNodePtr->expr3.type == REAL) ){
				line = left->exprNodePtr->expr1.value->infoNodePtr->infInt.line_no;
				ret->exprNodePtr->expr3.type = REAL;
				left_int = left->exprNodePtr->expr1.value->infoNodePtr->infInt.value;
				right_real = right->exprNodePtr->expr3.value->infoNodePtr->infReal.value;
				left_type = INT;
				right_type = REAL;
			}
			else if( (left->exprNodePtr->expr1.type == REAL) && (right->exprNodePtr->expr3.type == INT) ) {
				line = left->exprNodePtr->expr1.value->infoNodePtr->infReal.line_no;
				ret->exprNodePtr->expr3.type = REAL;
				left_real = left->exprNodePtr->expr1.value->infoNodePtr->infReal.value;
				right_int = right->exprNodePtr->expr3.value->infoNodePtr->infInt.value;
				left_type = REAL;
				right_type = INT;
			}
			else if( (left->exprNodePtr->expr1.type == REAL) && (right->exprNodePtr->expr3.type == REAL) ) {
				line = left->exprNodePtr->expr1.value->infoNodePtr->infReal.line_no;
				ret->exprNodePtr->expr3.type = REAL;
				left_real = left->exprNodePtr->expr1.value->infoNodePtr->infReal.value;
				right_real = right->exprNodePtr->expr3.value->infoNodePtr->infReal.value;
				left_type = REAL;
				right_type = REAL;
			}
			else if( (operator == ADD) && (left->exprNodePtr->expr1.type == STR) && (right->exprNodePtr->expr3.type == STR) ){
				line = left->exprNodePtr->expr1.value->infoNodePtr->infStr.line_no;
				ret->exprNodePtr->expr3.type = STR;
				left_str = left->exprNodePtr->expr1.value->infoNodePtr->infStr.value;
				right_str = right->exprNodePtr->expr3.value->infoNodePtr->infStr.value;
				left_type = STR;
				right_type = STR;
			}
			else if( (operator == MUL) && (left->exprNodePtr->expr1.type == INT) && (right->exprNodePtr->expr3.type == STR) ){
				line = left->exprNodePtr->expr1.value->infoNodePtr->infInt.line_no;
				ret->exprNodePtr->expr3.type = STR;
				left_int = left->exprNodePtr->expr1.value->infoNodePtr->infInt.value; 
				right_str = right->exprNodePtr->expr3.value->infoNodePtr->infStr.value;
				left_type = INT;
				right_type = STR;
			}
		}
	}
	if (left->thisNodeType == EXPR3 && right->thisNodeType == EXPR1) {
		if(left->exprNodePtr->expr3.type != ERROR && right->exprNodePtr->expr1.type != ERROR)
		{
			if( (left->exprNodePtr->expr3.type == INT) && (right->exprNodePtr->expr1.type == INT) ) {
				line = left->exprNodePtr->expr3.value->infoNodePtr->infInt.line_no;
				ret->exprNodePtr->expr3.type = INT;
				left_int = left->exprNodePtr->expr3.value->infoNodePtr->infInt.value;
				right_int = right->exprNodePtr->expr1.value->infoNodePtr->infInt.value;
				left_type = INT;
				right_type = INT;
			}
			else if( (left->exprNodePtr->expr3.type == INT) && (right->exprNodePtr->expr1.type == REAL) ){
				line = left->exprNodePtr->expr3.value->infoNodePtr->infInt.line_no;
				ret->exprNodePtr->expr3.type = REAL;
				left_int = left->exprNodePtr->expr3.value->infoNodePtr->infInt.value;
				right_real = right->exprNodePtr->expr1.value->infoNodePtr->infReal.value;
				left_type = INT;
				right_type = REAL;
			}
			else if( (left->exprNodePtr->expr3.type == REAL) && (right->exprNodePtr->expr1.type == INT) ) {
				line = left->exprNodePtr->expr3.value->infoNodePtr->infReal.line_no;
				ret->exprNodePtr->expr3.type = REAL;
				left_real = left->exprNodePtr->expr3.value->infoNodePtr->infReal.value;
				right_int = right->exprNodePtr->expr1.value->infoNodePtr->infInt.value;
				left_type = REAL;
				right_type = INT;
			}
			else if( (left->exprNodePtr->expr3.type == REAL) && (right->exprNodePtr->expr1.type == REAL) ) {
				line = left->exprNodePtr->expr3.value->infoNodePtr->infReal.line_no;
				ret->exprNodePtr->expr3.type = REAL;
				left_real = left->exprNodePtr->expr3.value->infoNodePtr->infReal.value;
				right_real = right->exprNodePtr->expr1.value->infoNodePtr->infReal.value;
				left_type = REAL;
				right_type = REAL;
			}
			else if( (operator == ADD) && (left->exprNodePtr->expr3.type == STR) && (right->exprNodePtr->expr1.type == STR) ){
				line = left->exprNodePtr->expr3.value->infoNodePtr->infStr.line_no;
				ret->exprNodePtr->expr3.type = STR;
				left_str = left->exprNodePtr->expr3.value->infoNodePtr->infStr.value;
				right_str = right->exprNodePtr->expr1.value->infoNodePtr->infStr.value;
				left_type = STR;
				right_type = STR;
			}
			else if( (operator == MUL) && (left->exprNodePtr->expr3.type == INT) && (right->exprNodePtr->expr1.type == STR) ){
				line = left->exprNodePtr->expr3.value->infoNodePtr->infInt.line_no;
				ret->exprNodePtr->expr3.type = STR;
				left_int = left->exprNodePtr->expr3.value->infoNodePtr->infInt.value; 
				right_str = right->exprNodePtr->expr1.value->infoNodePtr->infStr.value;
				left_type = INT;
				right_type = STR;
			}
		}
	}
	if (left->thisNodeType == EXPR3 && right->thisNodeType == EXPR3) {
		if(left->exprNodePtr->expr3.type != ERROR && right->exprNodePtr->expr3.type != ERROR)
		{
			if( (left->exprNodePtr->expr3.type == INT) && (right->exprNodePtr->expr3.type == INT) ) {
				line = left->exprNodePtr->expr3.value->infoNodePtr->infInt.line_no;
				ret->exprNodePtr->expr3.type = INT;
				left_int = left->exprNodePtr->expr3.value->infoNodePtr->infInt.value;
				right_int = right->exprNodePtr->expr3.value->infoNodePtr->infInt.value;
				left_type = INT;
				right_type = INT;
			}
			else if( (left->exprNodePtr->expr3.type == INT) && (right->exprNodePtr->expr3.type == REAL) ){
				line = left->exprNodePtr->expr3.value->infoNodePtr->infInt.line_no;
				ret->exprNodePtr->expr3.type = REAL;
				left_int = left->exprNodePtr->expr3.value->infoNodePtr->infInt.value;
				right_real = right->exprNodePtr->expr3.value->infoNodePtr->infReal.value;
				left_type = INT;
				right_type = REAL;
			}
			else if( (left->exprNodePtr->expr3.type == REAL) && (right->exprNodePtr->expr3.type == INT) ) {
				line = left->exprNodePtr->expr3.value->infoNodePtr->infReal.line_no;
				ret->exprNodePtr->expr3.type = REAL;
				left_real = left->exprNodePtr->expr3.value->infoNodePtr->infReal.value;
				right_int = right->exprNodePtr->expr3.value->infoNodePtr->infInt.value;
				left_type = REAL;
				right_type = INT;
			}
			else if( (left->exprNodePtr->expr3.type == REAL) && (right->exprNodePtr->expr3.type == REAL) ) {
				line = left->exprNodePtr->expr3.value->infoNodePtr->infReal.line_no;
				ret->exprNodePtr->expr3.type = REAL;
				left_real = left->exprNodePtr->expr3.value->infoNodePtr->infReal.value;
				right_real = right->exprNodePtr->expr3.value->infoNodePtr->infReal.value;
				left_type = REAL;
				right_type = REAL;
			}
			else if( (operator == ADD) && (left->exprNodePtr->expr3.type == STR) && (right->exprNodePtr->expr3.type == STR) ){
				line = left->exprNodePtr->expr3.value->infoNodePtr->infStr.line_no;
				ret->exprNodePtr->expr3.type = STR;
				left_str = left->exprNodePtr->expr3.value->infoNodePtr->infStr.value;
				right_str = right->exprNodePtr->expr3.value->infoNodePtr->infStr.value;
				left_type = STR;
				right_type = STR;
			}
			else if( (operator == MUL) && (left->exprNodePtr->expr3.type == INT) && (right->exprNodePtr->expr3.type == STR) ){
				line = left->exprNodePtr->expr3.value->infoNodePtr->infInt.line_no;
				ret->exprNodePtr->expr3.type = STR;
				left_int = left->exprNodePtr->expr3.value->infoNodePtr->infInt.value; 
				right_str = right->exprNodePtr->expr3.value->infoNodePtr->infStr.value;
				left_type = INT;
				right_type = STR;
			}
		}
	}
	TreeValue * tv = (TreeValue *)malloc (sizeof(TreeValue));
	
	if( ret->exprNodePtr->expr3.type != ERROR ) {
		
		if( ((left_type == INT) && (right_type == STR)) && (operator == MUL) ) {
			info_str str;
			str.line_no = line;
			char * strMul = (char *) malloc (left_int * sizeof( right_str) * sizeof(char) + 1);
			int i = 0;
			int v = 0;

			while( i < left_int )
			{
				int k = 0;
				while ( right_str[k] != '\0' )
				{
					strMul[v + k] = right_str[k];
					k++;
				}
				v = v + k;
				i++;
			}
			strMul[v] = '\0';
			str.value = strMul;
			tv = mkTypeStr( str );
		} 
		else if( (ret->exprNodePtr->expr3.type == STR) && (operator == ADD) ) {
			info_str str_sum;
			char * str = (char*) malloc( sizeof(char) * (sizeof(left_str) + sizeof(right_str)) + 1 );
			int i = 0;
			while ( left_str[i] != '\0' ){
				str[i] = left_str[i];
				i++;
			}
			int k = 0;
			while (  right_str[k] != '\0' ){ 
				str[ k + i ] = right_str[k];
				k++;
			}
			str[ k + i ] = '\0';
			str_sum.value = str;
			str_sum.line_no = line;
			tv = mkTypeStr( str_sum );
		}
		else if( (left_type == INT) && (right_type == INT) ) {
			if( operator == ADD ){
				info_int intSum;
				intSum.line_no = line;
				intSum.value = left_int + right_int;
				tv = mkTypeInt( intSum );
			} 
			else if( operator == SUB ){
				info_int intSub;
				intSub.line_no = line;
				intSub.value = left_int - right_int;
				tv = mkTypeInt( intSub );
			} 
			else if( operator == MUL ){
				info_int intMul;
				intMul.line_no = line;
				intMul.value = left_int * right_int;
				tv = mkTypeInt( intMul );
			}
			else if( operator == DIV ){
				info_int intDiv;
				intDiv.line_no = line;
				intDiv.value = left_int / right_int;
				tv = mkTypeInt( intDiv );
			}
		}
		else if( (left_type == INT) && (right_type == REAL) ) {
			if( operator == ADD ){
				info_real realSum;
				realSum.line_no = line;
				realSum.value = (float)left_int + right_real;
				tv = mkTypeReal( realSum );
			}
			else if( operator == SUB ){
				info_real realSub;
				realSub.line_no = line;
				realSub.value = (float)left_int - right_real;
				tv = mkTypeReal( realSub );
			}
			else if( operator == MUL ){
				info_real realMul;
				realMul.line_no = line;
				realMul.value = (float)left_int * right_real;
				tv = mkTypeReal( realMul );
			}
			else if( operator == DIV ){
				info_real realDiv;
				realDiv.line_no = line;
				realDiv.value = (float)left_int / right_real;		
				tv = mkTypeReal( realDiv );
			}
		}		
		else if( (left_type == REAL) && (right_type == INT) ) {
			if( operator == ADD ){
				info_real realSum;
				realSum.line_no = line;
				realSum.value = left_real + (float)right_int;
				tv = mkTypeReal( realSum );
			}
			else if( operator == SUB ){
				info_real realSub;
				realSub.line_no = line;
				realSub.value = left_real - (float)right_int;
				tv = mkTypeReal( realSub );
			}
			else if( operator == MUL ){
				info_real realMul;
				realMul.line_no = line;
				realMul.value = left_real * (float)right_int;
				tv = mkTypeReal( realMul );
			}
			else if( operator == DIV ){
				info_real realDiv;
				realDiv.line_no = line;
				realDiv.value = left_real / (float)right_int;
				tv = mkTypeReal( realDiv );
			}
		}
		else{
			if( operator == ADD ){
				info_real realAdd;
				realAdd.line_no = line;
				realAdd.value = left_real + right_real;
				tv = mkTypeReal( realAdd );
			}
			else if( operator == SUB ){
				info_real realSub;
				realSub.line_no = line;
				realSub.value = left_real - right_real;
				tv = mkTypeReal( realSub );
			}
			else if( operator == MUL ){
				info_real realMul;
				realMul.line_no = line;
				realMul.value = left_real * right_real;
				tv = mkTypeReal( realMul );
			}
			else if( operator == DIV ){
				info_real realDiv;
				realDiv.line_no = line;
				realDiv.value = left_real / right_real;
				tv = mkTypeReal( realDiv );
			}
		}
		
	}
	else{
		if(left->thisNodeType == EXPR3)
		{
			if(left->exprNodePtr->expr3.type == ERROR)
				tv = mkTypeError(left->exprNodePtr->expr3.value->infoNodePtr->error_line);
			else if(left->exprNodePtr->expr3.type == REAL)
				tv = mkTypeError(left->exprNodePtr->expr3.value->infoNodePtr->infReal.line_no);
			else if(left->exprNodePtr->expr3.type == INT)
				tv = mkTypeError(left->exprNodePtr->expr3.value->infoNodePtr->infInt.line_no);
			else if(left->exprNodePtr->expr3.type == STR)
				tv = mkTypeError(left->exprNodePtr->expr3.value->infoNodePtr->infStr.line_no);
		}
		else
		{	
			if(left->exprNodePtr->expr1.type == ERROR)
				tv = mkTypeError(left->exprNodePtr->expr1.value->infoNodePtr->error_line);
			else if(left->exprNodePtr->expr1.type == REAL)
				tv = mkTypeError(left->exprNodePtr->expr1.value->infoNodePtr->infReal.line_no);
			else if(left->exprNodePtr->expr1.type == INT)
				tv = mkTypeError(left->exprNodePtr->expr1.value->infoNodePtr->infInt.line_no);
			else if(left->exprNodePtr->expr1.type == STR)
				tv = mkTypeError(left->exprNodePtr->expr1.value->infoNodePtr->infStr.line_no);
		}
	}
	ret->exprNodePtr->expr3.value = tv;
	return (ret);
}

TreeNode * mkEXPR1 ( TreeValue * val,  ConstType cType ) {
	TreeNode * ret = (TreeNode *)malloc (sizeof(TreeNode));
	ret->thisNodeType = EXPR1;
	ret->exprNodePtr = (ExprNode *)malloc (sizeof(ExprNode));
	ret->exprNodePtr->expr1.type = cType;
	ret->exprNodePtr->expr1.value = val;
	return (ret);
}

TreeValue * mkTypeStr ( info_str str ) {
	TreeValue * ret = (TreeValue *)malloc (sizeof(TreeValue));
	ret->type = STR;
	ret->infoNodePtr = (InfoNode *)malloc (sizeof(InfoNode));
	if( str.value[0] == '\'')
	{
		char * str_without_quote = (char*)malloc( sizeof(char) * sizeof(str.value) );
		int i = 1;
		while ( str.value[i] != '\'') 
		{
			str_without_quote[ i - 1 ] = str.value[i];
			i++;
		}
		str_without_quote[ i - 1 ] = '\0'; 
		ret->infoNodePtr->infStr.value = str_without_quote;
	}
	else
	{
		ret->infoNodePtr->infStr.value = str.value;
	}
	ret->infoNodePtr->infStr.line_no = str.line_no;
	return (ret);
}

TreeValue * mkTypeInt ( info_int val ){
	TreeValue * ret = (TreeValue *)malloc (sizeof(TreeValue));
	ret->type = INT;
	ret->infoNodePtr = (InfoNode *)malloc (sizeof(InfoNode));
	ret->infoNodePtr->infInt.value = val.value;
	ret->infoNodePtr->infInt.line_no = val.line_no;
	return (ret);
}

TreeValue * mkTypeReal ( info_real val ){
        TreeValue * ret = (TreeValue *)malloc (sizeof(TreeValue));
        ret->type = REAL;
        ret->infoNodePtr = (InfoNode *)malloc (sizeof(InfoNode));
        ret->infoNodePtr->infReal.value = val.value;
        ret->infoNodePtr->infReal.line_no = val.line_no;
	return (ret);
} 

TreeValue * mkTypeError ( int line_num ){
	TreeValue * ret = (TreeValue *)malloc (sizeof(TreeValue));
	ret->type = ERROR;
	ret->infoNodePtr = (InfoNode *)malloc (sizeof(InfoNode));
	ret->infoNodePtr->error_line = line_num;
	return (ret);
}

int main ()
{
	if (yyparse()) {
			// parse error
			printf("ERROR\n");
			return 1;
		}
	else {
		// successful parsing
		return 0;
	     }
}
