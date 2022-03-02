#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

sem_t mutex;
sem_t barrier_a;
sem_t barrier_b;
sem_t car;
int count_a = 0;
int count_b = 0;
int finishedThreads = 0;
int isCarFull = 0;

void *fan_transport (void * data)
{
	char * info = data;
	
	sem_wait(&car);
	
	printf("Thread ID: %lu, Team: %s, I am looking for a car\n", pthread_self(), info);
	
	if(info == "A")
		count_a++;
	else if(info == "B")
		count_b++;
		
	if(count_b == 4)
	{
		isCarFull = 1;
		count_b = 0;
		sem_post(&barrier_b);
		sem_post(&barrier_b);
		sem_post(&barrier_b);
	}
	else if(count_a == 4)
	{
		isCarFull = 1;
		count_a = 0;
		sem_post(&barrier_a);
		sem_post(&barrier_a);
		sem_post(&barrier_a);
	}
	else if(count_a == 2 && count_b == 2)
	{
		isCarFull = 1;
		count_a = 0;
		count_b = 0;
		if(info == "A")
			sem_post(&barrier_b);
		else
			sem_post(&barrier_a);			
		sem_post(&barrier_a);
		sem_post(&barrier_b);
	}
	else if(count_a == 2 && count_b > 2)
	{
		isCarFull = 1;
		count_b -= 2;
		count_a = 0;
		sem_post(&barrier_a);
		sem_post(&barrier_b);
		sem_post(&barrier_b);
	}
	else if(count_a > 2 && count_b == 2)
	{
		isCarFull = 1;
		count_a -= 2;
		count_b = 0;
		sem_post(&barrier_a);
		sem_post(&barrier_a);
		sem_post(&barrier_b);
	}
	else
	{
		if(info == "A")
		{
			sem_post(&car);
			sem_wait(&barrier_a);
		}
		else if(info == "B")
		{
			sem_post(&car);
			sem_wait(&barrier_b);
		}
	}
	
	sem_wait(&mutex);
	
	printf("Thread ID: %lu, Team: %s, I have found a spot in a car\n", pthread_self(), info);
	finishedThreads++;
	if(finishedThreads == 4)
	{
		finishedThreads = 0;
		printf("Thread ID: %lu, Team: %s, I am the captain and driving the car\n", pthread_self(), info);
		isCarFull = 0;
		sem_post(&car);
	}
	
	sem_post(&mutex);

}


int main(int argc, char ** args)
{
	int team_a_fans = atoi(args[1]); 
	int team_b_fans = atoi(args[2]);
	
	if( (team_a_fans % 2 == 0) && (team_b_fans % 2 == 0) && ( (team_a_fans + team_b_fans) % 4 == 0) )
	{
		pthread_t team_A[team_a_fans];
		pthread_t team_B[team_b_fans];
		char  * teamAfan = "A";
		char  * teamBfan = "B";
		
		sem_init(&mutex, 0, 1);
		sem_init(&barrier_a, 0, 0);
		sem_init(&barrier_b, 0, 0);
		sem_init(&car, 0, 1);
		
		for(int i = 0; i < team_a_fans; i++)
		{
			pthread_create(&team_A[i], NULL, fan_transport, teamAfan);		
		}
		for(int i = 0; i < team_b_fans; i++)
		{
			pthread_create(&team_B[i], NULL, fan_transport, teamBfan);	
		}
		
		for(int i = 0; i < team_a_fans; i++)
		{
			pthread_join(team_A[i], NULL);	
		}
		for(int i = 0; i < team_b_fans; i++)
		{
			pthread_join(team_B[i], NULL);
		}
			
		sem_destroy(&mutex);
		sem_destroy(&car);
		sem_destroy(&barrier_a);
		sem_destroy(&barrier_b);
	}
	
	printf("The main terminates\n");
	return 0;
}
