#ifndef SET_
#define SET_

class Set
{
	int* id;
	int* size;
	size_t length;

public:
	Set (size_t len = 0) : length (len), id (nullptr), size (nullptr)
	{
		if (len > 0)
		{
			id = new int[len];
			size = new int[len];

			for (int i = 0; i < len; ++i)
			{
				id[i] = i;
				size[i] = 1;
			}
		}
	}

	void Union (int x, int y)
	{
		int rx = find (x);
		int ry = find (y);

		if (rx == ry)
		{
			return;
		}

		if (size[rx] < size[ry])
		{
			id[rx] = ry;
			size[ry] += size[rx];
		} else
		{
			id[ry] = rx;
			size[rx] += size[ry];
		}
	}

	int find (int x)
	{
		if (id[x] == x)
		{
			return x;
		}

		return id[x] = find (id[x]);
	}

	~Set ()
	{
		delete[] id;
		delete[] size;
	}
};

#endif // SET_