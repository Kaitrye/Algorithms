#include <fstream>
#include <iostream>
#include <cstring>
#include "Heap.hpp"

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

	Heap queue;
	int* history = new int[100000]{0};
	int line = 0;

	char str[1024];
	char** data = new char* [4];

	while (inFile.peek () != EOF)
	{
		++line;
		inFile.getline (str, 1024);

		// Парсерим строку, убирая ненужные символы
		int cnt = 0;
		bool in_word = false;
		for (int j = 0; str[j] != '\0'; ++j)
		{
			if (str[j] == ' ')
			{
				str[j] = '\0';
				in_word = false;
			} 
			else if (!in_word)
			{
				in_word = true;
				data[cnt++] = str + j;
			}
		}

		// Выполняем команду
		if (strcmp (data[0], "push") == 0)
		{
			int x = atoi(data[1]);
			queue.insert(x);
			history[line] = x;
		}
		else if (strcmp (data[0], "extract-min") == 0)
		{
			try
			{
				outFile << queue.getMin ();
			}
			catch (char error)
			{
				outFile << error;
			}
			outFile << '\n';
		}
		else if (strcmp (data[0], "decrease-key") == 0)
		{
			int num = atoi(data[1]);
			int x = atoi(data[2]);

			queue.change(history[num], x);
		}
	}

	delete[] data;
	delete[] history;
	return 0;
}

