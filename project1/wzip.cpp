// Gary Tou
// January 10, 2022
// CPSC 3500, Project 1
// wzip.cpp

#include <iostream>
#include <fstream>
#include <bitset>
using namespace std;

void printEncodedRun(char character, uint32_t count)
{
	// Convert the uint32_t counter to a char array for printing
	char counterBlock[4];
	counterBlock[3] = count >> 24;
	counterBlock[2] = count >> 16;
	counterBlock[1] = count >> 8;
	counterBlock[0] = count;

	// Print the counter (4-bytes) and the current char (1-byte) to the
	// standard ouput
	cout.write(counterBlock, 4);
	cout.write(&character, 1);
}

void zipFile(ifstream &file)
{

	// Counter is a 32 bit integer because the compression format (Run Length
	// Encoding) is limited to a 4-byte integer for the count.
	uint32_t counter = 0; // The number of consecutive `currChar` repetitions
	char currChar = -1;		// The current character being compressed
	char loopChar;				// The current character in the loop

	// Loop through all bytes in the file
	while (file.read(&loopChar, 1))
	{
		if (currChar == -1)
		{
			// `currChar` hasn't been initialized. (It is the first char in the
			// file.)
			currChar = loopChar;
		}

		if (loopChar != currChar)
		{
			// A new character was found. Encode (compress) and print the current
			// character run

			// Print current character run
			printEncodedRun(currChar, counter);

			// Reset and move onto the new character run
			counter = 0;
			currChar = loopChar;
		}

		// Increment the counter
		counter++;
	}

	// Process the last character run
	printEncodedRun(currChar, counter);
}

int main(int argc, char *argv[])
{
	try
	{
		// Guard clause for when no command-line arguments are passed in.
		if (argc <= 1)
		{
			cout << "wzip: file1 [file2 ...]" << endl;
			return 1;
		}

		// Iterate through the command-line arguments (file paths).
		// The first file path argument starts at index 1 since argv[0] is the name
		// of the program (wzip).
		for (int i = 1; i < argc; i++)
		{
			// Get the file path
			char *filePath = argv[i];

			// Create a file stream
			ifstream file(filePath);

			// Guard clause for when the file stream fails to open
			if (!file.is_open())
			{
				// Since the file stream failed to open, attempt to close the file and
				// print an error messag
				cout << "wzip: cannot open file" << endl;
				return 1;
			}

			// Zip the file and print the encoded file to the standard output
			zipFile(file);

			// Close the file
			file.close();
		}

		// We've zipped all the files!
		return 0;
	}
	catch (const ifstream::failure &e)
	{
		cout << "wzip: cannot open file" << endl;
		return 1;
	}
	catch (...)
	{
		cout << "wzip: invalid input" << endl;
		return 1;
	}
}
