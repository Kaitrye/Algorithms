#ifndef BTREE_
#define BTREE_

#include <fstream>
#include <iostream>
#include <climits>
#include <cstring>
#include "AVLTree.hpp"

class Node
{
	int ID;
	bool is_leaf;
	int n_key;
	int* keys;
	int n_child;
	int* children;

public:
	Node (int id) :
		ID (id),
		is_leaf (false),
		n_key (0),
		n_child (0),
		keys (nullptr),
		children (nullptr)
	{}

	Node (char** data) :
		n_child (0),
		keys (nullptr),
		children (nullptr)
	{
		int ind = 0;
		is_leaf = (strcmp (data[ind++], "leaf") == 0);
		ID = atoi (data[ind++]);

		n_key = atoi (data[ind++]);
		if (n_key > 0)
		{
			keys = new int[n_key];
			for (int i = 0; i < n_key; ++i)
			{
				keys[i] = atoi (data[ind++]);
			}
		}

		if (!is_leaf)
		{
			n_child = atoi (data[ind++]);
			if (n_child > 0)
			{
				children = new int[n_child];
				for (int i = 0; i < n_child; ++i)
				{
					children[i] = atoi (data[ind++]);
				}
			}
		}
	}

	Node (const Node& other) :
		ID (other.ID),
		is_leaf (other.is_leaf),
		n_key (other.n_key),
		n_child (other.n_child),
		keys (nullptr),
		children (nullptr)
	{
		if (n_key > 0)
		{
			keys = new int[n_key];
			for (int i = 0; i < n_key; ++i)
			{
				keys[i] = other.keys[i];
			}
		}

		if (!is_leaf && n_child > 0)
		{
			children = new int[n_child];
			for (int i = 0; i < n_child; ++i)
			{
				children[i] = other.children[i];
			}
		}
	}

	bool check (int t, int root, const AVLTree<Node>& tree, int& leaf_depth, int height, int mn = INT_MIN, int mx = INT_MAX) const
	{
		// Проверяем количество ключей
		if ((ID == root && n_key < 1) || (ID != root && n_key < t - 1) || n_key > 2 * t - 1)
		{
			return false;
		}

		// Проверяем упорядоченность ключей
		for (int i = 1; i < n_key; ++i)
		{
			if (keys[i] < keys[i - 1])
			{
				return false;
			}
		}

		// Проверяем сохранение порядка относительно предыдущих узлов
		if (keys[0] < mn || keys[n_key - 1] > mx)
		{
			return false;
		}

		if (!is_leaf)
		{
			// Проверяем количество потомков
			if (n_child != n_key + 1)
			{
				return false;
			}

			// Проверяем рекурсивно каждого потомка
			for (int i = 0; i < n_child; ++i)
			{
				auto it = tree.find (Node (children[i]));

				if (it == tree.end ())
				{
					return false;
				}

				int new_mn = (i > 0) ? keys[i - 1] : mn;
				int new_mx = (i < n_key) ? keys[i] : mx;

				if (!(*it).check (t, root, tree, leaf_depth, height + 1, new_mn, new_mx))
				{
					return false;
				}
			}
		} else
		{
			// Проверяем глубину листа
			if (leaf_depth == -1)
			{
				leaf_depth = height;
			} else if (leaf_depth != height)
			{
				return false;
			}
		}

		return true;
	}

	bool operator==(const Node& other) const
	{
		return ID == other.ID;
	}

	bool operator<(const Node& other) const
	{
		return ID < other.ID;
	}

	~Node ()
	{
		delete[] keys;
		delete[] children;
	}
};

#endif // !BTREE_
