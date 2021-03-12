#include <iostream>
#include <string>
using namespace std;

int main()
{
	string name;
	cout << "Welcome to Pequod's Coffee! Can you tell me your name?" << endl;
	cin >> name;							
	cout << "Dear " << name << ", would you kindly answer our questions, so we can determine the coffee you want."<<endl;
	
	void coffee_maker(string);				//this function will be defined later


	coffee_maker(name);

	return 0;
}

void coffee_maker(string name)
{
		
	string coffee_type;

	bool ingredient_checker(string);			//this functions will be defined later
	bool equality_checker(string,string);
	void displayCoffee_type(string,string);
	
												//with the operators below, we will find the coffee that user wants
	if (!ingredient_checker("espresso")){       //coffee_type variable stores the type of coffee which would be gathered by if else conditions
			coffee_type = "a filtered coffee";}
		
		else 
		{
			if (!ingredient_checker("milk"))
			{
				if (!ingredient_checker("water")){
					coffee_type = "an espresso";}
				else{
					coffee_type = "an americano";}
			}
			
			else 
			{
				if (ingredient_checker("hot chocolate")){
					coffee_type = "a mocha";}
				else
				{
					if (!ingredient_checker("foam")){
						coffee_type = "a cafe au lait";}
					else 
					{
						if (equality_checker("foam","milk")){
							coffee_type = "a cappucino";}
						else{
							coffee_type = "a latte";}
					}
				}
			 }
		}

	displayCoffee_type(name,coffee_type);
}

bool ingredient_checker(string ingredient)				//this function takes an ingredient as the parameter 
{                                                       //if user wants ingredient enters yes otherwise enters no
		string answer;
		cout << "Does it have " + ingredient + "?" << endl;		
		cin >> answer;
		
	if (answer == "yes"){
			return true;}
		
	else{
			return false;}
}

bool equality_checker(string ingrdnt1, string ingrdnt2)		//this function takes 2 ingredients as parameters 
{                                                           //if user wants equal amount of ingredients enters yes otherwise enters no
		string answer;
		cout << "Do " + ingrdnt1 +" and " + ingrdnt2 +" are in equal amounts?" << endl;
		cin >> answer;

		if (answer == "yes"){
			return true;}
		else{
			return false;}
}

void displayCoffee_type(string name, string type_of_coffee)		//this function displays the coffee that user wants.
{
		cout << "Your order is ready " + name + "! What you want is " + type_of_coffee + ". Enjoy!" <<endl;
}

