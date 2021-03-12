/*
Name: Ugur Kagan
Surname: Cakir
*/

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include "ugurkagan_cakir_ugurkagan_hw3_CardList.h"

using namespace std;

bool isValidCardNumber(string card_number) //checks the given credit card number is valid or not
{
	if(card_number.length() == 16)
	{
		for(int i = 0; i < card_number.length(); i++)
		{
			if(card_number[i] < '0' || card_number[i] > '9')		//must be all numbers
				return false;
		}
	}
	else
		return false;
	
	return true;
}

int main()
{
	CardList allCards;		//defaulty head and tail of the object points to null
	bool isTerminated = false;
	string option;
	
	do
	{
		cout << "\n1) Upload Card(s) from a File" << endl;
		cout << "2) Display List Chronological" << endl;
		cout << "3) Display List Reverse Chronological" << endl;
		cout << "4) Card Search" << endl;
		cout << "5) Bulk Delete" << endl;
		cout << "6) Exit" << endl;
		cout << "Please choose option from the menu: ";

		cin >> option;

		if(option == "1")
		{
			ifstream input;
			string fileName;
			
			cout << "Please enter file name: ";
			cin >> fileName;
			input.open(fileName.c_str());
			cout << "\n";

			if(input.fail())
				cout << "Could not find a file named " << fileName << endl;
			else
			{
				string line;
				while(getline(input, line))
				{
					string cardNum;
					int mon, year;
					istringstream card_information(line);
					card_information >> cardNum >> mon >> year;
					allCards.insertCard(cardNum, mon, year);			//insert a card with parameters taken from the file
				}
			}
		}
		else if(option == "2")
		{
			allCards.displayListChronological();
		}
		else if(option == "3")
		{
			allCards.displayListReverseChronological();	
		}
		else if(option == "4")
		{
			string credit_card_number;
			cout << "Please enter the credit card number: ";
			cin >> credit_card_number;
			
			if(isValidCardNumber(credit_card_number))					//credit card number is in the right format
				allCards.cardSearch(credit_card_number);
			else				
			{
				cout << "Invalid format!" << endl;
			}

		}
		else if(option == "5")
		{
			int card_month, card_year;
			bool valid_year = true;
			bool valid_month = true;
			cout << "Please enter month and year: ";
			if(!(cin >> card_month))		//user entered a non-integer month value
			{
				string s;
				cin.clear();
				cin >> s;
				valid_month = false;
			}
			else		
			{
				if(card_month < 1 || card_month > 12)	
					valid_month = false;
			}
			if(!(cin >> card_year))			//user entered a non-integer year value
			{
				string a;
				cin.clear();
				cin >> a;
				valid_year = false;
			}
			if(!(valid_year) || !(valid_month))		//at least one of the month and year is in the wrong format
			{
				cout << "Invalid format!" << endl;
			}
			else
			{
				allCards.bulkDelete(card_month, card_year);
			}

		}
		else if(option == "6")
		{
			allCards.deleteAll();			//all dynamically located memory area will return to the heap
			isTerminated = true;
			cout << "All the nodes have been deleted!" << endl;
			cout << "Terminating!!!" << endl;
		}
		else
		{
			cout << "Invalid operation!" << endl;
		}

	}while(!isTerminated);			//option is not equal to 6


	return 0;
}