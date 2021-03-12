#ifndef MY_HEAP_H
#define MY_HEAP_H

#define MAX_CAPACITY 512 // the size capacity of Img_heap

struct memory_block{

	memory_block::memory_block(memory_block* lft, memory_block* rght, bool isUsed, int numOfbytes, int st_address)	//constructor with parameters
		{left = lft; right = rght; used = isUsed, size = numOfbytes, starting_address = st_address;}
	memory_block::memory_block()	//default constructor
	{right = nullptr, left = nullptr, used = true, size = 0, starting_address = 0;}

	memory_block* right; // node to the right
	memory_block* left; // node to the left
	bool used; // if this memory block is reserved or not
	int size; // the number of bytes reserved in Img_heap
	int starting_address; // the starting address in Img_heap
	// of the memory reserved by this block
};


class My_heap{


	private:
		memory_block* heap_begin;	//most left in the doubly link list
		memory_block* blk;		//most right in the doubly link list
		int used_bytes;			//number of bytes in memory blocks that are used
	public:
		My_heap();	//empty linkedlist
		~My_heap();	//destructor, also prints used_bytes
		memory_block* bump_allocate(int num_bytes);		//allocates num_bytes of memory location
		memory_block* first_fit_allocate(int num_bytes);	//checks free memory locations and allocates first eligible one if there is one
		memory_block* best_fit_allocate(int num_bytes);		//checks free memory locations and allocates best eligible one if there is one
		memory_block* first_fit_split_allocate(int num_bytes);	//checks free memory locations and splits memory locations to return a memory location with exactly num_bytes bytes
		void deallocate(memory_block* block_address);	//deallocates given memory location
		void print_heap();		//prints the summary of linked list
		float get_fragmantation();	//calculates fragmentation of available memory
};

#endif