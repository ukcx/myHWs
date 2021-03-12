#include <iostream>
#include <string>
using namespace std;

bool choice_check(string choice) // decides if we get user's string or not
{
	bool flag;
	if (choice == "3")
	{
		cout << "See you!" << endl;
		flag = false;
	}
	else if (choice == "1")
	{
		flag = true;
	}
	else if (choice == "2")
	{
		flag = true;
	}
	else
	{
		flag = false;
	}
	
	return flag;
}
bool choice1_checker(string source) // checks source_function
{                                   // if appropriate or not
	bool flag = true;
	if  (source.length() == 0)
	{
		flag = false;
	}
	else
	{
		for (int k=0; k < source.length(); k++)
		{
			if (!( source.at(k) >= 'a' && source.at(k) <= 'z' ))
			{
				flag = false;
			}
		}
	}
	
	return flag;
}

bool choice2_checker(string search, string source_string) // checks search_string
{                                                         // if appropriate or not
	bool flag = true;
	int count = 0;
	if  (search.length() > 0 && search.length() <= source_string.length())
	{
		for (int k=0; k < search.length(); k++)
		{
			if (!( search.at(k) >= 'a' && search.at(k) <= 'z' ))
			{
				if ( search.at(k) == '?')
				{
					count += 1;
				}
				else
				{
					flag = false;
				}
			}
		}
		if (count == search.length())
		{
			flag = false;
		}
	}
	else
	{
		flag = false;
	}
	
	return flag;


}

void string_search(string search_text, string source_text) // search string without ?
{
	int count = 0;
	
		for (int i=0; i < source_text.length(); i++)
		{
			if (source_text.substr(i, search_text.length()) == search_text)
			{
				cout << "\n\"" << search_text << "\" has been found at index " << i << endl; 
				count += 1;
			}
		}
		if (count == 0)
		{
			cout << " no match has been found.";		
		}
		
}	
	
void wild_card(string search,string source) // search string with ?
{
	int cnt = 0;
	int count = 0;
	for (int y=0; y < source.length(); y++)
	{
		string substr = source.substr(y,search.length());
		for (int r=0; r < substr.length(); r++)
		{
			if (substr.at(r) == search.at(r))
			{
				cnt += 1;
			}
			if (search.at(r) == '?')
			{
				cnt += 1;
			}
			if (cnt == search.length())
			{
			
				cout << "\n\"" << substr << "\" has been found at index " << y;
				count += 1;
			}
		
		}
		cnt = 0;
	}
	if (count == 0)
		{
			cout << " no match has been found.";		
		}

}
int main()
{
	string user_string, choice, search_string, source_string;
	source_string = "";			// initializations
	search_string = "";

	cout << "This program searches a search string in a source string with the option of wildcards.\n\n" <<
	"Example inputs with their meaning in parantheses:\n" <<
	"1 thislectureisawesome (to enter a new source string)\n" <<
	"2 lecture (to enter a new source string)\n" << 
	"2 t?r? (to enter a source string with wildcards)  \n" <<
	"3 (to exit the program)\n" << endl;

	cout << "Enter your choice and string: ";
	cin >> choice;
	
	if(choice_check(choice))
	{
		cin >> user_string;
	}

	while (choice != "3")
	{
		if (choice == "1")
		{
			
			if (choice1_checker(user_string))
			{
				source_string = user_string;
				cout << "Source word has been changed to \"" << source_string << "\"";
			}
			else
			{
				cout << "Wrong input format! Try again.";
			}
			
		}
		else if (choice == "2")
		{
			if (choice2_checker(user_string, source_string))
			{
				search_string = user_string;
				cout << "For the source word \"" << source_string << "\" and search word \"" << search_string << "\",";
				unsigned int index;
				index = search_string.find("?");
				
				if (index == string::npos)	// search string not including ? 
				{
					string_search(search_string, source_string);
				}
				else                        // search string including ?
				{
					wild_card(search_string, source_string);
				}
			}
			else
			{
				cout << "Wrong input format! Try again.";
			}
			
		}
		else
		{
			cout << "Choice can be 1, 2 or 3! Try again.";
		}
		
		cout << "\n\n";
		cout << "Enter your choice and string: ";
		cin >> choice;
			
		if(choice_check(choice))
		{
			cin >> user_string;
		}
		
	}
	
	
	
	
	
	
	return 0;
}