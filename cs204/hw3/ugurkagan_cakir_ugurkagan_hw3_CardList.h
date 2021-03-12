
#ifndef _CARDLIST_H
#define _CARDLIST_H
#include <string>

using namespace std;

struct creditCardNode  
{  
	string creditCardNo;  
	creditCardNode * next;  

	/*
		if no parameter is given while creation of an object
		next pointer is initialized to point at null
	*/
	creditCardNode::creditCardNode()
	{
		next = NULL;
	}

	/*
		constructer with parameters
		creditCardNo must be entered, next is optional
	*/
	creditCardNode::creditCardNode(string cardNum, creditCardNode * next = NULL)
		:creditCardNo(cardNum),
		next(next){}
};

struct expirationNode 
{  
	int month, year;  
	creditCardNode * cHead;  
	expirationNode * next;  
	expirationNode * prev;

	/*
		if no parameter is given while creation of an object
		all pointers initialized to point at null
	*/
	expirationNode::expirationNode()		
	{
		cHead = NULL;
		next = NULL;
		prev = NULL;
	}

	/*
		month and year values must be entered, cHead, next and prev are optional
		cHead, next and prev will point to null if there is no parameter given
	*/
	expirationNode::expirationNode(int expiration_month, int expiration_year, creditCardNode * cards = NULL, expirationNode * next = NULL, expirationNode * prev = NULL)
		:month(expiration_month),
		year(expiration_year),
		cHead(cards),
		next(next),
		prev(prev)
	{
	}
};

class CardList 
{ 
public: 
	CardList(); //default constructor that creates an empty list 
	void insertCard (string creditCardNo, int month, int year); 
		//inserts a new card to the structure in sorted fashion 
	void displayListChronological (); 
		//displays entire structure in chronological order 
	void displayListReverseChronological (); 
		//displays entire structure in reverse chronological order 
	void cardSearch (string creditCardNo);
		//displays all of the occurrences of the given card number 
	void bulkDelete (int month, int year); 
		//deletes all nodes up to and including given expiration date 
	void deleteAll (); //deletes the entire structure

private: 
	expirationNode * head; 
	expirationNode * tail;
};

#endif