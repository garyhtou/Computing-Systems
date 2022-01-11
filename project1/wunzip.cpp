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

void failureExit()
{
	cout << "wunzip: cannot open file" << endl;
	exit(1);
}
void unzipFile(ifstream &file)
{
	try
	{
		// Guard clause for when the file stream fails to open
		if (!file.is_open())
		{
			// Since the file stream failed to open, print an error message
			failureExit();
		}

		// String representation of the binary number
		string countBinStr = "";
		// We are forced to implement are counter to 32 bits instead of using a
		// non '1' and '0' character as a delimiter. This is because '1' and '0' can
		// appear as a char in the encoded string
		int counter = 0;
		char character;

		// Loop through all lines in the file
		while (file.get(character))
		{
			// Increment the counter
			counter++;

			bool isBinaryChar = character == '1' || character == '0';
			bool isCharOfRun = counter == 32 + 1; // 32 count + 1 char
			if (isBinaryChar && !isCharOfRun)
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
				counter = 0;
			}
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
	catch (...)
	{
		cout << "wunzip: invalid input" << endl;
		return 1;
	}
}
