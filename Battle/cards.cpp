#include "cards.hpp"

const int MAX_STEPS = 1000000;

std::istream& operator>> (std::istream& in, card& x)
{
	char buf[8];
	in.getline (buf, 8);

	switch (buf[0])
	{
	case 'A':
		x.value = 14;
		break;
	case 'K':
		x.value = 13;
		break;
	case 'Q':
		x.value = 12;
		break;
	case 'J':
		x.value = 11;
		break;
	case '1':
		x.value = 10;
		break;
	default:
		x.value = buf[0] - '0';
	}

	x.suit = buf[strlen (buf) - 1];

	return in;
}

bool operator==(const card& left, const card& right)
{
	return left.value == right.value;
}

bool operator<(const card& left, const card& right)
{
	if (left.value == 14 && right.value == 2)
	{
		return true;
	}

	if (left.value == 2 && right.value == 14)
	{
		return false;
	}

	return (left.value < right.value);
}

void stack::push (card x)
{
	if (top_ < 51)
	{
		s[++top_] = x;
	} else
	{
		throw "error";
	}
}

card stack::pop ()
{
	if (top_ < 0)
	{
		throw "error";
	}
	
	return s[top_--];
}

card stack::top () const
{	
	if (top_ < 0)
	{
		throw "error";
	}

	return s[top_];
}

bool stack::empty () const
{
	return top_ < 0;
}

void add (stack& player, stack* pack)
{
	while (!player.empty ())
	{
		pack[1].push (player.pop ());
	}

	while (!pack[0].empty ())
	{
		player.push (pack[0].pop ());
	}

	while (!pack[1].empty ())
	{
		player.push (pack[1].pop ());
	}
}
