// Write a multithreaded program that calculates the summation of a non-negative
// integer in a separate thread (1+2+3+...+N)
// • The non-negative integer is from command-line parameter

#include "pthread.h"
#include "stdlib.h"
#include "iostream"

void *summation(void *param)
{
	int *n = (int *)param;								 // cast param to int pointer
	int *sum = (int *)malloc(sizeof(int)); // allocate heap memory for return value
	*sum = 0;

	std::cout << "n: " << *n << std::endl;

	for (int i = 1; i <= *n; i++)
	{
		*sum += i;
	}

	std::cout << "sum: " << *sum << std::endl;

	pthread_exit(sum);
}

int main(int argc, char *argv[])
{
	if (argc < 2)
	{
		std::cout << "pass in a number" << std::endl;
		exit(1);
	}

	try
	{
		int n = atoi(argv[1]);

		pthread_t tid;
		if (pthread_create(&tid, NULL, summation, (void *)&n))
		{
			std::cout << "FAILED CREATING THREAD" << std::endl;
			exit(1);
		}

		void *retval;
		pthread_join(tid, (void **)&retval);

		int *sum = (int *)retval;
		std::cout << *sum << std::endl;

		// free return value's heap memory
		free(retval);
		return 0;
	}
	catch (...)
	{
		std::cout << "invalid number" << std::endl;
		exit(1);
	}
}