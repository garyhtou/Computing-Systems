// Gary Tou
// January 10, 2022
// CPSC 3500, Project 1
// wunzip.cpp

#include <iostream>
#include <fstream>
using namespace std;

string decodeRun(char character, string countBinStr)
{
	// Convert the string representation of the binary number to a decimal integer
	// The binary string should be 32 bits long
	uint32_t count = bitset<32>(countBinStr).to_ulong();

	// Form the decoded return string
	string decoding = "";
	for (uint32_t i = 0; i < count; i++)
	{
		decoding += character;
	}

	return decoding;
}

void unzipFile(ifstream &file)
{
	// Guard clause for when the file stream fails to open
	if (!file.is_open())
	{
		// Since the file stream failed to open, print an error message
		cout << "wunzip: cannot open file" << endl;
		exit(1);
	}

	// String representation of the binary number
	string countBinStr = "";
	char character;

	// Loop through all lines in the file
	while (file.get(character))
	{
		if (isdigit(character))
		{
			// The current character is a digit. Append it to the binary string
			countBinStr += character;
		}
		else
		{
			// The current character is not a digit. This means that we have hit the
			// end of an encoded run.

			// Decode (decompress) and print the run
			cout << decodeRun(character, countBinStr); // No `endl`

			// Reset and move onto the next encoded character run
			countBinStr = "";
		}
	}
}

int main(int arg, char *argv[])
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

		// Unzip the file.
		// `unzipFile` will check if the file stream is open
		unzipFile(file);
	}

	// We've unzipped all the files!
	return 0;
}
