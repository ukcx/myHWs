/*
	Name: Ugur Kagan
	Surname: Cakir
*/

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>


using namespace std;


void matrixPrinter(const vector <vector <char>> & user_matrix)		//this function prints the matrix with char type, used for printing out matrix of text file
{
	for(int i=0; i < user_matrix.size(); i++)
	{
		for(int k=0; k < user_matrix[i].size(); k++)
			cout << user_matrix[i][k] << " ";
		cout << "\n";
	}
}

void matrixPrinter(const vector <vector <int>> & user_matrix)		//prints the matrix with int type, used for printing out visited points' coordinates
{
	for(int i=0; i < user_matrix.size(); i++)
	{
		for(int k=0; k < user_matrix[i].size(); k++)
			cout << user_matrix[i][k] << "  ";
		cout << "\n";
	}
	cout << endl;
}

bool isOccupied(const vector <vector <char>> & user_matrix, int x_coordinate , int y_coordinate)		//checks a given coordinate occupied or not
{
	if(user_matrix[x_coordinate][y_coordinate] == 'x')
		return true;
	return false;
}

bool isVisited(const vector <vector <int>> & visited_points, int x, int y)		//checks a given coordinate is visited before or not
{
	bool visited = false;
	for (int i = 0; i < visited_points.size(); i++)
	{
		if (visited_points[i][0] == x)
		{
			if (visited_points[i][1] == y)
				visited = true;
		}
	}
	return visited;
}

bool findPath(const vector <vector <char>> & user_matrix, vector <vector <int>> & visitedPoints_so_far , int & x_coor, int & y_coor)		//returns if we can find a path to move or not
{
	int x_boundary_point = user_matrix.size();
	int y_boundary_point = user_matrix[0].size();
	if (y_coor + 1 < y_boundary_point)				//first if statements check boundaries
	{
		if( isOccupied(user_matrix, x_coor, y_coor + 1) && !(isVisited(visitedPoints_so_far, x_coor, y_coor + 1)))			//if appropriate to move to that point or not
		{                                                                                                                   //that point is not visited before and is occupied 
			y_coor += 1;		//go right
			return true;		//can move
		}
	}
	if (x_coor + 1 < x_boundary_point)		//check boundaries
	{
		if( isOccupied(user_matrix, x_coor + 1, y_coor) && !(isVisited(visitedPoints_so_far, x_coor + 1, y_coor)))
		{
			x_coor += 1;		//go down
			return true;
		}	
	}
	if(y_coor -1 >= 0)						//check boundaries
	{
		if(isOccupied(user_matrix, x_coor, y_coor - 1) && !(isVisited(visitedPoints_so_far, x_coor, y_coor - 1)))
		{
			y_coor -= 1;		//go left
			return true;
		}
	}
	if(x_coor - 1 >= 0)						//check boundaries
	{
		if(isOccupied(user_matrix, x_coor - 1, y_coor) && !(isVisited(visitedPoints_so_far, x_coor - 1, y_coor)))
		{
			x_coor -= 1;		//go up
			return true;
		}
	}
	return false;
}

bool isEnclosed(const vector <vector <int>> & allVisitedPoints)			//if the founded path is enclosed or not
{
	int vector_size = allVisitedPoints.size();
	int last_x = allVisitedPoints[vector_size - 1][0];					//last point's x coordinate
	int last_y = allVisitedPoints[vector_size - 1][1];					//last point's y coordinate
	int first_x = allVisitedPoints[0][0];								//first point's x coordinate
	int first_y = allVisitedPoints[0][1];								//first point's y coordinate
	bool enclosed = false;

	if(vector_size >= 4)												//an enclosed area consists of at least 4 points
	{
		if((last_x == first_x) && ((last_y - first_y == -1 ) || (last_y - first_y == 1)))			//if the first point and the last point are next to or on top of each other the area is enclosed
		{
			enclosed = true; 
		}
		if((last_y == first_y) && ((last_x - first_x == -1 ) || (last_x - first_x == 1)))
		{
			enclosed = true;
		}
	}
	return enclosed;
}

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

	}while(input.fail());				//until the file successfully opens

	string line;
	int numOfElements = -1;				//number of elements in a row of matrix, initialized at -1 but it will change after reading first row of the matrix
	bool allXandO = true;				//if matrix consists of just x's and o's or not
	bool equalChars = true;				//if matrix has equal amount of characters in each row or not
	vector<vector<char>> matrixLines;		//this matrix will store the lines of the matrix


	while(getline(input,line) && equalChars && allXandO)
	{
		istringstream getChar(line);
		char character;
		int charCount = 0;
		vector <char> aLineOfMatrix;
		

		while(getChar >> character)
		{
			aLineOfMatrix.push_back(character);
			charCount++;
			if(character != 'x' && character != 'o')	//if there exist a character in matrix other than x and o
			{
				allXandO = false;
			}
		}
		matrixLines.push_back(aLineOfMatrix);
		
		if(numOfElements == -1)				//this would happen in first iteration
			numOfElements = charCount;
		else if(numOfElements != charCount)		
			equalChars = false;

	
	}
	
	if(!allXandO)
		cout << fileName << " includes invalid char(s)" << endl;
	else if(!equalChars)
		cout << fileName << " is invalid matrix, does not contain same amount of char each row!" << endl;
	
	bool validMatrix = false;
	if(equalChars && allXandO)			//if these statements are true we have a valid matrix
		validMatrix = true;

	if(validMatrix)
	{
		cout << "Input Matrix:" << endl;
		
		matrixPrinter(matrixLines);
		
		int x, y;						//coordinates
		int max_x = matrixLines.size()-1;
		int max_y = matrixLines[0].size()-1;
		bool isTerminated = false;		

		while(!(isTerminated))				//until the user enters -1 -1 this loop continues
		{
			cout << "Please enter starting coordinates, first row X then column Y: ";
			if(!(cin >> x >> y))			//if the input x and/or y not in the int type
			{
				cout << "Invalid Coordinates\n" << endl;
				string s, a;
				cin.clear();			
				cin >> s;
				cin.clear();
				cin >> a;
			}
			
			else
			{
				if(x == -1 && y == -1)			
				{
					cout << "Terminating..." << endl;
					isTerminated = true;				//program ends
				}

				else if (!(0 <= x && x <= max_x && 0 <= y && y <= max_y))	//x and y are out of range, but not -1 -1 
					cout << "Invalid Coordinates\n" << endl;
					

				else									//user entered x and y are in the range and in the right format 
				{
					if(!(isOccupied(matrixLines, x, y)))			//entered point is not occupied
					{
						cout << "This cell is not occupied!\n" << endl;
					}
					else
					{
						vector <vector <int>> visited_points;			//this matrix will store all the points are being visited
						int new_x = x;			//new_x and new_y values will be updated to the next point we move in each iteration below  
						int new_y = y;
						
						do
						{
							vector <int> point;		
							point.push_back(new_x);
							point.push_back(new_y);
							visited_points.push_back(point);			

						}while(findPath(matrixLines, visited_points, new_x, new_y));		//findPath function updates new_x and new_y values if it founds a new point to visit
																							//if we can find a point to visit then findPath = true

						if( isEnclosed(visited_points))				//the founded area is an enclosed one
						{
							cout << "Found an enclosed area. The coordinates of the followed path: " << endl;
							matrixPrinter(visited_points);
						}
						else if( !isEnclosed(visited_points))
						{
							cout << "Cannot found an enclosed area starting with given coordinate. The coordinates of the followed path: " << endl;
							matrixPrinter(visited_points);
						}

					}
		
		
				}
			}
		}
	}


	return 0;
}