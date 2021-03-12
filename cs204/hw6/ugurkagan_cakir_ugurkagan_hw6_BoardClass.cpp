#include "ugurkagan_cakir_ugurkagan_hw6_BoardClass.h"
#include <iostream>

using namespace std;

//default constructor
Board::Board()
{
	for(int i = 0; i < 2; i++)
	{
		for(int j = 0; j < 6; j++)
			theBoard[i][j] = '-';
	}
}

//print out the board
void Board::displayBoard() const
{
	for(int i = 0; i < 2; i++)
	{
		for(int j = 0; j < 6; j++)
			cout << theBoard[i][j] << " ";
		cout << "\n";
	}
}

//get the char which is filling a given cell
char Board::getOwner(int row, int column) const
{
		return theBoard[row][column];
}

//set owner of a given cell
void Board::setOwner(int row, int column, char player) 
{
	if(row >= 0 && row < 2 && column >= 0 && column < 6)  
		theBoard[row][column] = player;
}

//true if all the cells of the board are filled by different chars than default char ('-')
bool Board::isFull() const
{
	for(int i = 0; i < 2; i++)
	{
		for(int j = 0; j < 6; j++)
		{
			if(theBoard[i][j] == '-')
				return false;
		}
	}
	return true;
}

//count the cells filled by a given char
int Board::countOwnedCells(char playerChar) const
{
	int count = 0;
	for(int i = 0; i < 2; i++)
	{
		for(int j = 0; j < 6; j++)
		{
			if(theBoard[i][j] == playerChar)
				count += 1;
		}
	}
	return count;
}