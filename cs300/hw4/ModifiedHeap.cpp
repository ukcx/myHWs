#include "ModifiedHeap.h"
using namespace std;


/*constructor*/
ModifiedHeap::ModifiedHeap(vector<string> blocks, vector<string> rows)
{
	for(int i = 0; i < rows.size(); i++)
	{
		row_positions[rows[i]] = i;					//the positions of rows in heap. to reach index of the rows; when only the name of the row is known
		vector<counterInOneRow> blocksInOneRow;		//all the blocks; blocks will be stored as a min heap, the heap is based on count values of counterInOneRow struct 
		counterInOneRow dummyElem(-1,-1);			//dummy element to occupy 0th index
		blocksInOneRow.push_back(dummyElem);
		for(int j = 0; j < blocks.size(); j++)
		{
			counterInOneRow temp(j, 0);
			blocksInOneRow.push_back(temp);
			block_positions[blocks[j]][rows[i]] = j + 1;
		}
		heap.push_back(blocksInOneRow);				//all the blocks for a row
	}
	block_names = blocks;		//names of the blocks are stored to reach the name of a block, when only the position of the block in the heap is known
}


/*destructor*/
ModifiedHeap::~ModifiedHeap()
{
	block_positions.erase(block_positions.begin(), block_positions.end());		//erase each element from unordered_maps
	row_positions.erase(row_positions.begin(), row_positions.end());	
}


/*remove one seat from given block and row*/
void ModifiedHeap::removeSeat(string block, string row)			
{
	int current_value = --heap[row_positions[row]][block_positions[block][row]].count;	//number of full seats in a given block and row is decreased by 1
	int hole = block_positions[block][row];
	int parent_index;
	counterInOneRow temp = heap[row_positions[row]][hole];

	for( ; hole > 1 && (current_value < heap[row_positions[row]][ hole / 2 ].count 
		|| ((current_value == heap[row_positions[row]][ hole / 2 ].count) && (heap[row_positions[row]][hole].id < heap[row_positions[row]][ hole / 2 ].id))); hole = parent_index )	
										//perculation is needed when for each time the count of the hole is greater than the count of the parent index
										//or when the counts are equal for hole and parent index; but id of parent index is greater
	{
		parent_index = hole / 2;			
		block_positions[block_names[heap[row_positions[row]][ parent_index ].id]][row] = hole;		//the location of the block in heap is updated
		heap[row_positions[row]][ hole ] = heap[row_positions[row]][ parent_index ];				//perculate down
	}

	heap[row_positions[row]][hole] = temp;
	block_positions[block_names[heap[row_positions[row]][ hole ].id]][row] = hole;		//the location of the block in heap is updated
}



/*insert a seat to the given row, and return the name of the row as reference parameter*/
bool ModifiedHeap::insert_and_return_block(string& availableBlock, string row, int max_columns)
{
	if(heap[row_positions[row]][1].count >= max_columns)	//all the columns for that row is full
		return false;
	else
	{
		availableBlock = block_names[heap[row_positions[row]][1].id];	//first block in heap is the most empty one
		insert_to(availableBlock, row);									//insert the seat into the block that found
		return true;
	}
}


/*insert a seat to the given row and block*/
void ModifiedHeap::insert_to(string block, string row)		
{
	int current_value = ++heap[row_positions[row]][block_positions[block][row]].count;	//number of full seats in a given block and row is increased by 1
	int hole = block_positions[block][row];
	counterInOneRow temp = heap[row_positions[row]][hole];
	int child_index;
	int size = heap[0].size() - 1;

	for( ; hole * 2 <= size; hole = child_index)		//perculation is needed when for each time the count of the hole is less than the count of the child index
														//or when the counts are equal for hole and child index; but id of child index is lesser
	{																		
		child_index = hole * 2;
		if( child_index < size && ((heap[row_positions[row]][ child_index + 1 ].count < heap[row_positions[row]][ child_index ].count) 
			||((heap[row_positions[row]][ child_index + 1 ].count == heap[row_positions[row]][ child_index ].count) && (heap[row_positions[row]][ child_index + 1 ].id < heap[row_positions[row]][ child_index ].id))))
            child_index++;
		if( (heap[row_positions[row]][ child_index ].count < current_value)
			|| ((current_value == heap[row_positions[row]][ child_index ].count) && (heap[row_positions[row]][ child_index ].id < heap[row_positions[row]][hole].id)))
		{
			block_positions[block_names[heap[row_positions[row]][ child_index ].id]][row] = hole;		//the location of the block in heap is updated
			heap[row_positions[row]][ hole ] = heap[row_positions[row]][ child_index ];					//perculate up
		}
        else
            break;				//no more perculation is needed
	}

	heap[row_positions[row]][hole] = temp;
	block_positions[block_names[heap[row_positions[row]][ hole ].id]][row] = hole;						//the location of the block in heap is updated
}