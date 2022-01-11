// Gary Tou
// January 10, 2022
// CPSC 3500, Project 1
// wzip.cpp

#include <iostream>
#include <fstream>
using namespace std;

string encodeRun(char character, uint32_t count)
{
	// Convert the count to a 4-byte (32 bit) binary number; stored in a string
	string encoding = bitset<32>(count).to_string();
	encoding += character;

	// Return the compressed run
	return encoding;
}

void failureExit()
{
	cout << "wzip: cannot open file" << endl;
	exit(1);
}

void zipFile(ifstream &file)
{
	try
	{
		// Guard clause for when the file stream fails to open
		if (!file.is_open())
		{
			// Since the file stream failed to open, print an error message
			failureExit();
		}
		// Counter is a 32 bit integer because the compression format (Run Length
		// Encoding) is limited to a 4-byte integer for the count.
		uint32_t counter = 0; // The number of consecutive `currChar` repetitions
		char currChar = -1;		// The current character being compressed
		char loopChar;				// The current character in the loop

		// Loop through all lines in the file
		while (file.get(loopChar))
		{
			if (loopChar != currChar && currChar != -1)
			{
				// A new character was found. Encode (compress) and print the current
				// character run
				cout << encodeRun(currChar, counter); // no `endl`

				// Reset and move onto the new character run
				counter = 0;
				currChar = loopChar;
			}
			else if (currChar == -1)
			{
				// `currChar` hasn't been initialized. (It is the first char in the file.)
				currChar = loopChar;
			}

			// Increment the counter
			counter++;
		}

		// Process the last character run
		cout << encodeRun(currChar, counter); // no `endl`
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
		// Guard clause for when no command-line arguments are passed in.
		if (arg <= 1)
		{
			cout << "wzip: file1 [file2 ...]" << endl;
			return 1;
		}

		// Iterate through the command-line arguments (file paths).
		// The first file path argument starts at index 1 since argv[0] is the name of
		// the program (wzip)
		for (int i = 1; i < arg; i++)
		{
			// Get the file path
			char *filePath = argv[i];

			// Create a file stream
			ifstream file(filePath);

			// Zip the file.
			// `zipFile` will check if the file stream is open
			zipFile(file);
		}

		// We've zipped all the files!
		return 0;
	}
	catch (...)
	{
		cout << "wzip: invalid input" << endl;
		return 1;
	}
}
