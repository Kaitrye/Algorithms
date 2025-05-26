#ifndef GAME_
#define GAME_

#include <iostream>
#include <fstream>
#include <cstring>

extern const int MAX_STEPS;

// карта.
struct card
{
	int value;
	char suit;
};

std::istream& operator>> (std::istream&, card&);
bool operator==(const card&, const card&);
bool operator<(const card&, const card&);

// стопка карт.
class stack
{
	card s[52] {};
	int top_;

public:
	stack () : top_ (-1) {};

	void push (card);
	card pop ();
	card top () const;
	bool empty () const;
};

// Перекладывание карт из стопки под низ колоды игрока.
void add (stack& player, stack* pack);

#endif //GAME_


