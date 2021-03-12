#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include "PointQuadTree.h"

using namespace std;

int main()
{
	fstream in, input;
	string cityFile = "cities.txt";
	string queryFile = "queries.txt";
	in.open(cityFile.c_str());
	input.open(queryFile.c_str());

	if(!(in.fail()) && !(input.fail()))		//both of the files are needed to be opened
	{
		string line;
		int upprLimX, upprLimY;
		PointQuadTree cities;
		getline(in, line);					//the first line in the cities.txt file, contains upper limit for coordinates
		istringstream coordinates(line);
		coordinates >> upprLimX >> upprLimY;

		while(getline(in, line))
		{
			string city;
			int x_coor, y_coor;
			istringstream info(line);
			info >> city >> x_coor >> y_coor;
			if((x_coor >= 0) && (x_coor < upprLimX) && (y_coor < upprLimY) && (y_coor >= 0))	//coordinates in range
			{
				cities.insert(city, x_coor, y_coor);
			}
		}
		cities.pretty_print();		//print point quadtree
		in.close();

		int radius, x, y;
		string queries;
		while(getline(input,queries))	
		{
			vector<string> visited_cities;		//cities visited during the search operation, this vector will be updated in citiesInside function
			vector<string> cities_in_radius;	//cities that are found within the radius of the given point, this vector will be updated in citiesInside function
			string info = "";
			int index;
			int len = queries.length();
			while((index = queries.find(",")) != string::npos)		//to get rid of ',' character in a line of the queries.txt file
			{
				info += queries.substr(0, index) + " ";
				queries = queries.substr(index + 2, len);
			}
			info += queries;
			istringstream query(info);
			query >> x >> y >> radius;

			cities.citiesInside(x, y, radius, visited_cities, cities_in_radius);	//visited_cities and cities_in_radius are updated
			string citiesInRadiusNames = "";
			string visitedCityNames = "";
			unsigned int i = 0;
			if(cities_in_radius.size() == 0)	//no city in radius
			{
				cout << "\n" << "<None>" << endl;
			}
			else
			{
				for(; i <= cities_in_radius.size() - 1 ; i++)
				{
					citiesInRadiusNames += cities_in_radius[i] + ", ";
				}
				cout << "\n" << citiesInRadiusNames.substr(0, citiesInRadiusNames.length()-2) << endl;  //all the cities found within radius during the search operation printed with ',' seperator
			}

			i = 0;
			for(; i <= visited_cities.size() - 1; i++)
			{
				visitedCityNames += visited_cities[i] + ", ";
			}
			cout << visitedCityNames.substr(0, visitedCityNames.length()-2) << endl;	//all the cities visited during search operation printed with ',' seperator
		}
		input.close();
	}
	else	//if at least one of the files can not be opened
	{
		cout << "Can not open the files!";
	}

	return 0;
}