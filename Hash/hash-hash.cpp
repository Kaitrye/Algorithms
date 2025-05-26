#include <fstream>
#include <iostream>
#include "Hashmap.hpp"

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

	int N;
	inFile >> N;
	Hashmap set(N);

	char action;
	int x;
	for (int i = 0; i < N; ++i)
	{
		inFile >> action >> x;

		switch (action)
		{
		case '+':
			set.insert (x);
			break;
		case '-':
			set.erase (x);
			break;
		case '?':
			outFile << std::boolalpha << (set.find (x) != -1) << '\n';
			break;
		}
	}

	inFile.close ();
	outFile.close ();
	return 0;
}