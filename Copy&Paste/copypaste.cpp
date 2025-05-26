#include <iostream>
#include <fstream>
#include <cstring>
#include "TextEditor.hpp"

int main (int argc, char* argv[])
{
	if (argc < 4)
	{
		return -3;
	}

	TextEditor text;

	// считываем строки из файла в список.
	text.load(argv[1]);

	// считываем и выполняем команды.
	std::ifstream inFile(argv[2]);
	if (!inFile.is_open ())
	{
		return -4;
	}

	char action[8];
	while (inFile.peek () != EOF)
	{
		inFile.getline(action, 8);

		// При необходимости удаляем последний символ '\r'.
		if (action[strlen (action) - 1] == '\r')
		{
			action[strlen (action) - 1] = '\0';
		}
		
		if (strcmp (action, "Down") == 0)
		{
			--text;
		}
		else if (strcmp (action, "Up") == 0)
		{
			++text;
		}
		else if (strcmp (action, "Shift") == 0)
		{
			text.shift();
		}
		else if (strcmp (action, "Ctrl+X") == 0)
		{
			text.erase();
		}
		else if (strcmp (action, "Ctrl+V") == 0)
		{
			text.paste();
		}
	}

	inFile.close();

	// записываем получившийся список в файл.
	text.save(argv[3]);

	return 0;
}