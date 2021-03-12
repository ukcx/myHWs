
#include <iostream>
#include <string>
#include <fstream>
#include "ugurkagan_cakir_ugurkagan_hw4_DynStack.h"

using namespace std;

bool takeInt(string & wrongInput, int & integer)		//this function takes integer input from user
{														//if it fails, it returns the wrong input as a string as a reference parameter
	int intInput;
	if(!(cin >> intInput))		//if the input isn't an integer
	{
		cin.clear();
		cin >> wrongInput;
		return false;			//input isn't an integer
	}
	
	integer = intInput;
	return true;				//input is in integer type
}

bool isStucked(char ** matrix, int row, int column)
{
	if(matrix[row + 1][column] != ' ' && matrix[row - 1][column] != ' ' && matrix[row][column + 1] != ' ' && matrix[row][column - 1] != ' ')
		return true;	//all directions(up, left, right, down) have occupied in the matrix, so there is no way to move, it is stuck
	else
	{
		return false;
	}
	
}

void deleteMatrix(char ** &matrix, int rows)		//this function deletes the dynamically allocated char matrix 
{
	for (int i = 0; i < rows; i++)
	{
		delete [] matrix[i];
	}
	delete [] matrix;
}

int main()
{
	int rows = 3;		
	int columns = 3;
	string wrongRowsValue, wrongColumnsValue;

	cout << "Enter the number of rows: ";
	while((!takeInt(wrongRowsValue, rows)) || rows < 3)	//if an integer row value is entered, rows will change and we can check if it is smaller than 3
	{
		if(rows < 3)
		{
			cout << rows << " is not valid!" << endl;
			rows = 3;		
		}
		else	
			cout << wrongRowsValue << " is not valid!" << endl;
		
		cout << "Enter the number of rows: ";
	}

	cout << "Enter the number of columns: ";
	while((!takeInt(wrongColumnsValue, columns)) || columns < 3) //if an integer column value is entered, columns will change and we can check if it is smaller than 3
	{
		if(columns < 3)
		{
			cout << columns << " is not valid!" << endl;
			columns = 3;
		}
		else
			cout << wrongColumnsValue << " is not valid!" << endl;
		
		cout << "Enter the number of columns: ";
	}

	char** matrix = new char*[rows];		//this char matrix will hold the map that is in a text file
	for (int i = 0; i < rows; i++)
		matrix[i] = new char[columns];

	ifstream input;
	string fileName;
	
	do
	{
		cout << "Please enter file name: ";
		cin >> fileName;
		input.open(fileName.c_str());
		if(input.fail())
			cout << "Cannot open a file named " << fileName << endl;

	}while(input.fail());		

	char matrix_char;
	string line;
	int lines = 0;			//the row index we are at while reading the file
	int position = 0;		//the column index we are at while reading the file
	
	while(getline(input,line))		//reading text file a line at a time
	{
		for(position = 0; position < columns; position++)	//move further through a line of the text file
		{
			matrix_char = line.at(position);
			matrix[lines][position] = matrix_char;
		}
		lines++;			//iterations are done in the taken line, move to the next line
	}

	int startingRow = -1;
	int startingColumn = -1;
	bool validStartingPoint;
	string wrongStartingRow, wrongStartingColumn;

	do
	{
		validStartingPoint = true;		
		cout << "Enter the starting point: ";
		
		if(!(takeInt(wrongStartingRow, startingRow) && startingRow > 0 && startingRow < rows))	
			validStartingPoint = false;		//starting row isn't an integer that is bigger than 0 and smaller than rows value
		
		if(!(takeInt(wrongStartingColumn, startingColumn) && startingColumn > 0 && startingColumn < columns))
			validStartingPoint = false;		//starting column isn't an integer that is bigger than 0 and smaller than columns value
		
		if(!validStartingPoint)
			cout << "Invalid coordinate!" << endl;

	}while(validStartingPoint == false);	//starting row or starting column or both are not in the correct format


	if(matrix[startingRow][startingColumn] == 'X')
	{
		cout << "Starting point is already occupied." << endl;
		cout << "Terminating..." << endl;
	}
	else
	{
		char filling_char;
		
		do
		{
			cout << "Enter the filling char: ";
			cin >> filling_char;
			if(filling_char == 'X' || filling_char == 'x')		
			{
				cout << "Filling char is not valid!" << endl;
			}
		
		}while(filling_char == 'X' || filling_char == 'x');
		
		DynStack filledPoints;										//will contain the points visited by program
		int newPointsRow = startingRow;
		int newPointsColumn = startingColumn;
		filledPoints.push(newPointsRow, newPointsColumn);			//starting point is pushed to the empty stack
		matrix[newPointsRow][newPointsColumn] = filling_char;

		do
		{

			if(matrix[newPointsRow][newPointsColumn] == filling_char && isStucked(matrix, newPointsRow, newPointsColumn)) 
			{					//the point is already filled and also there is no available direction to move from that point
				do
				{
					filledPoints.pop(newPointsRow, newPointsColumn);

				}while(isStucked(matrix, newPointsRow, newPointsColumn) && !filledPoints.isEmpty()); //if filledpoints is empty pop operation can not be done
			}
			
			else
			{
				if(matrix[newPointsRow + 1][newPointsColumn] == ' ')			//move down 
					newPointsRow += 1;
				else if(matrix[newPointsRow][newPointsColumn + 1] == ' ')		//move right
					newPointsColumn += 1;
				else if(matrix[newPointsRow -1][newPointsColumn] == ' ')		//move up
					newPointsRow -= 1;
				else if(matrix[newPointsRow][newPointsColumn - 1] == ' ')		//move left
					newPointsColumn -= 1;
																				
				filledPoints.push(newPointsRow, newPointsColumn);				
				matrix[newPointsRow][newPointsColumn] = filling_char;			//fill the point in the matrix that we have moved to
																				//in the case where we can't move, fill the point that we are at
			}


		}while(!(filledPoints.isEmpty() && isStucked(matrix, newPointsRow, newPointsColumn)));		//all the blank chars are replaced by filling char in the boundary made by X's

		for(int i = 0; i < rows; i++)	//print out the char matrix			
		{
			for(int k = 0; k < columns; k++)
			{
				cout << matrix[i][k];
			}
			cout << "\n";
		}
	}
	
	deleteMatrix(matrix, rows);		//return the dynamically allocated memory to the heap


	return 0;
} 