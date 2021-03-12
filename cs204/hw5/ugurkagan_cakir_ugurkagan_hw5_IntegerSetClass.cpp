#include <iostream>
#include "ugurkagan_cakir_ugurkagan_hw5_IntegerSetClass.h"

using namespace std;

//default constructor creates an empty integerset
IntegerSet::IntegerSet()
{
	size = 0;
	elementSet = NULL;
}

//constructor with value, creates an integer array contains all numbers starting from 0 up to some number
IntegerSet::IntegerSet(const int & numOfElements)
{
	if(numOfElements > 0)
	{
		size = numOfElements;
		elementSet = new int[numOfElements];

		for(int i = 0; i < numOfElements; i++)
		{
			elementSet[i] = i;
		}
	}
	else //if the number is not positive, create an empty set
	{
		size = 0;
		elementSet = NULL;
		cout << "Created an empty set." << endl;
	}
}

//deep copy constructor
IntegerSet::IntegerSet(const IntegerSet & copy)
{
	size = copy.size;
	if(size == 0)		//if the size is zero the pointer should point to null, there shouldn't be any array with 0 elements
		elementSet = NULL;

	else
	{
		elementSet = new int[size];
	
		for(int i = 0; i < size; i++)
		{
			elementSet[i] = copy.elementSet[i];
		}
	}
}

//destructor
IntegerSet::~IntegerSet()
{
	size = 0;
	delete [] elementSet;		//free dynamically allocated memory
	elementSet = NULL;
}

//returns the size of the set, it allows non-member functions to learn the size of an IntegerSet object
int IntegerSet::getSize() const
{
	return size;
}

//checks if a given number is inside the elementSet or not
bool IntegerSet::isIn(const int & number) const
{
	for(int i = 0; i < size; i++)
	{
		if(elementSet[i] == number) //the number exists in elementSet
			return true;
	}
	return false;
}

//gets the element in a given position from elementSet and returns the number as a reference parameter (intInPos)
void IntegerSet::getAnInt(const int & position, int & intInPos) const
{
	if(elementSet != NULL) //if NULL no need to check
	{
		if(position < size)
			intInPos = elementSet[position];
	}
}

//adds the integer taken as parameter to a copy of the object's elementSet if needed
IntegerSet IntegerSet::operator + (const int & number) const
{
	if(isIn(number)) //the number is already in the elementSet
	{
		IntegerSet lhs(*this);
		return lhs;		//return a copy of the original object
	}
	else
	{
		IntegerSet sum(size + 1);
		for(int i = 0; i < size; i++)
		{
			sum.elementSet[i] = elementSet[i];
		}
		sum.elementSet[size] = number;
		return sum;		//return the object which has all the elements in the original set and also the number
	}
}

//assigns the rhs IntegerSet object to the lhs IntegerSet object
const IntegerSet & IntegerSet::operator = (const IntegerSet & intSet)
{
	if(&intSet != this) //shouldn't be a self-assignment
	{
		size = intSet.size;
		delete [] elementSet;	//to prevent memory leak
		if(intSet.elementSet != NULL)	
		{
			elementSet = new int[size];
			for(int i = 0; i < size; i++)
				elementSet[i] = intSet.elementSet[i];
		}
		else				//if intSet is empty there is no need to create an integer array
			elementSet = NULL;
	}
	return *this;	
}

//adds all the values of the RHS set that does not occur in LHS, to the LHS set
const IntegerSet & IntegerSet::operator += (const IntegerSet & rhs)
{
	int * set = new int[size + rhs.size];
	for(int i = 0; i < size; i++)
		set[i] = elementSet[i];

	int sizeOfSet = size; //sizeOfSet will hold the number of characters that we will add to the set
						  //we may or may not fill all the set, not filled characters won't be added to the elementSet of the LHS

	for(int k = 0; k < rhs.size; k++)
	{
		bool addToSet = true;
		if(isIn(rhs.elementSet[k]))	//an element of the rhs occurs in lhs
			addToSet = false;		//do not add it to the set

		if(addToSet)
		{
			set[sizeOfSet] = rhs.elementSet[k];
			sizeOfSet += 1;		//sizeOfSet is almost 1 bigger than the input of the last filled character
		}
	}

	delete [] elementSet;
	size = sizeOfSet;
	
	if(size != 0)
	{
		elementSet = new int[sizeOfSet];
		for(int m = 0; m < sizeOfSet; m++)		//add all elements of the set to lhs object
			elementSet[m] = set[m];
	}

	else		//both lhs and rhs are empty sets
	{
		elementSet = NULL;
	}
	delete [] set;	

	return *this;
}

//checks if 2 IntegerSet objects are the same or not
bool IntegerSet::operator != (const IntegerSet & rhs) const
{
	if(size != rhs.size) //if sizes are different, objects are diffent from each other automatically
		return true;

	for(int i = 0; i < size; i++)
	{
		if(!isIn(rhs.elementSet[i]))	//found a difference
			return true;
	}
	return false; 
}