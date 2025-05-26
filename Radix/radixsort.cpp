#include <fstream>
#include <iostream>
#include "Radix.hpp"

int main(int argc, char* argv[]){

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
		inFile.close();
		return -3;
	}

	size_t N;
	int size;
	int k;
	inFile >> N >> size >> k;

	Dict dict(N, size);
	dict.load(inFile);
	dict.sort(k);
	dict.print_first(outFile);

	outFile.close();
	inFile.close ();

	return 0;
}
