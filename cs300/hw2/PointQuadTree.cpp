#include "PointQuadTree.h"
#include <iostream>
#include <vector>
#include <math.h>
using namespace std;

PointQuadTree::PointQuadTree()	//empty point quadree
{
	root = nullptr;
}

PointQuadTree::~PointQuadTree()		//destructor
{
	for(unsigned int i = 0; i < duplicates.size(); i++)
	{
		cout << "These cities weren't inserted: " <<  duplicates[i] << "\t";	//if there were duplicate coordinates with different cities
	}
	deleteAll(root);
}

void PointQuadTree::deleteAll(cityNode * &subtree)		//recursively deletes elements from the tree
{
	if(subtree == nullptr) return;

	deleteAll(subtree->ne);
	deleteAll(subtree->nw);
	deleteAll(subtree->se);
	deleteAll(subtree->sw);

	delete subtree;
}

void PointQuadTree::insert(string city, int x, int y)	//calls private version
{
	insert(root, city, x, y);	
}

void PointQuadTree::insert(cityNode * &rootNode, string city, int x, int y)		//recursively searches for the spot to the node to be added, adds the node to that position
{
	if( rootNode == nullptr)
	{
		rootNode = new cityNode(city, x, y);
	}
	else if(x == rootNode->xCoord && y == root->yCoord )
	{
		duplicates.push_back(city);
		cout << "Can not insert " << city << ". There is another city with the same coordinates!" << endl;
	}
	else if(x < rootNode->xCoord && y < rootNode->yCoord)	//coordinates are to the southwest of the rootNode
	{
		insert(rootNode->sw, city, x, y);
	}
	else if(x < rootNode->xCoord && y >= rootNode->yCoord)	//coordinates are to the northwest of the rootNode
	{
		insert(rootNode->nw, city, x, y);
	} 
	else if(x >= rootNode->xCoord && y < rootNode->yCoord)	//coordinates are to the southeast of the rootNode
	{
		insert(rootNode->se, city, x, y);
	}
	else if(x >= rootNode->xCoord && y >= rootNode->yCoord)	//coordinates are to the northeast of the rootNode
	{
		insert(rootNode->ne, city, x, y);
	}
}

void PointQuadTree::pretty_print()		// pretty print the quadtree rooted at root:
{ 
	pretty_print(root);
}

void PointQuadTree::pretty_print(cityNode * ptr)		// pretty print the quadtree rooted at root:
{ 
	if (ptr != NULL)	// if the tree is not empty
	{ 
		cout << ptr->name << endl;
		pretty_print(ptr->se);	// recursively print the south east subtree
		pretty_print(ptr->sw);	// recursively print the south west subtree
		pretty_print(ptr->ne);	// recursively print the north east subtree
		pretty_print(ptr->nw);	// recursively print the north west subtree
	}
}

void PointQuadTree::citiesInside(int x, int y, int rad, vector<string> & visited_cities, vector<string> & cities_in_radius)	//calls the private version
{
	if(rad >= 0)	//min value for radius is 0
	{
		citiesInside(root, x, y, rad, visited_cities, cities_in_radius);
	}
	else
	{
		cout << "Radius can not be less than 0" << endl;
	}
}

