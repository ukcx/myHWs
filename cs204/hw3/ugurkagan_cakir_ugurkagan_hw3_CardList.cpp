#include <iostream>
#include "ugurkagan_cakir_ugurkagan_hw3_CardList.h"

using namespace std;

/*
	this function is not a member function 
	this function is used inside insertCard function to insert a credit card number in a given expirationNode 
*/
bool insert_a_card(expirationNode * & ptr, const string cardNumber)
{
	creditCardNode * temp = ptr->cHead;
	creditCardNode * prev = NULL;
	bool isFoundPlace = false;		//the place to insert the card number is found or not
	bool isDuplicate = false;		//this is true if a given card is already in the card list

	while(temp != NULL && !isFoundPlace)
	{
		if(cardNumber == temp->creditCardNo)
		{
			isDuplicate = true;		//card is already in the list
			isFoundPlace = true;
		}
		else if(cardNumber < temp->creditCardNo)
		{
			isFoundPlace = true;
		}
		else
		{
			prev = temp;
			temp = temp->next;
		}

	}
	if(!isDuplicate)		
	{
		if(prev != NULL)		
		{
			temp = new creditCardNode(cardNumber);
			temp->next = prev->next;
			prev->next = temp;
		}
		else				//adding to the beginnning of the list
		{
			prev = new creditCardNode(cardNumber);
			prev->next = temp;
			ptr->cHead = prev;
		}
		return true;		//card is added to the list
	}
	return false;			//card is not added to the list
}

/*
	default constructer
*/
CardList::CardList()
{
	tail = NULL;
	head = NULL;
}

/*
	inserts a card to a CardList object
*/
void CardList::insertCard(string card_number, int month, int year)
{
	bool isNewNode = true;				//this stays true if a new expirationNode is required
	bool isFoundPlace = false;			//for finding right place to add the node
	expirationNode * temp = head;
	expirationNode * previous = NULL;

	while(temp != NULL && !isFoundPlace)
	{
		if(temp->month == month && temp->year == year)
		{
			isNewNode = false;				//the node with given month and year is already exists no need to create a new expirationNode
			isFoundPlace = true;
		}
		else if((temp->year == year && temp->month > month) || temp->year > year)
		{
			isFoundPlace = true;
		}
		else						//if we didn't find the place
		{
			previous = temp;
			temp = temp->next;			 
		}
	}
	expirationNode * ptr = temp;		//if a new node is not required ptr points at the same place with temp until the end of the function

	if(isNewNode)
	{
		ptr = new expirationNode(month, year);
		if(head == NULL && tail == NULL)			//list is empty 
		{
			head = ptr;
			tail = head;
		}
		else if(previous != NULL && temp == NULL)		//adding to the end of the expirationNode list
		{
			previous->next = ptr;
			ptr->prev = previous;
			tail = ptr;
		}
		else if(previous == NULL && temp != NULL)		//adding to the beginning of the expirationNode list
		{
			ptr->next = temp;
			temp->prev = ptr;
			head = ptr;
		}
		else											//adding to somewhere in middle of the expirationNode list
		{
			previous->next = ptr;
			ptr->prev = previous;
			ptr->next = temp;
			temp->prev = ptr;
		}
	}
	bool isInserted = insert_a_card(ptr, card_number);			//if the card number is not duplicate it will be inserted

	if(isNewNode)
	{
		cout << card_number << " " << month << " " << year << ": added to a new expiration date node" << endl;
	}
	else if(isInserted)
	{
		cout << card_number << " " << month << " " << year << ": inserted to an existing expiration date node" << endl;
	}
	else
	{
		cout << card_number << " " << month << " " << year << ": this card was already inserted" << endl;
	}
}

