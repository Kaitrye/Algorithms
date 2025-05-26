#include <fstream>
#include <iostream>
#include "Sequence.hpp"

int main (int argc, char* argv[])
{
	if (argc < 3)
	{
		return -1;
	}

	std::ifstream inFile(argv[1]);
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

	size_t n;
	int begin; 
	int end;

	inFile >> n >> begin >> end;

	int A;
	int B;
	int C;
	int x0;
	int x1;
	inFile >> A >> B >> C >> x0 >> x1;

	Sequence s(A, B, C, x0, x1, n);
	s.print_kth(begin, end);
	
	inFile.close();
	outFile.close();
	return 0;
}
