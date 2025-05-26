#include <iostream>
#include <fstream>
#include "Queue.hpp"

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

	std::ofstream outFile(argv[2]);

	if (!outFile.is_open ())
	{
		inFile.close();
		return -3;
	}

	size_t n;
	inFile >> n;

	Queue queue;
	char command;
	int x;
	while (n-- > 0)
	{
		inFile >> command;

		switch (command)
		{
		case '+':
			inFile >> x;
			queue.push(x);
			break;
		case '-':
			queue.pop();
			break;
		case '?':
			outFile << queue.diff_max_min() << std::endl;
			break;
		}
	}

	inFile.close();
	outFile.close();
	return 0;
}
