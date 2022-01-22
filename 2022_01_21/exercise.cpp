#include "pthread.h"
#include "iostream"

void *thread_print(void *arg)
{
	int *num = (int *)(arg);
	for (int i = 0; i < 5; i++)
	{
		printf("Hello World! (thread %d)\n", *num);
	}
	return NULL;
}

int main(int argc, char *argv[])
{
	int numThreads = 10;
	pthread_t tids[numThreads];
	int nums[numThreads];

	for (int i = 0; i < numThreads; i++)
	{
		nums[i] = i;
		if (pthread_create(&tids[i], NULL, thread_print, (void *)&nums[i]))
		{
			std::cout << "Error creating thread" << std::endl;
			return 1;
		}
	}

	for (int i = 0; i < numThreads; i++)
	{
		pthread_join(tids[i], NULL);
	}
	return 0;
}
