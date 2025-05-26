#include <iostream>
#include <fstream>
#include "Segments.hpp"

int main (int argc, char* argv[])
{
	if (argc < 2)
	{
		return -1;
	}

	Crossings cross;
	cross.load(argv[1]);

	std::cout << cross.count();

	return 0;
}
