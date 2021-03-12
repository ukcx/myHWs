#ifndef UGURKAGAN_CAKIR_UGURKAGAN_HW5_INTEGERSETCLASS_H
#define UGURKAGAN_CAKIR_UGURKAGAN_HW5_INTEGERSETCLASS_H

class IntegerSet
{
private:
	int size;				//the number of integers stored in the array pointed by elementSet
	int * elementSet;		//integer array with size amount of elements

public:
	IntegerSet();											//default constructor
	IntegerSet(const int &);								//constructor with size of the array parameter
	IntegerSet(const IntegerSet &);							//copy constructor
	~IntegerSet();											//destructor
	int getSize() const;									//returns size
	void getAnInt(const int &, int &) const;				//returns an integer from elementSet using reference parameter
	bool isIn(const int &) const;							//checks if a given int is in the elementSet
	IntegerSet operator + (const int &) const;				//add one integer to IntegerSet object
	const IntegerSet & operator = (const IntegerSet &);		//assign rhs IntegerSet to the lhs IntegerSet
	const IntegerSet & operator += (const IntegerSet &);	//add rhs IntegerSet to the lhs IntegerSet
	bool operator != (const IntegerSet &) const;			//check the inequality of 2 IntegerSet objects

};

#endif