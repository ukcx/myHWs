#include <iostream>
#include <semaphore.h>
using namespace std;


#ifndef HEAPMANAGER
#define HEAPMANAGER

struct memo_chunk
{
	int id;
	int size;
	int index;
	memo_chunk * next;

	memo_chunk(int i, int s, int idx)
	{
		id = i;
		size = s;
		index = idx;
	}
};

class HeapManager
{
public:
	int initHeap( int );
	int myMalloc(int, int);
	int myFree(int, int);
	void print();
	~HeapManager();
	HeapManager();

private:
	memo_chunk * head;
	sem_t mutex;
	sem_t print_mtx;
};

#endif


HeapManager::HeapManager()
{
	head = nullptr;
	sem_init(&mutex, 0, 1);
	sem_init(&print_mtx, 0, 1);
}

HeapManager::~HeapManager()
{
	memo_chunk * temp = head;

	while(head != nullptr)
	{
		temp = head->next;
		delete head;
		head = temp;
	}
	
	sem_destroy(&mutex);
	sem_destroy(&print_mtx);
}

int HeapManager::initHeap(int size)
{
	head = new memo_chunk(-1, size, 0);
	head->next = nullptr;

	print();
	return 1;
}

int HeapManager::myMalloc(int id, int size)
{
	sem_wait(&mutex);
	bool isSpaceFound = false;
	memo_chunk * iterator = head;
	while( (iterator != nullptr)  &&  !(isSpaceFound))
	{
		if( (iterator->id == -1) && (iterator->size >= size))
		{
			isSpaceFound = true;
			if( iterator->size - size > 0 )
			{
				memo_chunk * next = iterator->next;
				memo_chunk * free_chunk_left = new memo_chunk(-1, iterator->size - size, iterator->index + size);
				iterator->id = id;
				iterator->size = size;
				iterator->next = free_chunk_left;
				free_chunk_left->next = next;
			}
			else
			{
				iterator->id = id;
				iterator->size = size;
			}

		}

		if(!isSpaceFound)
			iterator = iterator->next;
	}
	
	
	if(isSpaceFound)
	{
		cout << "Allocated for thread " << id << endl;
		print();
		sem_post(&mutex);
		return iterator->index;
	}
	else
	{
		cout << "Can not allocate, requested size " << size << " for thread " << id << " is bigger than remaining size" << endl;
		print();
		sem_post(&mutex);
		return -1;
	}
}

int HeapManager::myFree(int id, int index)
{
	sem_wait(&mutex);
	bool doesNodeExists = false;
	memo_chunk * iterator = head;
	memo_chunk * previous = nullptr;

	while( (iterator != nullptr) && !(doesNodeExists) )
	{
		memo_chunk * next = iterator->next;

		if( (iterator->id == id) && (iterator->index == index) )
		{
			doesNodeExists = true;

			if( previous == nullptr )
			{
				if( next == nullptr )
				{
					iterator->id = -1;
				}
				else
				{
					if(next->id == -1)
					{
						//coalesce with right
						memo_chunk * new_next = next->next;
						iterator->id = -1;
						iterator->size = iterator->size + next->size;
						delete next;
						iterator->next = new_next;	
					}
					else
					{
						iterator->id = -1;
					}
				}
			}
			else
			{
				if( next == nullptr )
				{
					if(previous->id == -1)
					{
						//coalesce with left
						previous->size = previous->size + iterator->size;
						previous->next = next;
						delete iterator;

					}
					else
					{
						iterator->id = -1;
					}
				}
				else
				{
					if( (previous->id == -1) && (next->id == -1) )
					{
						//coalesce with both sides
						memo_chunk * new_next = next->next;
						previous->size = previous->size + iterator->size + next->size;
						previous->next = new_next;
						delete iterator;
						delete next;
					}
					else if( (previous->id == -1) )
					{
						//coalesce with left
						previous->size = previous->size + iterator->size;
						previous->next = next;
						delete iterator;

					}
					else if( (next->id == -1) )
					{
						//coalesce with right
						memo_chunk * new_next = next->next;
						iterator->id = -1;
						iterator->size = iterator->size + next->size;
						delete next;
						iterator->next = new_next;	
					}
					else
					{
						iterator->id = -1;
					}
				}
			}
		}

		if(!doesNodeExists)
		{
			previous = iterator;
			iterator = iterator->next;
		}
	}

	
	if(doesNodeExists)
	{
		cout << "Freed for thread " << id << endl;
		print();
		sem_post(&mutex);
		return 1;
	}
	else 
	{
		cout << "Can not free the requested memory, the memory with index " << index << " for thread " << id << " does not exist." << endl;
		print();
		sem_post(&mutex);
		return -1;
	}
	
}

void HeapManager::print()
{
	sem_wait(&print_mtx);
	memo_chunk * iterator = head;
	int count = 0;

	while( iterator != nullptr)
	{
		if(count != 0)
			cout << "---";
		cout << "[" << iterator->id << "][" << iterator->size << "][" << iterator->index << "]";
		iterator = iterator->next;
		count++;
	}
	cout << "\n";
	
	sem_post(&print_mtx);

}

