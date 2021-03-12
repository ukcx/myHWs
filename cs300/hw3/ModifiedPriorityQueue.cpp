#include "ModifiedPriorityQueue.h"
using namespace std;

//constructor for ModifiedPriorityQueue
//takes number of elements as input to create the arrays
ModifiedPriorityQueue::ModifiedPriorityQueue(int size)
{
	heap = new sky_line[size + 1];	//heap to store the elements, 0th index will stay unmodified during any function
	locations = new int[size];		//stores the positions of elements that are currently stored in heap, i.e. locations[5] = 2 then heap[2].label = 5
	current_size = 0;				//currently no element inserted to the heap
}

//destructor
ModifiedPriorityQueue::~ModifiedPriorityQueue()
{
	delete [] locations;	//deletes the dynamically created arrays to prevent memory leakage
	delete [] heap;
}

//inserts an element(sky_line object) to the heap
void ModifiedPriorityQueue::insert(sky_line building, int id)
{
	int hole = ++current_size;	//hole strores the position where building should be inserted

	for( ; hole > 1 && building.height > heap[ hole / 2 ].height; hole /= 2 )	//maximum height values should be stored in forward indices of heap
	{																		//since the heap is a max heap to getmax easier
		sky_line temp = heap[hole];			
        heap[ hole ] = heap[ hole / 2 ];	//perculate down	
		locations[heap[hole].label] = hole;	//location is changed for the the value that changed position
		heap[hole/2] = temp;
	}
    heap[ hole ] = building;				//the input sky_line object inserted in the position found by perculating down
	locations[heap[hole].label] = hole;		
}

//remove an element from the heap with given label
sky_line ModifiedPriorityQueue::remove(int label)
{
	sky_line  temp = heap[current_size];
	heap[current_size] = heap[locations[label]];
	heap[locations[label]] = temp;				//the element that needs to be removed
	int hole = locations[label];
	int child;
	current_size--;								//current size that is being used is decremented by 1
    for( ; hole * 2 <= current_size; hole = child )	//perculate up
    {   
        child = hole * 2;							//heap is implemented as binary heap, child elements are in position of hole*2 and hole*2+1
		if( child != current_size && heap[ child + 1 ].height > heap[ child ].height )	//second child has greater height value
            child++;
		if( heap[ child ].height > temp.height )	//perculation up is needed
		{
			heap[ hole ] = heap[ child ];
			locations[heap[ hole ].label] = child;
		}
        else
            break;
    }
    heap[ hole ] = temp;
	locations[label] = -1;						//heap[locations[label]] isn't being used, -1 means that the element with label is removed
	return heap[current_size + 1];		//return the element that is removed
}

//get the maximum height in the heap
int ModifiedPriorityQueue::GetMax()
{
	if(IsEmpty())	//if the heap is empty height is 0
		return 0;
	return heap[1].height;
}

//return if the heap is empty or not
bool ModifiedPriorityQueue::IsEmpty()
{
	return(current_size == 0);
}