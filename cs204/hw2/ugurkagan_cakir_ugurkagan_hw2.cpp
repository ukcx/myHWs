/*
	Name: Ugur Kagan Cakir
*/

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>

using namespace std;

struct node
{
	int month;
	int year;
	vector<string> credit_cards;
	node * next;

	node::node()		//node initially points to NULL
	{
		next = NULL;
	}

	node::node(int expiration_month, int expiration_year)
		:month(expiration_month),
		 year(expiration_year)
	{
	}
};

void displayList(node * head)		//this function displays the list of nodes
{
	node * temp = head;
	cout << "\n";
	if(temp == NULL)
	{
		cout << "List is empty!\n" << endl;
	}
	while(temp != NULL)
	{
		cout << "Expiration Date: " << temp->month << " " << temp->year << endl;
		for(int i = 1; i <= temp->credit_cards.size(); i++)
			cout << i << ") " << temp->credit_cards[i-1] << endl;
		cout << "-------------------" << endl << endl;
		temp = temp->next;
	}

}

bool validCard(string card_num)		//checks if the user-entered card number is valid or not
{
	bool cardIsValid = true;
	int len = card_num.length();
	for(int i = 0; i < len; i++)
	{
		if(card_num[i] < '0' || card_num[i] > '9')		//all digits
		{
			cardIsValid = false;
		}
	}
	if( len != 16)		//16 character long
		cardIsValid = false;

	return cardIsValid;
}

void cardFinder(string card_number, node * head)		//checks if a given card number is in the list
{
	bool isFound = false;
	node * temp = head;
	node * prev = NULL;		//holds previous node
	while(temp != NULL && !(isFound))
	{
		for(int i = 0; i < temp->credit_cards.size(); i++)
		{
			if(temp->credit_cards[i] == card_number)
				isFound = true;
		}
		prev = temp;
		temp = temp->next;		
	}

	if(isFound)		//card number is found in the list
	{
		cout << "There exists a credit card given number " << card_number << " with expiration date: " << prev->month << " " << prev->year << endl << endl;
	}
	else
	{
		cout << "There is no credit card with given credit card number: " << card_number << endl << endl;
	}
}

void deleteCard(node * & head, int month, int year)			//deletes the card with given month and year
{
	node * temp = head;
	node * prev = head;
	bool isFound = false;
	while( temp != NULL && !(isFound))
	{
		if(temp->month == month && temp->year == year)
		{
			isFound = true;
		}
		else
		{
			prev = temp;
			temp = temp->next;
		}
	}

	if(isFound)			//if the given card number can be found in the list
	{
		cout << "Node with expiration date " << month << " " << year << " and the following credit cards have been deleted!" << endl;
		for(int i = 1; i <= temp->credit_cards.size(); i++)
		{
			cout << i << ") " << temp->credit_cards[i-1] << endl;
		}
	}
	else
	{
		cout << "There is no node with expiration date " <<  month << " " << year << ", nothing deleted!" << endl;
	}

	if(temp != NULL && temp == head)		//if first node should be deleted
	{
		head = temp->next;
		delete temp;
	}
	else if(temp != NULL)		//if any other node needs to be deleted
	{
		prev->next = temp->next;
		delete temp;
	}

	
}

/*Begin: code taken from CS204 lab linkedList.cpp*/
void deleteList(node * & head)		//deletes the whole list of nodes
{
	if( head == NULL);
	else
	{
		deleteList(head->next);
		delete head;
	}
}
/*End code taken from CS204 lab linkedList.cpp*/

