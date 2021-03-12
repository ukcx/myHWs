#ifndef POINTQUADTREE
#define POINTQUADTREE
#include <string>
#include <vector>
using namespace std;

struct cityNode
{
	cityNode * nw;	//northwest pointer
	cityNode * ne;	//northeast pointer
	cityNode * sw;  //southwest pointer
	cityNode * se;  //southeast pointer
	string name;	//name of the city
	int xCoord;		//x coordinate of the city
	int yCoord;		//y coordinate of the city

	cityNode::cityNode(string city, int x, int y)	//constructor with city name, x coordinate and y coordinate given as parameters
	{
		xCoord = x;
		yCoord = y;
		name = city;
		nw = nullptr;
		ne = nullptr;
		sw = nullptr;
		se = nullptr;
	}
};

class PointQuadTree
{
	public:
		PointQuadTree();			//constructor
		~PointQuadTree();			//destructor
		void pretty_print ();		//print the tree
		void insert(string, int, int);		//insert to the tree
		void citiesInside(int, int, int, vector<string> &, vector<string> &);	//find the cities inside given radius

	private:
		void deleteAll(cityNode *&);	//helps destructor
		void pretty_print (cityNode *);		//helps pretty_print
		void insert(cityNode* &, string, int, int);		//helps insert
		void citiesInside(cityNode* , int, int, int, vector<string> &, vector<string> &);	//helps citiesInside
		cityNode * root;		//root of the point quadtree
		vector<string> duplicates;		//stores the names of the cities which has same coordinates with an already existent point quadtree node
};

#endif