/*
	this function lists all the credit card numbers in the chronological order(earliest to latest)
*/
void CardList::displayListChronological()
{
	cout << "\n";
	if(head == NULL)
	{
		cout << "List is empty!" << endl;
	}
	else
	{
		expirationNode * temp = head;
		while(temp != NULL)
		{
			cout << "Expiration Date: " << temp->month << " " << temp->year << endl;
			int id = 1;
			creditCardNode * cards = temp->cHead;
			while(cards != NULL)
			{
				cout << id << ") " << cards->creditCardNo << endl;
				id += 1;
				cards = cards->next;
			}
			cout << "-------------------" << endl;
			temp = temp->next;			//from head to tail of the list
		}
	}
}

/*
	this function lists all the credit card numbers in the reverse order of chronological order(latest to earliest)
*/
void CardList::displayListReverseChronological()
{
	cout << "\n";
	if(tail == NULL)
	{
		cout << "List is empty!" << endl;
	}
	else
	{
		expirationNode * temp = tail;
		while(temp != NULL)
		{
			cout << "Expiration Date: " << temp->month << " " << temp->year << endl;
			int id = 1;
			creditCardNode * cards = temp->cHead;
			while(cards != NULL)
			{
				cout << id << ") " << cards->creditCardNo << endl;
				id += 1;
				cards = cards->next;
			}
			cout << "-------------------" << endl;
			temp = temp->prev;			//from tail to head of the list
		}
	}
}

/*
	this function takes a credit card number as a parameter and searchs that number in the list
*/
void CardList::cardSearch(string cardNumber)
{
	bool cardIsInside = false;
	cout << "\n";

	if(head == NULL);
	else
	{
		expirationNode * temp = head;
		while(temp != NULL)
		{
			creditCardNode * cTemp = temp->cHead;
			while(cTemp != NULL)
			{
				if(cTemp->creditCardNo == cardNumber)
				{
					cardIsInside = true;			//card is found in the list
					cout << "There exists a credit card given number " << cardNumber << " with expiration date: " << temp->month << " " << temp->year << endl;
				}
				cTemp = cTemp->next;
			}
			temp = temp->next;
		}	
	}
	
	if(!cardIsInside)
		cout << "There is no credit card with given credit card number: " << cardNumber << endl;
}

/*
	this function deletes cards that have an expiration date same with or before than month and year that took as parameters 
*/
void CardList::bulkDelete(int month, int year)
{
	bool isDeleted = false;
	cout << "\n";
	if(head == NULL);
	else
	{
		expirationNode * temp = NULL;
		creditCardNode * cards_head = NULL;
		creditCardNode * cTemp = NULL;
		while(head != NULL && ((month >= head->month && year == head->year) || (year > head->year)))
		{
			cards_head = head->cHead;
			isDeleted = true;
			int id = 1;
			cout << "Node with expiration date " << head->month << " " << head->year << "  and the following credit cards have been deleted!" << endl;
			while(cards_head != NULL)
			{
				cout << id << ") " << cards_head->creditCardNo << endl;
				id += 1;
				cTemp = cards_head->next;
				delete cards_head;			//deleting the creditCardNode list
				cards_head = cTemp;
			}
			temp = head->next;
			delete head;			//deleting an expirationNode
			head = temp;
		}
	}
	if(head == NULL)		//list became empty
		tail = NULL;
	else					//list has some elements but head's prev points to a deleted memory location
		head->prev = NULL;
	if(!isDeleted)
		cout << "No cards have been deleted!" << endl;
}

/*
	this function returns all the dynamically allocated memory area to the heap
*/
void CardList::deleteAll()
{
	while(head != NULL)
	{
		expirationNode * temp = head->next;
		creditCardNode * credit_card_head = head->cHead;
		while(credit_card_head != NULL)
		{
			creditCardNode * temp2 = credit_card_head->next;
			delete credit_card_head;		//deleting the creditCardNode list
			credit_card_head = temp2;
		}
		delete head;				//deleting the expirationNode list
		head = temp;
	}
	tail = NULL;
}