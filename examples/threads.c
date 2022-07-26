#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

void *myturn(void *arg)
{
	int count = 10;

	// Allocate memory for the thread return this needs to be a pointer
	int *iptr = (int *)malloc(sizeof(int));
	*iptr = 20;

	for (int i = 0; i < count; i++)
	{
		sleep(2);
		printf("I'm thinking, %d, iptr = %d\n", i, *iptr);
		(*iptr)++;
	}
	return (iptr);
}

void yourturn()
{
	int count = 5;

	for (int i = 0; i < count; i++)
	{
		sleep(2);
		printf("Philosopher is thinking, %d\n", i);
	}
}

/*
gcc -pthread -o threads threads.c <- command to enable pthread_create
*/
int main()
{
	// Start threads
	pthread_t newthread;

	// Holder for return value of pthread_create()
	// This can point to any data type, like an int, a pointer, a struct, etc.
	int *result;

	pthread_create(&newthread, NULL, myturn, NULL);
	yourturn();

	// wait until the thread is done before exit
	pthread_join(newthread,(void *)&result);

	// result is a pointer to the return value of pthread_create()
	printf("iptr = %d\n", *result);
	printf("Thread is done\n");
}
