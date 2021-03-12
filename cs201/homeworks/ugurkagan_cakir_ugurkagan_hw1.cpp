
#include <iostream>
#include <string>

using namespace std;

int main()

{
	string name;
	double outcallperminute,incallperminute,price_of_internet_usage_per_MB, how_many_GBs,price_of_one_sms;
	int outcallminutes,incallminutes,number_of_sms;
	double out_call_cost,in_call_cost,internet_cost,cost_of_sms,total_cost,total_tax,total_bill;


	cout << "Please enter your name: ";
	cin >> name;
	cout << "\n";

	cout << name << ", please enter the price for outgoing call per minute: ";
	cin >> outcallperminute;
	cout << name << ", please enter how many minutes you have talked in outgoing calls: ";
	cin >> outcallminutes;
	out_call_cost =  outcallperminute * outcallminutes;							//calculating total cost of outgoing calls
	cout << name << ", you have spent " << out_call_cost << " TL for outgoing calls you made while you are abroad." <<endl;
	cout << "\n";
	
	cout << name << ", please enter the price for incoming call per minute: ";
	cin >> incallperminute;
	cout << name << ", please enter how many minutes you have talked in incoming calls: ";
	cin >> incallminutes;
	in_call_cost = incallperminute * incallminutes;								//calculating total cost of incoming calls
	cout << name << ", you have spent " << in_call_cost << " TL for incoming calls you made while you are abroad." <<endl;
	cout << "\n";

	cout << name << ", please enter the price for internet usage per MB: ";
	cin >> price_of_internet_usage_per_MB;
	cout << name << ", please enter how many GBs you have used: ";
	cin >> how_many_GBs;
	internet_cost = how_many_GBs * 1024 * price_of_internet_usage_per_MB;		//calculating the cost of the internet
	cout << name << ", you have spent " << internet_cost << " TL for the internet while you are abroad." <<endl;
	cout << "\n";

	cout << name << ", please enter the price for one SMS: ";
	cin >> price_of_one_sms;
	cout << name << ", please enter the number of SMS you have sent: ";
	cin >> number_of_sms;
	cost_of_sms = price_of_one_sms * number_of_sms;								//calculating total cost of sms's
	cout << name << ", you have spent " << cost_of_sms << " TL for the SMS while you are abroad." << endl;
	cout << "\n";

	total_cost = out_call_cost + in_call_cost + internet_cost + cost_of_sms;				//cost without tax
	total_tax = total_cost * 18 / 100;														//amount of tax
	total_bill = total_cost + total_tax;													//total cost including tax

	cout << name << ", total cost for all roaming services is " << total_cost << " TL." <<endl;
	cout << name << ", tax is " << total_tax << " TL." <<endl;
	cout << name << ", total roaming bill fee with tax is " << total_bill << " TL." <<endl; 


	
}
