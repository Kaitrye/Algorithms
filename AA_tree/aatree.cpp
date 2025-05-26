#include <fstream>
#include <iostream>
#include "AATree.hpp"

int main (int argc, char* argv[])
{
	if (argc < 3)
	{
		return -1;
	}

	std::ifstream inFile (argv[1]);
	if (!inFile.is_open ())
	{
		return -2;
	}

	std::ofstream outFile (argv[2]);
	if (!outFile.is_open ())
	{
		inFile.close ();
		return -3;
	}

	AATree set;
	int N;
	inFile >> N;

	char action;
	int x;
	for (int i = 0; i < N; ++i)
	{
		inFile >> action >> x;

		switch (action)
		{
		case '+':
			set.insert (x);
			outFile << set.balance () << '\n';
			break;
		case '-':
			set.erase (x);
			outFile << set.balance () << '\n';
			break;
		case '?':
			outFile << std::boolalpha << set.is_in(x) << '\n';
			break;
		}
	}

	inFile.close ();
	outFile.close ();
	return 0;
}