/*
	recursively check subtrees to find the cities within radius, update the cities_in_radius to return the cities found
	also returns the cities visited during the search operation. update the visited_cities to return the cities visited
*/
void PointQuadTree::citiesInside(cityNode * rootNode, int x, int y, int rad, vector<string> & visited_cities, vector<string> & cities_in_radius)
{
	if(rootNode != nullptr)
	{
		visited_cities.push_back(rootNode->name);
		double distance = sqrt(pow((rootNode->xCoord - x), 2) + pow((rootNode->yCoord- y), 2));	//distance between the node and the (x,y)
		if(distance <= rad)		//city is within radius
		{
			cities_in_radius.push_back(rootNode->name);
		}
		if( distance < rad)
		{
			citiesInside(rootNode->se, x, y, rad, visited_cities, cities_in_radius);
			citiesInside(rootNode->sw, x, y, rad, visited_cities, cities_in_radius);
			citiesInside(rootNode->ne, x, y, rad, visited_cities, cities_in_radius);
			citiesInside(rootNode->nw, x, y, rad, visited_cities, cities_in_radius);		
		}
		else
		{
			if((rootNode->xCoord > (x -rad)) && (rootNode->xCoord < x) && (rootNode->yCoord > y) && (rootNode->yCoord <= (y + rad)))
			{
				citiesInside(rootNode->se, x, y, rad, visited_cities, cities_in_radius);
				citiesInside(rootNode->sw, x, y, rad, visited_cities, cities_in_radius);
				citiesInside(rootNode->ne, x, y, rad, visited_cities, cities_in_radius);
			}
			else if((rootNode-> xCoord > x) && (rootNode->xCoord <= (x + rad)) && (rootNode->yCoord > y) && (rootNode->yCoord <= (y + rad)))
			{
				citiesInside(rootNode->se, x, y, rad, visited_cities, cities_in_radius);
				citiesInside(rootNode->sw, x, y, rad, visited_cities, cities_in_radius);
				citiesInside(rootNode->nw, x, y, rad, visited_cities, cities_in_radius);
			}
			else if((rootNode->xCoord > (x - rad)) && (rootNode->xCoord < x) && (rootNode->yCoord < y) && (rootNode->yCoord > (y - rad)))
			{
				citiesInside(rootNode->se, x, y, rad, visited_cities, cities_in_radius);
				citiesInside(rootNode->ne, x, y, rad, visited_cities, cities_in_radius);
				citiesInside(rootNode->nw, x, y, rad, visited_cities, cities_in_radius);
			}
			else if((rootNode->xCoord > x) && (rootNode->xCoord <= (x + rad)) && (rootNode->yCoord < y) && (rootNode->yCoord > (y - rad)))
			{
				citiesInside(rootNode->sw, x, y, rad, visited_cities, cities_in_radius);
				citiesInside(rootNode->ne, x, y, rad, visited_cities, cities_in_radius);
				citiesInside(rootNode->nw, x, y, rad, visited_cities, cities_in_radius);
			}
			else if((rootNode->xCoord <= (x - rad)) && (rootNode->yCoord > (y + rad)))
			{
				citiesInside(rootNode->se, x, y, rad, visited_cities, cities_in_radius);
			}
			else if(((rootNode->xCoord == x) && (rootNode->yCoord == y + rad)) || ((rootNode->xCoord <= (x + rad)) && (rootNode->xCoord > (x - rad)) && (rootNode->yCoord > (y + rad))))
			{
				citiesInside(rootNode->se, x, y, rad, visited_cities, cities_in_radius);
				citiesInside(rootNode->sw, x, y, rad, visited_cities, cities_in_radius);
			}
			else if((rootNode->xCoord > (x + rad)) && (rootNode->yCoord > (y + rad)))
			{
				citiesInside(rootNode->sw, x, y, rad, visited_cities, cities_in_radius);
			}
			else if((rootNode->xCoord <= (x - rad)) && (rootNode->yCoord > (y - rad)) && (rootNode->yCoord <= (y + rad)))
			{
				citiesInside(rootNode->se, x, y, rad, visited_cities, cities_in_radius);
				citiesInside(rootNode->ne, x, y, rad, visited_cities, cities_in_radius);
			}
			else if(((rootNode->xCoord == x + rad) && (rootNode->yCoord == y)) || ((rootNode->xCoord > (x + rad)) && (rootNode->yCoord > (y - rad)) && (rootNode->yCoord <= (y + rad))))
			{
				citiesInside(rootNode->sw, x, y, rad, visited_cities, cities_in_radius);
				citiesInside(rootNode->nw, x, y, rad, visited_cities, cities_in_radius);
			}
			else if((rootNode->xCoord <= (x - rad)) && (rootNode->yCoord <= (y - rad)))
			{
				citiesInside(rootNode->ne, x, y, rad, visited_cities, cities_in_radius);
			}
			else if((rootNode->xCoord > (x - rad)) && (rootNode->xCoord <= (x + rad)) && (rootNode->yCoord <= (y - rad)))
			{
				citiesInside(rootNode->ne, x, y, rad, visited_cities, cities_in_radius);
				citiesInside(rootNode->nw, x, y, rad, visited_cities, cities_in_radius);
			}
			else if((rootNode->xCoord > (x + rad)) && (rootNode->yCoord <= (y - rad)))
			{
				citiesInside(rootNode->nw, x, y, rad, visited_cities, cities_in_radius);
			}
		}
	}
}