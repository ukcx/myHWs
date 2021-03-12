#ifndef MODIFIED_HEAP_H 
#define MODIFIED_HEAP_H
#include <vector>
#include <string>
#include <unordered_map>
using namespace std;

struct counterInOneRow		//struct to keep track of number of columns that are full for given row and block
{
	int id;					//the id is used to keep the order of block names and row names as they were given as input
							//i.e. id = 0 for the first block which was given as input when using constructor of ModifiedHeap
	int count;				//the number of columns that are full for given row and block
	counterInOneRow::counterInOneRow(int label, int value)
	{
		id = label;
		count = value;
	}
};

class ModifiedHeap
{
public:
	ModifiedHeap(vector<string>, vector<string>);			//constructor
	~ModifiedHeap();										//destructor
	void removeSeat(string, string);						//remove a seat from given block and row
	bool insert_and_return_block(string&, string, int);		//insert a seat to the given row, and return the name of the row as reference parameter
	void insert_to(string, string);							//insert a seat to the given row and block

private:
	vector<vector<counterInOneRow>> heap;									//heap to keep counts of full columns for every block and row
	vector<string> block_names;												//names of the blocks
	unordered_map<string, unordered_map<string, int>> block_positions;		//positions of blocks in heap
	unordered_map<string, int> row_positions;								//positions of rows in heap
};

#endif