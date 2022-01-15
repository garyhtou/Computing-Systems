// Gary Tou
// January 10, 2022
// CPSC 3500, Project 1
// wunzip.cpp

#include <iostream>
#include <fstream>
#include <bitset>
using namespace std;

void printDecodedRun(char character, uint32_t count)
{
	for (int i = 0; i < count; i++)
	{
		cout.write(&character, 1);
	}
}

void unzipFile(ifstream &file)
{

	uint32_t counter;
	char counterBlock[4];
	char character[1];

	// Loop through all 5-byte blocks in the file
	//   counter: 4-byte block
	//   character: 1-byte block
	while (file.read(counterBlock, 4) && file.read(character, 1))
	{
		// Cast the counter from a char array to a uint32_t
		// counter = reinterpret_cast<uint32_t>(counterBlock);
		counter = *(int *)&counterBlock;

		// Print the decoded run
		printDecodedRun(*character, counter);
	}
}

int main(int arg, char *argv[])
{
	try
	{
		// Guard clause for when no command-line arguments are passed in.
		if (arg <= 1)
		{
			cout << "wunzip: file1 [file2 ...]" << endl;
			return 1;
		}

		// Iterate through the command-line arguments (file paths).
		// The first file path argument starts at index 1 since argv[0] is the name of
		// the program (wunzip)
		for (int i = 1; i < arg; i++)
		{
			// Get the file path
			char *filePath = argv[i];

			// Create a file stream
			ifstream file(filePath);

			// Guard clause for when the file stream fails to open
			if (!file)
			{
				// Since the file stream failed to open, attempt to close the file and
				// print an error message
				file.close();
				cout << "wunzip: cannot open file" << endl;
				return 1;
			}

			// Unzip the file and print the decoded file to the standard output
			unzipFile(file);

			// Close the file
			file.close();
		}

		// We've unzipped all the files!
		return 0;
	}
	catch (const ifstream::failure &e)
	{
		cout << "wunzip: cannot open file" << endl;
		return 1;
	}
	catch (...)
	{
		cout << "wunzip: invalid input" << endl;
		return 1;
	}
}
