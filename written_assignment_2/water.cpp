#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>
#include <iostream>

using namespace std;

void *Oxygen(void *arg);
void *Hydrogen(void *arg);

sem_t oxygen, hydrogen; // two Pthread semaphores
int main(int argc, char *argv[])
{
	// fill in your code to initialize two semaphores using sem_init()
	// hint: a counting semphore’s value represents # of resource instances

	// =============== MY CODE STARTS HERE ===============
	sem_init(&hydrogen, 0, 0);
	sem_init(&oxygen, 0, 0);
	// ================ MY CODE ENDS HERE ================

	int num_of_water = atoi(argv[1]); //# of water molecules
	cout << "Number of water molecules: " << num_of_water << endl;

	pthread_t tidox[num_of_water], tidhydro[2 * num_of_water];
	// create hydrogen atom threads
	for (int k = 0; k < num_of_water; k++)
		pthread_create(&tidox[k], NULL, Oxygen, NULL);

	// create hydrogen atom threads
	for (int k = 0; k < 2 * num_of_water; k++)
		pthread_create(&tidhydro[k], NULL, Hydrogen, NULL);

	for (int k = 0; k < 2 * num_of_water; k++)
		pthread_join(tidhydro[k], NULL);
	for (int k = 0; k < num_of_water; k++)
		pthread_join(tidox[k], NULL);

	// fill in your code to destroy semaphores using sem_destroy()

	// =============== MY CODE STARTS HERE ===============
	sem_destroy(&oxygen);
	sem_destroy(&hydrogen);
	// ================ MY CODE ENDS HERE ================

	cout << "Done!" << endl;
	return 0;
}

void *Oxygen(void *arg)
{
	// fill in your synchronization code

	// =============== MY CODE STARTS HERE ===============
	// Wait for two Hydrogens
	sem_wait(&hydrogen);
	sem_wait(&hydrogen);

	// Make one Oxygen available (to both Hydrogen threads)
	sem_post(&oxygen);
	sem_post(&oxygen);

	// We now have everything we need to make water. Exit
	pthread_exit(0);
	// ================ MY CODE ENDS HERE ================
}

void *Hydrogen(void *arg)
{
	// fill in your synchronization code

	// =============== MY CODE STARTS HERE ===============
	// Make one Hydrogen available
	sem_post(&hydrogen);

	// Wait for one Oxygen
	sem_wait(&oxygen);

	// We now have everything needed to make a water. Exit
	pthread_exit(0);
	// ================ MY CODE ENDS HERE ================
}