#ifndef __EX4_H
#define __EX4_H

typedef enum { EXPR3, EXPR1 } NodeType;

typedef enum { ERROR, STR, INT, REAL} ConstType;

typedef enum { ADD, SUB, MUL, DIV } OpType;

typedef struct info_real{
	float value;
	int line_no;
	} info_real;

typedef struct info_int{
	int value;
	int line_no;
	} info_int;

typedef struct info_str{
	char * value;
	int line_no;
	} info_str;

typedef union{
	info_real infReal;
	info_int infInt;
	info_str infStr;
	int error_line;
	} InfoNode;

typedef struct TreeValue{
	ConstType type;
	InfoNode * infoNodePtr;
	} TreeValue;

typedef struct Expr3Node {
	OpType operator;
	ConstType type;
	TreeValue * value;
	struct TreeNode *leftChild;
	struct TreeNode *rightChild;
	} Expr3Node;

typedef struct Expr1Node {
	TreeValue * value;
	ConstType type;
	} Expr1Node;

typedef union {
	Expr1Node expr1;
	Expr3Node expr3;
	} ExprNode;

typedef struct TreeNode {
	NodeType thisNodeType;
	ExprNode *exprNodePtr;
	} TreeNode;
#endif
