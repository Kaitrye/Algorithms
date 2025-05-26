#ifndef HEAP_
#define HEAP_
#include "Hashmap.hpp"

class Heap
{
	int* data;
	int pos;
	Hashmap indices { 0 };

	void swap (int i, int j)
	{

		indices.change (data[i], j);
		indices.change (data[j], i);

		std::swap (data[i], data[j]);
	}

	void siftDown (int i)
	{
		while (2 * i + 1 < pos)
		{
			int min_child = 2 * i + 1;
			if (2 * i + 2 < pos && data[2 * i + 2] < data[2 * i + 1])
			{
				min_child = 2 * i + 2;
			}

			if (data[i] > data[min_child])
			{
				swap (i, min_child);
				i = min_child;
			} else
			{
				break;
			}
		}
	}

	void siftUp (int i)
	{
		while (i > 0 && data[i] < data[(i - 1) / 2])
		{
			swap (i, (i - 1) / 2);
			i = (i - 1) / 2;
		}
	}

public:
	Heap (int size = 100000) : pos (0), data (nullptr), indices (Hashmap (size))
	{
		if (size > 0)
		{
			data = new int[size];
		}
	}

	void insert (int x)
	{
		data[pos] = x;
		indices.insert (x, pos);
		siftUp (pos);
		++pos;
	}

	int getMin ()
	{
		if (pos == 0)
		{
			throw '*';
		}

		int min = data[0];
		indices.erase (min);
		data[0] = data[--pos];
		siftDown (0);

		return min;
	}


	void change (int cur_x, int new_x)
	{
		int i = indices.find (cur_x);
		if (i != -1)
		{
			data[i] = new_x;
			indices.erase (cur_x);
			indices.insert (new_x, i);
			siftUp (i);
		}
	}

	~Heap ()
	{
		delete[] data;
	}
};

#endif // HEAP_