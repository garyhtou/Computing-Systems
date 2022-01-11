// Gary Tou
// January 10, 2022
// CPSC 3500, Project 1
// wcat.cpp

#include <iostream>
#include <fstream>
using namespace std;

void failureExit()
{
	cout << "wcat: cannot open file" << endl;
	exit(1);
}

void printFile(char *filePath)
{
	try
	{
		// Create a file stream with the provided file path
		ifstream file(filePath);

		// Check if the file stream is open
		if (file.is_open())
		{
			// print out the stream buffer
			cout << file.rdbuf();
		}
		else
		{
			// Since the file stream failed to open, print an error message
			failureExit();
		}
	}
	catch (const ifstream::failure &e)
	{
		failureExit();
	}
}

int main(int arg, char *argv[])
{
	try
	{
		// Guard clause for when no command-line arguments are passed in
		if (arg <= 1)
		{
			cout << "wcat: file [file ...]" << endl;
			return 1;
		}

		// Iterate through the command-line arguments (file paths).
		// The first command-line arguments starts at index 1 since argv[0] is the
		// name of the program (wcat).
		for (int i = 1; i < arg; i++)
		{
			// Print the file.
			printFile(argv[i]);
		}

		return 0;
	}
	catch (...)
	{
		cout << "wcat: invalid input" << endl;
		return 1;
	}
}
