#ifndef DYNSTACK_H
#define DYNSTACK_H

/* Begin: code taken and updated from DynIntStack.h */

struct StackNode
{
	int row_coordinate;
	int column_coordinate;
	StackNode *next;

	StackNode::StackNode()		//initializer without parameter
	{
		next = NULL;
	}

	StackNode::StackNode(int row, int column, StackNode *next)
		:row_coordinate(row),
		column_coordinate(column),
		next(next){}
};

class DynStack
{
private:
	StackNode *top;
	StackNode *createClone() const;			//used in copy constructor to create a deep copy

public:
	DynStack();							//default constructor that creates an empty stack
	DynStack(const DynStack &);			//copy constructer that constructs deep copy of a DynStack object
	~DynStack();						//destructer
	void push(int, int);				//pushes a point with given row and column coordinates 
	void pop(int &, int &);				//pops the top stacknode in the stack
	bool isEmpty(void);					//checks if the stack is empty or not
};

#endif
/* End: code taken and updated from DynIntStack.h */	
