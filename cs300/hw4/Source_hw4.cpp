#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <unordered_map>
#include "ModifiedHeap.h"
using namespace std;

struct position	//struct to hold information of a seat in the stadium
{
	string block_name;		//name of the block that seat is located
	string row_name;		//name of the row that seat is located
	int column_num;			//number of the column that seat is located
	position::position(){}
	position::position(string blk_name, string row, int column)
	{
		block_name = blk_name;
		row_name = row;
		column_num = column;
	}
};

int main()
{
	string fileName = "inputs.txt";
	fstream input;
	ofstream output;
	input.open(fileName.c_str());
	output.open("outputs.txt");
	if(!(input.fail()))
	{
		vector<string> block_names;			//will hold names of the blocks
		vector<string> row_names;			//will hold names of the rows
		int numOfColumns;
		string line, block, row;
		getline(input, line);				//first line includes block names
		istringstream block_info(line);
		while(block_info >> block)
		{
			block_names.push_back(block);
		}

		getline(input, line);				//second line includes row names
		istringstream row_info(line);
		while(row_info >> row)
		{
			row_names.push_back(row);
		}
		
		getline(input, line);				//third line includes number of columns
		istringstream column_info(line);
		column_info >> numOfColumns;


		vector<string> columns;				//columns will be represented as vector of string in unordered_map (positionsInStadium object)
		for(int i=0; i < numOfColumns; i++)
		{
			columns.push_back("---");		//columns will be filled with "---" as default
		}
		ModifiedHeap blocks(block_names, row_names);					//heap object to keep 
		unordered_map < string, position > reservations;				//list of persons and their reservations
																		//names of costumers as keys; and position of the seats as values
		unordered_map <string, unordered_map<string, vector<string>>> positionsInStadium;	//list of seat positions in stadium	
																							//blocks as keys; rows as keys inside values; columns as values
		for(int i = 0; i < block_names.size(); i++)
		{
			for(int k = 0; k < row_names.size(); k++)
			{
				positionsInStadium[block_names[i]][row_names[k]] = columns;
			}
		}

		while(getline(input,line))
		{
			string function;
			istringstream info(line);
			info >> function;
			if(function == "print")			//print the positionsInStadium
			{
				output << "\n";
				for( auto const pair: positionsInStadium)	//pair is an iterator object; pair->first is a pointer to the keys; iterates through each block
				{
					output << pair.first << endl;
					output << "~~~~~~~" << endl;
					for( auto const pair2: pair.second)		//pair2 is an iterator object; pair2->first is a pointer to the keys inside values; iterates through each row
					{
						output << pair2.first << " : ";
						for( auto const pair3: pair2.second)	//pair3 is an iterator object; pair3's are columns; iterates through each column
						{
							output << pair3.substr(0, 3) << " ";
						}
						output << endl;
					}		
					output << "=======" << endl << endl;
				}	
			}
			else if(function == "reserve_seat")		//reserve the given seat to the customer
			{
				string custumer_name, block_name, row_name;
				int column_number;
				info >> custumer_name >> block_name >> row_name >> column_number;
				if(positionsInStadium[block_name][row_name][column_number] != "---")	//seat is already taken
				{
					output << custumer_name <<  " could not reserve a seat!" << endl;
				}
				else if(reservations.find( custumer_name ) != reservations.end())		//the customer already has a reservation
				{
					output << custumer_name <<  " could not reserve a seat!" << endl;
				}
				else
				{
					position pos(block_name,row_name, column_number);
					blocks.insert_to(block_name, row_name);								//insert to heap to keep track of fullness of rows for each block
					positionsInStadium[block_name][row_name][column_number] = custumer_name;	//costumers name added to columns vector
					reservations[custumer_name] = pos;											//the position of seat is added as customers reservation
					output << custumer_name << " has reserved " << block_name << " " << row_name << "-" << column_number << endl;
				}
			}
		else if(function == "reserve_seat_by_row")		//reserve a seat at a given row
			{
				string custumer_name, row_name;
				info >> custumer_name >> row_name;
				if(reservations.find( custumer_name ) != reservations.end())		//the customer already has a reservation
				{
					output << custumer_name << " could not reserve a seat!" << endl;
				}
				else
				{
					string	availableBlock	=	"";
					bool isAvailable = blocks.insert_and_return_block(availableBlock, row_name, numOfColumns);
					if(!isAvailable)		//for the given row, all the blocks are completely full
					{
						output << custumer_name << " could not reserve a seat!" << endl;
					}
					else
					{
						int i = 0;
						for(; i < positionsInStadium[availableBlock][row_name].size(); i++)
						{
							if(positionsInStadium[availableBlock][row_name][i] == "---")	//find an empty seat
							{
								break;
							}
						}
						position pos(availableBlock, row_name, i);
						positionsInStadium[availableBlock][row_name][i] = custumer_name;	//costumers name added to columns vector
						reservations[custumer_name] = pos;									//the position of seat is added as customers reservation
						output << custumer_name << " has reserved " << availableBlock << " " << row_name << "-" << i << " by emptiest block" << endl;
					}
				}
			}
			else if(function == "get_seat")		//get the position of the seat reserved by given customer
			{
				string custumer_name;
				info >> custumer_name;
				if(reservations.find( custumer_name ) == reservations.end())		//the customer does not have a reservation
				{
					output << "There is no reservation made for " << custumer_name << "!" << endl;
				}
				else
				{
					unordered_map<string, position>::iterator costumors_seat = reservations.find( custumer_name );
					string blockName = costumors_seat->second.block_name;		//the block the seat located
					string rowName = costumors_seat->second.row_name;			//the row the seat located
					int columnNum = costumors_seat->second.column_num;			//the column the seat located
					output << "Found that " << custumer_name << " has a reservation in " << blockName <<	" " << rowName << "-" << columnNum << endl;
				}
			}
			else if(function == "cancel_reservation")		//cancel the reservation of the given customer
			{
				string custumer_name;
				info >> custumer_name;
				if(reservations.find( custumer_name ) == reservations.end())		//the customer does not have a reservation
					output << "Could not cancel the reservation for " << custumer_name << "; no reservation found!" << endl;
				else
				{
					unordered_map<string, position>::iterator costumors_seat = reservations.find( custumer_name );
					string blockName = costumors_seat->second.block_name;				//the block the seat located
					string rowName = costumors_seat->second.row_name;					//the row the seat located
					int columnNum = costumors_seat->second.column_num;					//the column the seat located
					positionsInStadium[blockName][rowName][columnNum] = "---";			//empty the seat where the customer cancelled the reservation
					blocks.removeSeat(blockName, rowName);								//remove 1 seat from given row and block to keep count
					reservations.erase(custumer_name);									//delete the reservation from the list of reservations
					output << "Cancelled the reservation of " << custumer_name << endl;
				}
			}
		}
		reservations.erase(reservations.begin(), reservations.end());						//erase all elements from the unordered_maps
		positionsInStadium.erase(positionsInStadium.begin(), positionsInStadium.end());
	}
	input.close();
	output.close();
	return 0;
}