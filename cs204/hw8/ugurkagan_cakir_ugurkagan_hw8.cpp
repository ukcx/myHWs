//Name: Ugur Kagan Cakir

#include <iostream>
#include <thread>
#include <mutex>
#include <random>
#include <time.h>
#include <chrono>
#include <iomanip> 
#include "ugurkagan_cakir_ugurkagan_HW8DynIntQueue.h"

using namespace std;


HW8DynIntQueue queue;			//shared queue object
int size = 0;					//size of the queue
int lastCustomerID = 0;			//id of the customer which is just processed by the cashier
mutex queueMutex, coutMutex;	//mutexes for cout and queue object


//Begin: code taken from cs204 lab week13
void printTime()	//print current time(now)
{
	
	time_t now = chrono::system_clock::to_time_t (chrono::system_clock::now());
	struct tm *ptm = new struct tm;  //creating the time struct to be used in thread
	localtime_s(ptm, &now);
	cout << put_time(ptm,"%X") << endl;
}
//End: code taken from cs204 lab week13


int random_range(const int & min, const int & max) 
{
	static mt19937 generator(time(0));
	uniform_int_distribution<int> distribution(min, max);
	return distribution(generator);
}

void cashier_1(const int & min, const int & max, const int & numOfCustomers)	//thread for cashier 1
{
	int rand = random_range(min, max);
	this_thread::sleep_for(chrono::seconds(rand));

	while((size > 0) || ((size == 0) && (lastCustomerID != numOfCustomers)) )	//when queue is not empty or there is customer left
	{
		if(size > 0)
		{
			int rand = random_range(min, max);
			int a, b;
			bool dequeued = false;	
		
			queueMutex.lock();
			if(!queue.isEmpty())	
			{
				queue.dequeue(lastCustomerID);
				size -= 1;
				dequeued = true;
				a = lastCustomerID;
			}
			queueMutex.unlock();

			if(dequeued)	//if cashier processed a customer
			{
				coutMutex.lock();
				cout << "Cashier 1 started transaction with customer " << a  << " (queue size is " << size << "): ";
				printTime();
				coutMutex.unlock();

				this_thread::sleep_for(chrono::seconds(rand));		//checkout time

				coutMutex.lock();
				cout << "Cashier 1 finished transaction with customer " << a << " ";
				printTime();
				coutMutex.unlock();
			}
		}

	}
}
void cashier_2(const int & threshold, const int & min, const int & max, const int & numOfCustomers)		//thread for cashier 2
{
	int rand = random_range(min, max);
	this_thread::sleep_for(chrono::seconds(rand));

	while((size > 0) || ((size == 0) && (lastCustomerID != numOfCustomers)) )	//when queue is not empty or there is customer left
	{
		if (size >= threshold)		//the number of people in queue is more than threshold value
		{
			int rand = random_range(min, max);
			bool dequed = false;
			int a;

			queueMutex.lock();
			if(!queue.isEmpty())
			{
				size -= 1;
				queue.dequeue(lastCustomerID);
				dequed = true;
				a = lastCustomerID;
			}
			queueMutex.unlock();

			if (dequed)		//if cashier processed a customer
			{
				coutMutex.lock();
				cout << "Cashier 2 started transaction with customer " << a << " (queue size is " << size << "): ";
				printTime();
				coutMutex.unlock();

				this_thread::sleep_for(chrono::seconds(rand));		//checkout time

				coutMutex.lock();
				cout << "Cashier 2 finished transaction with customer " << a << " ";
				printTime();
				coutMutex.unlock();
			}
		}	
	}
}
void allCustomers(const int & numOfCustomer, const int & min, const int & max)		//customer queue thread
{
	for( int i = 1; i <= numOfCustomer; i++)		//for each customer 
	{
		int rand = random_range(min, max);

		queueMutex.lock();
		size += 1;
		queue.enqueue(i);		//add a customer to the list
		queueMutex.unlock();

		coutMutex.lock();
		cout << "New customer with ID " << i << " has arrived (queue size is " << size << "): ";		//id's are from 1 to numOfCustomer
		printTime();
		coutMutex.unlock();
		

		this_thread::sleep_for(chrono::seconds(rand));
	}
}

int main()
{
	int numOfCustomers, thresholdValue, minArrival, maxArrival, minCheckout, maxCheckout;		//input variables
	cout << "Please enter the total number of customers: ";
	cin >> numOfCustomers;
	cout << "Please enter the number of customers waiting in the queue to open the second cashier: ";
	cin >> thresholdValue;
	cout << "Please enter the inter-arrival time range between two customers: " << endl;
	cout << "Min: ";
	cin >> minArrival;
	cout << "Max: ";
	cin >> maxArrival;
	cout << "Please enter the checkout time range of cashiers: " << endl;
	cout << "Min: ";
	cin >> minCheckout;
	cout << "Max: ";
	cin >> maxCheckout;
	cout << "Simulation starts ";
	printTime(); 

	thread customers(&allCustomers, numOfCustomers, minArrival, maxArrival);
	thread cashier1(&cashier_1, minCheckout, maxCheckout, numOfCustomers);
	thread cashier2(&cashier_2, thresholdValue, minCheckout, maxCheckout, numOfCustomers);


	customers.join();
	cashier2.join();
	cashier1.join();
	
	
	cout << "End of the simulation ends: ";
	printTime();

	return 0;
}