#include <iostream> 
#include "my_heap.h"
#include <string>
using namespace std;

My_heap::My_heap()
{
	heap_begin = nullptr;
	blk = nullptr;
	used_bytes = 0;
}
My_heap::~My_heap()
{
	memory_block * prev = heap_begin;
	while(heap_begin != nullptr)
	{		
		heap_begin = heap_begin->right;
		delete prev;
		prev = heap_begin;
	}
	cout << "At destruction, the heap had a memory leak of " << used_bytes << " bytes" << endl;
}
memory_block*  My_heap::bump_allocate(int num_bytes)
{
	int totalUsedMemory = 0;
	memory_block * ptr = heap_begin;
	while(ptr != nullptr)
	{
		totalUsedMemory += ptr->size;
		ptr = ptr->right;
	}
	if((totalUsedMemory + num_bytes) > MAX_CAPACITY)	//checks capacity
	{
		return nullptr;
	}

	else
	{
		if(heap_begin == nullptr)	//adding to the empty linkedlist
		{
			heap_begin = new memory_block(nullptr, nullptr, true, num_bytes, 0);
			blk = heap_begin;
		}
		else
		{
			int new_adress = blk->starting_address + blk->size; 
			blk->right = new memory_block(blk, nullptr, true, num_bytes, new_adress);
			blk = blk->right;
		}
	}
	used_bytes += num_bytes;
	return blk;
}
memory_block* My_heap::first_fit_allocate(int num_bytes)
{
	memory_block * ptr = heap_begin;
	while(ptr != nullptr)
	{
		if(ptr->used == false && ptr->size >= num_bytes)	//if a fit is found
		{
			used_bytes += ptr->size;		
			ptr->used = true;
			return ptr;
		}
		ptr = ptr->right;
	}

	return bump_allocate(num_bytes);		//if a fit is not found, allocate to the end
}
memory_block*  My_heap::best_fit_allocate(int num_bytes)
{
	memory_block * ptr = heap_begin;
	int bestFitSoFar = -1;				//is -1, because it will change in the first iteration of the loop
	memory_block * bestFit = nullptr;	

	while(ptr != nullptr)
	{
		if(ptr->used == false && ptr->size >= num_bytes)
		{
			if( (bestFitSoFar == -1) || ((ptr->size - num_bytes) <= bestFitSoFar))
			{
				bestFitSoFar = ptr->size - num_bytes;
				bestFit = ptr;
			}
		}
		ptr = ptr->right;
	}
	if(bestFit != nullptr)	//a fit is found
	{
		used_bytes += bestFit->size;
		bestFit->used = true;
		return bestFit;
	}
	else	//fit can't be found
	{
		return bump_allocate(num_bytes);	//allocate to the end
	}

}
memory_block* My_heap::first_fit_split_allocate(int num_bytes)
{
	memory_block * first_fit_split = first_fit_allocate(num_bytes);

	if(first_fit_split == nullptr)		//if exceeds capacity
	{
		return nullptr;
	}
	else if(first_fit_split->size == num_bytes)		//split is not needed, memory block has exactly num_bytes bytes
	{
		return first_fit_split;
	}
	else	//split is needed
	{
		memory_block * next = first_fit_split->right;
		first_fit_split->right = new memory_block(first_fit_split, next, false, first_fit_split->size - num_bytes, first_fit_split->starting_address + num_bytes);
		first_fit_split->size = num_bytes;

		if(next == nullptr)		//adding to the end
		{
			blk = first_fit_split->right;
		}
		else
		{
			next->left = first_fit_split->right;
		}

		used_bytes -= first_fit_split->right->size;		//splitted and not used memory is substracted from used_bytes
		return first_fit_split;
	}

}
void My_heap::deallocate(memory_block* block_address)
{
	if(block_address != nullptr)
	{
		if(block_address->used == true)
		{
			used_bytes -= block_address->size;	//deallocated memory was used
		}
		block_address->used = false;
		memory_block * node_next_to;

		if((block_address->right != nullptr) && (block_address->right->used == false))	//node on the right is not used
		{
			node_next_to = block_address->right;
			node_next_to->size += block_address->size; 
			node_next_to->starting_address = block_address->starting_address;
			node_next_to->left = block_address->left;
			if(block_address->left != nullptr)
			{
				block_address->left->right = node_next_to;
			}
			else	//deletion on the most left
			{
				heap_begin = node_next_to;
			}
			delete block_address;
		}
		if((block_address->left != nullptr) && (block_address->left->used == false))	//node on the left is not used
		{
			node_next_to = block_address->left;
			node_next_to->size += block_address->size;
			node_next_to->right = block_address->right;
			if(block_address->right != nullptr)
			{
				block_address->right->left = node_next_to;
			}
			else	//deletion on the most right
			{
				blk = node_next_to;
			}
			delete block_address;
		}
	}
}
void My_heap::print_heap()
{
	memory_block * ptr = heap_begin;
	int num_of_memory_blocks = 0;
	int num_of_used = 0;	
	int num_of_free = 0;
	while(ptr != nullptr)
	{
		if(ptr->used == true)
		{
			num_of_used += 1;
		}
		else
		{
			num_of_free += 1;
		}
		num_of_memory_blocks += 1;
		ptr = ptr->right;
	}

	cout << "Maximum capacity of heap: " << MAX_CAPACITY << "B" << endl;
	cout << "Currently used memory (B): " << used_bytes << endl;
	cout << "Total memory blocks: " << num_of_memory_blocks << endl;
	cout << "Total used memory blocks: " << num_of_used << endl;
	cout << "Total free memory blocks: " << num_of_free << endl;
	cout << "Fragmentation: " << get_fragmantation() << "%" << endl;
	cout << "------------------------------" << endl;

	ptr = heap_begin;
	int index = 0;
	while(ptr != nullptr)
	{
		string isUsed = ptr->used?"True":"False";	//to print out true or false instead of 1 or 0
		cout << "Block " << index << "\t\tUsed: " << isUsed << "\tSize (B): " << ptr->size << "\tStarting Address: 0x" << hex << ptr->starting_address << dec << "\n";
		index += 1;
		ptr = ptr->right;
	}

	cout << "------------------------------" << endl;
	cout << "------------------------------" << endl;
}

float My_heap::get_fragmantation()
{
	memory_block * get_sizes = heap_begin;
	int biggest_free_block = 0;
	int used_or_free_memory = 0;
	int free_memory = MAX_CAPACITY - used_bytes;

	while (get_sizes != nullptr)
	{
		used_or_free_memory += get_sizes->size;
		if(get_sizes->used == false)
		{
			if(get_sizes->size > biggest_free_block)
			{
				biggest_free_block = get_sizes->size;
			}
		}
		get_sizes = get_sizes->right;
	}
	if(biggest_free_block < (MAX_CAPACITY - used_or_free_memory))	
	{
		biggest_free_block = MAX_CAPACITY - used_or_free_memory;	
	}

	float fragmentation = (float(free_memory - biggest_free_block)/free_memory) *100;
	return fragmentation;
}
