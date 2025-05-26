#ifndef HASHMAP_
#define HASHMAP_
#include <cmath>

class Hashmap
{
	struct Node
	{
		int value;
		bool is_deleted = false;

		Node (int x = 0) : value (x), is_deleted (false) {}
	};

	Node** data;
	size_t size;

	int hash (int x)
	{
		double A = sqrt (5) - 1 / 2;
		double x_new = x * A;
		return int(size * (x_new - int(x_new)));
	}

	int hash (int x, int i)
	{
		return (hash(x) + i) % size;
	}

public:
	Hashmap (size_t sz) : size (sz), data (nullptr)
	{
		if (size > 0)
		{
			data = new Node* [size];
			for (size_t i = 0; i < size; ++i)
			{
				data[i] = nullptr;
			}
		}
	}

	void insert (int x)
	{
		size_t i = 0;
		do
		{
			int j = hash (x, i);
			if (data[j] == nullptr || data[j]->is_deleted)
			{
				delete data[j];
				data[j] = new Node(x);
				return;
			}

			if (data[j]->value == x)
			{
				return;
			}

			++i;
		} while (i < size);
	}

	void erase (int x)
	{
		int j = find(x);
		if (j == -1)
		{
			return;
		}

		data[j]->is_deleted = true;
	}

	int find (int x)
	{
		size_t i = 0;
		do
		{
			int j = hash (x, i);
			if (data[j] == nullptr)
			{
				return -1;
			}

			if (!data[j]->is_deleted && data[j]->value == x)
			{
				return j;
			}

			++i;
		} while (i < size);

		return -1;
	}

	void print () const
	{
		for (size_t i = 0; i < size; ++i)
		{
			if (data[i] == nullptr || data[i]->is_deleted)
			{
				std::cout << '-';
			}
			else
			{
				std::cout << data[i]->value;
			}
			std::cout << ' ';
		}
	}

	~Hashmap ()
	{
		for (size_t i = 0; i < size; ++i)
		{
			delete data[i];
		}

		delete[] data;
	}
};

#endif // HASHMAP_
