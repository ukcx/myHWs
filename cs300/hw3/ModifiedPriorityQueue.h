#ifndef MODIFIEDPRIORITYQUEUE
#define MODIFIEDPRIORITYQUEUE

struct sky_line			//this struct is the object type that will be stored in heap
{
	int height;			//height of the given building
	int label;			//the position of the building when it is read from the input file
	sky_line::sky_line(){}
	sky_line::sky_line(int y, int id)	//constructer when the height and label values given as input
	{
		height = y;
		label = id;
	}
};

class ModifiedPriorityQueue
{
private:
	int * locations;	//will store the positions of sky_line objects in heap
	sky_line * heap;	//the heap is implemented as pointer to an array
	int current_size;	//current amount of heap that is being used in a given time
public:
	ModifiedPriorityQueue(int);	//constructor with number of buildings given as parameter
	~ModifiedPriorityQueue();	//destructor
	void insert(sky_line, int);	//insert a sky_line object with given label to the heap 
	sky_line remove(int);		//remove one element from the heap with given label as input
	int GetMax();				//return the maximum height value in the heap
	bool IsEmpty();				//returns true if the heap is empty
		
};
#endif 
