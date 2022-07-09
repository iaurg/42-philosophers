#include <pthread.h>
#include <unistd.h>
#include <stdio.h>

void *myturn(void *arg)
{
	int count = 10;

	for (int i = 0; i < count; i++)
	{
		sleep(2);
		printf("I'm thinking, %d\n", i);
	}
	return (NULL);
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
	pthread_t newthread;
	pthread_create(&newthread, NULL, myturn, NULL);
	yourturn();
	pthread_join(newthread, NULL);
}
