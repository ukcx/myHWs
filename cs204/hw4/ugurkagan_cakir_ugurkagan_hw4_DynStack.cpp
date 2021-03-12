#include <iostream>
#include "ugurkagan_cakir_ugurkagan_hw4_DynStack.h"
using namespace std;

/* Begin: code taken and updated from DynIntStack.cpp */

/*
	Constructor      
*/
DynStack::DynStack()
{
	top = NULL;
}

/*
	pushes new StackNode into top of the stack with given row and column coordinates
*/
void DynStack::push(int row, int column)
{
	StackNode *newNode;

	// Allocate a new node 
	newNode = new StackNode(row, column, NULL);

	// If there are no nodes in the list
	// make newNode the first node
	if (isEmpty())
	{
		top = newNode;
	}
	else	// Otherwise, insert newNode before top
	{
		newNode->next = top;
		top = newNode;
	}
}

/*
	pops the top element of the stack, returns the row and column coordinates of the popped StackNode as reference parameters
*/
void DynStack::pop(int &row, int &column)
{
	StackNode *temp;

	if (isEmpty())		//if the stack is already empty warns the user
	{
		cout << "The stack is empty.\n";
	}
	else	// pop value off top of stack
	{
		row = top->row_coordinate;
		column = top->column_coordinate;
		temp = top->next;
		delete top;
		top = temp;
	}
}

/*
	checks if the stack is empty or not
*/
bool DynStack::isEmpty(void)
{
	bool status;

	if (top == NULL)
		status = true;
	else
		status = false;

	return status;
}

/* End: code taken and updated from DynIntStack.cpp */

/* Begin: code taken and updated from LinkedListExtraOper.cpp */

/*
	copy constructor
*/
DynStack::DynStack(const DynStack & originalStack)
{
	top = originalStack.createClone();
}

/*
	Destructor
*/
DynStack::~DynStack()
{
	StackNode * temp = top;

	while(top != NULL)
	{
		temp = top->next;
		delete top;
		top = temp;
	}
}

/*
	a private function that used in copy constructor to create deep copy
*/
StackNode * DynStack::createClone() const
{
	if (top == NULL)  
		return NULL;   
	
	StackNode * cloneHead = new StackNode(top->row_coordinate, top->column_coordinate, NULL);		//clone's head is a copy of original stack's head
	StackNode * ptr = top->next;  
	StackNode * ptrClone = cloneHead;
	while (ptr != NULL) 
	{
		ptrClone->next = new StackNode (ptr->row_coordinate, ptr->column_coordinate, NULL);			//original stack's other nodes are adding into copy stack
		ptr = ptr->next;																			//ptr is iterating over the original stack
		ptrClone = ptrClone->next;
	}

	return cloneHead;
}

/* End: code taken and updated from LinkedListExtraOper.cpp */