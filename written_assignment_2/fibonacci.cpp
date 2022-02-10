#include <pthread.h>
#include <iostream>

using namespace std;

int *output;

void *Generate(void *arg)
{
	int num = *(int *)arg;

	// Prime the output
	output[0] = 0;
	output[1] = 1;

	for (int i = 2; i < num; i++)
	{
		output[i] = output[i - 1] + output[i - 2];
	}

	return (void *)output;
}

int main(int argc, char *argv[])
{
	int num = atoi(argv[1]);

	output = new int[num];

	pthread_t pid;
	pthread_create(&pid, NULL, Generate, (void *)&num);

	pthread_join(pid, (void **)&output);

	for (int i = 0; i < num; i++)
	{
		cout << output[i] << endl;
	}

	delete[] output;
}
