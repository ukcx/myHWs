#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

typedef struct __thread_info {
	char mark;
}thread_info;
	
typedef struct __lock_t{
	int turn;
	char marks[2];
}lock_t;

void lock_init(lock_t * lock){
	lock->turn = 0;
	lock->marks[0] = 'x';
	lock->marks[1] = 'o';
}	

void lock(lock_t * lock, thread_info * info){
	while (lock->marks[lock->turn] != info->mark)
		;
}	

void unlock(lock_t * lock){
	int prev_turn = lock->turn;
	lock->turn = 1 - prev_turn;
}

pthread_t threads[2];
int empty_cells;
int size;
int isGameFinished = 0;
char winner = '-';
char** board;
lock_t thread_lock;
	
void *fill_the_board(void * data)
{
	while( isGameFinished == 0 )
	{
		thread_info * thread_data = data;
		lock(&thread_lock, thread_data);
		if(isGameFinished == 0)
		{
			int rand_row = rand() % size;
			int rand_clmn = rand() % size;
			while(board[rand_row][rand_clmn] != '-')
			{	
				rand_row = rand() % (size - 0) + 0;
				rand_clmn = rand() % (size - 0) + 0;
			}
			board[rand_row][rand_clmn] = thread_data->mark;
			empty_cells--;
			printf("Player %c played on: (%d,%d)\n", thread_data->mark, rand_row, rand_clmn);

			int isWon = 1;
			for(int k = 0; k < size; k++){
				if( board[rand_row][k] != thread_data->mark)
				{
					isWon = 0;
					break;
				}
			}
			if(isWon == 0)
			{
				isWon = 1;
				for(int k = 0; k < size; k++){
					if( board[k][rand_clmn] != thread_data->mark)
					{
						isWon = 0;
						break;
					}
				}		
			}
			if( (rand_row == rand_clmn) && (isWon == 0) )
			{	
				isWon = 1;
				for(int k = 0; k < size; k++)
				{
					if( board[k][k] != thread_data->mark)
					{
						isWon = 0;
						break;
					}
				}		
			}
			if( (rand_row + rand_clmn == size - 1) && (isWon == 0) )
			{	
				isWon = 1;
				for(int k = 0; k < size; k++){
					if( board[k][size-1-k] != thread_data->mark)
					{
						isWon = 0;
						break;
					}
				}		
			}
			if( isWon == 1)
			{
				isGameFinished = 1;
				winner = thread_data->mark;
			}
			else if( empty_cells == 0 ){
				isGameFinished = 1;
			}
		}
		unlock(&thread_lock);
	}
}

int main()
{
	srand(time(NULL));
	char str_size[3];
	printf("Board Size: ");
	fgets(str_size, 3, stdin);
	const char * char_size = &str_size[0];
	char x_mark = 'x';
	char o_mark = 'o';
	thread_info * info1 = malloc(sizeof(thread_info));
	info1->mark = x_mark;
	thread_info * info2 = malloc(sizeof(thread_info));
	info2->mark = o_mark;
	
	size = atoi(char_size);
	empty_cells = size * size;
	
	board = (char**)malloc(size * sizeof(char *));
	for (int i = 0; i < size; i++)
	{
		board[i] = (char*)malloc(size * sizeof(char));
	}
	for (int i = 0; i < size; i++)
	{	
		for (int j = 0; j < size; j++)
		{
			board[i][j] = '-';
		}
	}
	
	lock_init(&thread_lock);
	
	int rv_1 = pthread_create(&threads[0], NULL, fill_the_board, info1);
	int rv_2 = pthread_create(&threads[1], NULL, fill_the_board, info2);

	if(rv_1 == 0 && rv_2 == 0)
	{
		pthread_join(threads[0], NULL);
		pthread_join(threads[1], NULL);
		
		printf("Game end\n");
		if(winner != '-')
		{
			printf("Winner is %c\n", winner);
		}
		else 
			printf("It is a tie\n");
		
		for (int i = 0; i < size; i++)
		{	
			for (int j = 0; j < size; j++)
			{
				if(board[i][j] == '-')
					printf("[ ]");
				else
					printf("[%c]" , board[i][j]);
			}
			printf("\n");
		}
		
		free(info1);
		free(info2);
		for (int i = 0; i < size; i++)
		{	
			free(board[i]);
		}
		free(board);
	}
	else
	{
		printf("Error on creating children threads!");
	}
	return 0;
}	

