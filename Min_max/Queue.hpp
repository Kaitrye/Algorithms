#ifndef QUEUE_
#define QUEUE_
#include "Stack.hpp"
#include <iostream>

class Queue
{
	Stack* S[6]; // Расположены в следующем порядке: L, L', S, R, Rc, Rc'
	bool recopy;
	int toCopy;
	bool copied;

	void checkRecopy ()
	{
		recopy = S[0]->size () > S[3]->size ();
		if (recopy)
		{
			toCopy = S[3]->size ();
			copied = false;
			checkNormal ();
		}
	}

	void checkNormal ()
	{
		int toDo = 3;
		while (!copied && toDo > 0 && !S[3]->is_empty ())
		{
			S[2]->push (S[3]->pop ());
			--toDo;
		}

		while (toDo > 0 && !S[0]->is_empty ())
		{
			copied = true;
			int x = S[0]->pop ();
			S[3]->push (x);
			S[5]->push (x);
			--toDo;
		}

		while (toDo > 0 && !S[2]->is_empty ())
		{
			int x = S[2]->pop ();
			if (toCopy > 0)
			{
				S[3]->push (x);
				S[5]->push (x);
				--toCopy;
			}
			--toDo;
		}

		if (S[2]->is_empty ())
		{
			std::swap (S[0], S[1]);
			std::swap (S[4], S[5]);
		}

		recopy = !S[2]->is_empty ();
	}

public:
	Queue () : recopy (false), toCopy (0), copied (true)
	{
		for (size_t i = 0; i < 6; ++i)
		{
			S[i] = new Stack;
		}
	}

	void push (int x)
	{
		if (!recopy)
		{
			S[0]->push (x);
			if (!S[5]->is_empty ())
			{
				S[5]->pop ();
			}
			checkRecopy ();
		} else
		{
			S[1]->push (x);
			checkNormal ();
		}
	}

	int pop ()
	{
		int tmp;
		if (!recopy)
		{
			tmp = S[3]->pop ();
			S[4]->pop ();
			if (!S[5]->is_empty ())
			{
				S[5]->pop ();
			}
			checkRecopy ();
		} else
		{
			tmp = S[4]->pop ();
			if (toCopy > 0)
			{
				--toCopy;
			} else
			{
				S[3]->pop ();
				S[5]->pop ();
			}
			checkNormal ();
		}

		return tmp;
	}

	int diff_max_min () const
	{
		int max_el = S[4]->max ();
		int min_el = S[4]->min ();

		for (size_t i = 0; i < 4; ++i)
		{
			if (!S[i]->is_empty () && i != 2)
			{
				max_el = std::max (S[i]->max (), max_el);
				min_el = std::min (S[i]->min (), min_el);
			}
		}

		return max_el - min_el;
	}

	~Queue ()
	{
		for (size_t i = 0; i < 6; ++i)
		{
			delete S[i];
		}
	}
};

#endif // QUEUE_
