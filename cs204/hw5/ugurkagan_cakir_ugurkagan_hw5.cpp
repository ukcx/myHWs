//Name: Ugur Kagan Cakir
#include <iostream>
#include <string>
#include "ugurkagan_cakir_ugurkagan_hw5_IntegerSetClass.h"

using namespace std;

//print out integers in the integer set array
ostream & operator << (ostream & os, const IntegerSet & ints)
{
	int size = ints.getSize();
	int num;	//num will store an integer from the integer set array
	
	if(size > 0)
	{
		os << "{";
		for(int i = 0; i <= size - 2; i++)
		{
			ints.getAnInt(i, num);
			os << num << ", ";
		}
		ints.getAnInt(size - 1, num);
		os <<  num << "}";
	} 

	else
		os << "{}";

	return os;
}

//add 2 integersets, returning set contains all the elements from lhs and rhs only once
IntegerSet operator + (const IntegerSet & lhs, const IntegerSet & rhs)
{
	IntegerSet sum(lhs);
	sum += rhs;
	return sum;
}

//checks if a given number occurs in the integer set array
bool operator <= (const int & num, const IntegerSet & intSet)
{
	if(intSet.isIn(num))
		return true;

	return false;
}

//return true if lhs integer set is a subset of the rhs integer set
bool operator <= (const IntegerSet & lhs, const IntegerSet & rhs)
{
	if(lhs.getSize() > rhs.getSize())	//if lhs has more elements in the set than rhs it can not be a subset of rhs
		return false;

	bool isSubSet = true;	//stays true if the elements of lhs also occurs in the rhs
	for(int i = 0; i < lhs.getSize() && isSubSet; i++)
	{
		isSubSet = false;
		int num;
		lhs.getAnInt(i, num);
		
		if(rhs.isIn(num))
			isSubSet = true;
	}
	
	if(isSubSet)	//all elements of lhs also occurs in the rhs
		return true;
	else
		return false;
}

//returns the integerset that includes all the common integers of lhs and rhs
IntegerSet operator * (const IntegerSet & lhs, const IntegerSet & rhs)
{
	IntegerSet intSet;	//intersection set, currently empty

	for(int i = 0; i < lhs.getSize(); i++)
	{
		int num;
		lhs.getAnInt(i, num);
		if(rhs.isIn(num))	//common integer
		{
			intSet = intSet + num;	//add common integer to the intersection set
		}
	}
	return intSet;
}
//All #includes and free functions ends here
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

IntegerSet Union(const IntegerSet& lhs, const IntegerSet& rhs) 
{
	IntegerSet res = lhs + rhs;

	return res;
}

void takeInputs(IntegerSet& intSet, int x) 
{
	cout << "Please enter elements of set " << x << ". Press CTRL + Z after all elements are entered " << endl;

	int element;
	while (cin >> element)
	{
		intSet = intSet + element;
	}
	cin.clear();
}

int main()
{
	
	IntegerSet intSet1;
	IntegerSet intSet2;

	takeInputs(intSet1, 1);
	cout << "intSet1" << endl;
	cout << intSet1 << endl << endl;

	takeInputs(intSet2, 2);
	cout << "intSet2" << endl;
	cout << intSet2 << endl << endl;

	IntegerSet intSet3(intSet1);

	cout << "intSet3 after IntegerSet intSet3(intSet1)" << endl;
	cout << intSet3 << endl << endl;
	intSet3 = intSet3;

	if (intSet1 != intSet3)
	{
		cout << "intSet3" << intSet3 << " is different than intSet1 " << intSet1 << endl << endl;
	}
	else 
	{
		cout << "intSet3" << intSet3 << " is equal to intSet1 " << intSet1 << endl << endl;
	}

	if (!(intSet1 != intSet2))
		cout << "intSet1 " << intSet1 << " is equal to intSet2 " << intSet2 << endl << endl;
	else
		cout << "intSet1 " << intSet1 << " is not equal to intSet2 " << intSet2 << endl << endl;
	
	intSet3 = Union(intSet1, intSet2);
	cout << "intSet3 after intSet3 = Union(intSet1, intSet2) " << endl << intSet3 << endl << endl;

	IntegerSet intSet4;
	intSet4 = intSet1 + intSet2;
	cout << "intSet4 after intSet4 = intSet1 + intSet2 "<< endl << intSet4 << endl << endl;

	if (!(intSet3 != intSet4))
		cout << "intSet3 " << intSet3 << " is equal to intSet4 " << intSet4 << endl << endl;
	else
		cout << "intSet3 " << intSet3 << " is not equal to intSet4 " << intSet4 << endl << endl;

	intSet1 = intSet1 + 22;
	cout << "intSet1 after intSet1 = intSet1 + 22" << endl;
	cout << intSet1 << endl << endl;
	intSet2 = intSet2 + -22;
	cout << "intSet2 after intSet2 = intSet2 + -22" << endl;
	cout << intSet2 << endl << endl;

	intSet4 = intSet3 * intSet2;

	cout << "intSet4 after intSet4 = intSet3 * intSet2" << endl;
	cout << intSet4 << endl << endl;

	intSet4 = intSet3 * intSet1;

	cout << "intSet4 after intSet4 = intSet3 * intSet1" << endl;
	cout << intSet4 << endl << endl;

	intSet3 = intSet1 + intSet2 + intSet4;
	cout << "intSet3 after intSet3 = intSet1 + intSet2 + intSet4" << endl;
	cout << intSet3 << endl << endl;

	intSet4 += intSet1;

	cout << "intSet4 after intSet4 += intSet1" << endl;
	cout << intSet4 << endl << endl;
	
	if (3 <= intSet1)
		cout << 3 << " is element of intSet1 " << intSet1 << endl << endl;
	else
		cout << 3 << " is not element of intSet1 " << intSet1 << endl << endl;

	if (intSet4 <= intSet3)
		cout << "intSet4 " << intSet4 << " is a subset of intSet3 " << intSet3 << endl << endl;
	else
		cout << "intSet4 " << intSet4 << " is not a subset of intSet3 " << intSet3 << endl << endl;

	intSet1 = intSet2 += intSet3;
	cout << "intSet2 after intSet1 = intSet2 += intSet3 " << endl << intSet2 << endl << endl;

	cout << "intSet1 after intSet1 = intSet2 += intSet3 " << endl << intSet1 << endl << endl;

	IntegerSet intSet5(11);
	cout << "intSet5 after IntegerSet intSet5(11) " << endl << intSet5 << endl << endl;

	intSet1 = intSet2 = intSet3 += intSet4 += intSet5;
	cout << "After intSet1 = intSet2 = intSet3 += intSet4 += intSet5 " << endl << endl;
	cout << "intSet1: " << intSet1 << endl;
	cout << "intSet2: " << intSet2 << endl;
	cout << "intSet3: " << intSet3 << endl;
	cout << "intSet4: " << intSet4 << endl;
	cout << "intSet5: " << intSet5 << endl;

	return 0;
}