// Gary Tou
// January 10, 2022
// CPSC 3500, Project 1
// wgrep.cpp

#include <iostream>
#include <fstream>
using namespace std;

void grepStream(istream &stream, char *searchTerm)
{
	// Assume the stream is open (in the case of a file)

	string line;
	// Loop through all lines in the stream
	while (getline(stream, line))
	{
		// Search the string (line) for the search term
		if (line.find(searchTerm) != string::npos)
		{
			// The string contains the search term. Print the line
			cout << line << endl;
		}
	}
}

void failureExit()
{
	cout << "wgrep: cannot open file" << endl;
	exit(1);
}

int main(int arg, char *argv[])
{
	try
	{
		// Guard clause for when no command-line arguments are passed in.
		if (arg <= 1)
		{
			cout << "wcat: file [file ...]" << endl;
			return 1;
		}

		// The guard clause above guarrantees that we have a search term argument
		// (however, there may be no file paths)
		char *searchTerm = argv[1];

		// Guard clause for when no file path arguments are passed in
		if (arg == 2)
		{
			// We have a search term, but no file paths. Read the file from the standard
			// input (cin)
			grepStream(cin, searchTerm);

			// we're done!
			return 0;
		}

		// Iterate through the command-line arguments (file paths).
		// The first file path argument starts at index 2 since argv[0] is the name of
		// the program (wgrep) and argv[1] is the search term
		for (int i = 2; i < arg; i++)
		{
			try
			{
				// Get the file path
				char *filePath = argv[i];

				// Create a file stream
				ifstream file(filePath);

				// Guard clause for when the file stream fails to open
				if (!file.is_open())
				{
					// attempt to close the file
					file.close();
					// exit with an error message
					failureExit();
				}

				// Grep the file stream
				grepStream(file, searchTerm);

				// Close the file
				file.close();
			}
			catch (const ifstream::failure &e)
			{
				failureExit();
			}
		}

		// We've grep'ed all the files
		return 0;
	}
	catch (...)
	{
		cout << "wgrep: invalid input" << endl;
		return 1;
	}
}
