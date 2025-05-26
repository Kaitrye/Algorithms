#ifndef HASHMAP_
#define HASHMAP_
#include <cmath>

class Hashmap
{
	struct Node
	{
		int key;
		int value;
		bool is_deleted = false;

		Node (int k = 0, int x = 0) : key(k), value (x), is_deleted (false) {}
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

	void insert (int key, int x)
	{
		size_t i = 0;
		do
		{
			int j = hash (key, i);
			if (data[j] == nullptr || data[j]->is_deleted)
			{
				delete data[j];
				data[j] = new Node(key, x);
				return;
			}

			if (data[j]->key == key)
			{
				return;
			}

			++i;
		} while (i < size);
	}

	void erase (int key)
	{
		int j = find_ind (key);
		if (j == -1)
		{
			return;
		}

		data[j]->is_deleted = true;
	}

	int find_ind (int key)
	{
		size_t i = 0;
		do
		{
			int j = hash (key, i);
			if (data[j] == nullptr)
			{
				return -1;
			}

			if (!data[j]->is_deleted && data[j]->key == key)
			{
				return j;
			}

			++i;
		} while (i < size);

		return -1;
	}

	int find (int key)
	{
		size_t i = 0;
		do
		{
			int j = hash (key, i);
			if (data[j] == nullptr)
			{
				return -1;
			}

			if (!data[j]->is_deleted && data[j]->key == key)
			{
				return data[j]->value;
			}

			++i;
		} while (i < size);

		return -1;
	}

	void change (int key, int new_x)
	{
		int j = find_ind (key);
		if (j == -1)
		{
			return;
		}

		data[j]->value = new_x;
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
