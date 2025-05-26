#include <iostream>
#include <fstream>
#include "cards.hpp"

int main (int argc, char* argv[])
{
	if (argc < 2)
	{
		return -1;
	}

	std::ifstream inFile(argv[1]);

	if (!inFile.is_open ())
	{
		return -2;
	}

	/*
		Раздача карт.
	*/

	card x;
	stack player[2]; // колоды карт игроков.
	stack pack[2]; // стопка вскрытых карт + доп. стек для перекладывания карт под низ колоды игрока.

	while (inFile.peek () != EOF)
	{
		inFile >> x;
		pack[0].push(x);
	}

	int cnt = 52; // количество нерозданных карт.
	while (!pack[0].empty ())
	{
		player[--cnt / 26].push(pack[0].pop());
	}

	/*
		Игра.
	*/

	card left;
	card right;
	cnt = 0; // количество сделанных ходов игры.

	while (!player[0].empty() && !player[1].empty() && ++cnt <= MAX_STEPS)
	{
		left = player[0].pop ();
		right = player[1].pop ();

		pack[0].push(left);
		pack[0].push(right);

		if (left == right)
		{
			continue;
		}
		
		if (left < right)
		{
			add(player[1], pack);
		}
		else
		{
			add(player[0], pack);
		}
	}

	/*
		Подведение итогов игры.
	*/
	
	bool win1 = player[1].empty ();
	bool win2 = player[0].empty ();

	if (win1 && win2)
	{
		std::cout << "draw";
	}
	else if (win2)
	{
		std::cout << "second";
	}
	else if (win1)
	{
		std::cout << "first";
	}
	else
	{
		std::cout << "unknown";
	}

	inFile.close();
	return 0;
}