int main()
{
	ifstream input;
	string fileName;

	do
	{
		cout << "Please enter file name: ";
		cin >> fileName;
		input.open(fileName.c_str());
		if(input.fail())
			cout << "Cannot find a file named " << fileName << endl;
		
	}while(input.fail());		//until file opens successfully 

	string line, card_number;
	int month, year; 
	node * head = NULL;

	while(getline(input, line))		
	{
		istringstream card_info(line);
		card_info >> card_number >> month >> year;
		bool isNewNode = true;			//new node will be created or not
		bool isFoundPlace = false;		//this is for finding right place for new node to add
		node * temp = head;
		node * prev = NULL;		//holds previous node

		while(temp != NULL && !(isFoundPlace))
		{
			if(temp->month == month && temp->year == year)		//given month and year already exists in a node
			{
				temp->credit_cards.push_back(card_number);
				isNewNode = false;		//no need to create a new node
				isFoundPlace = true;
			}
			else if((temp->year == year && temp->month > month) || temp->year > year)
			{
				isFoundPlace = true;
			}
			else
			{
				prev = temp;
				temp = temp->next;
			}
		}	
	
		if(isNewNode)
		{
			temp = new node(month, year);
			temp->credit_cards.push_back(card_number);
			if( prev != NULL)
			{
				temp->next = prev->next;
				prev->next = temp;
			}
			else		//new node is added to the head of the list
			{
				temp->next = head;
				head = temp;
			}
		}

		
		if(isNewNode)
		{
			cout << "\nNew node is created with expiration date: " << month << " " << year << endl;
			cout << "Credit card " << card_number << " added to node " << month << " " << year << endl;
			cout << "***************";
		}

		else
		{
			cout << "\nNode with expiration date " << month << " " << year << " already exists" << endl;
			cout << "Credit card " << card_number << " added to node " << month << " " << year << endl;
			cout << "***************";
		}
		
	}

	bool isTerminated = false;		
	string option;


	while(!isTerminated)		//until the user enters 4 as the option, this loop continues
	{
		cout << "\n\n1)Display List" << endl;
		cout << "2)Card Search via Credit Number" << endl;
		cout << "3)Delete Card with respect to Expiration Date" << endl;
		cout << "4)Exit\n" << endl;

		do
		{
			cout << "Please choose option from the menu: ";
			cin >> option;
			if(option != "1" && option != "2" && option != "3" && option != "4")
				cout << option << " is invalid option!" << endl;		
			
		}while(option != "1" && option != "2" && option != "3" && option != "4");		//until user enters a valid option
	

		if(option == "1")
		{
			displayList(head);		
		}
		else if(option == "2")
		{
			string credit_card_number;
			cout << "\nPlease enter the credit card number: ";
			cin >> credit_card_number;
			
			while(!(validCard(credit_card_number)))		//while card number is not a 16 character long integer
			{
				cout << "Invalid format!" << endl;
				cout << "Please enter the credit card number: ";
				cin >> credit_card_number;
			}
			
			cardFinder(credit_card_number, head);		//finding card in the list
		
		}
		else if(option == "3")
		{
			int card_month, card_year;
			bool valid_year = true;
			bool valid_month = true;
			cout << "\n";
			do
			{
				valid_year = true;		
				valid_month = true;
				cout << "Please enter month and year: ";
				if(!(cin >> card_month))		//non-integer month entered
				{
					string s;
					cin.clear();
					cin >> s;
					valid_month = false;
				}
				else		//if the entered month is an integer check if it is in range
				{
					if(card_month < 1 || card_month > 12)
						valid_month = false;
				}
				if(!(cin >> card_year))			//non-integer year entered
				{
					string a;
					cin.clear();
					cin >> a;
					valid_year = false;
				}
				if(!(valid_year) || !(valid_month))		//if year or month is invalid
				{
					cout << "Invalid Date!" << endl;
				}

			}while(!(valid_year) || !(valid_month));

			deleteCard(head, card_month, card_year);		//deletes cards with a given month and year from the list

		}
		else if(option == "4")
		{
			isTerminated = true;		//program ends
			cout << "Terminating!!!" << endl;
			deleteList(head);		//memory locations return to heap
			head = NULL;
		}
	}

	
	return 0;
}