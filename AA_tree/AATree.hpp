#ifndef AA_TREE_
#define AA_TREE_

class AATree
{
	struct Node
	{
		int data;
		int level;
		Node* left;
		Node* right;

		Node (int x = 0) : data (x), level (1), left (nullptr), right (nullptr)
		{}
	};

	Node* root;

	static Node* skew (Node* now)
	{
		if (now == nullptr)
		{
			return nullptr;
		}

		if (now->left != nullptr && now->left->level == now->level)
		{
			Node* child = now->left;

			now->left = child->right;
			child->right = now;

			return child;
		}

		return now;
	}

	static Node* split (Node* now)
	{
		if (now == nullptr)
		{
			return nullptr;
		}

		if (now->right != nullptr && now->right->right != nullptr && now->right->right->level == now->level)
		{
			Node* child = now->right;

			++child->level;

			now->right = child->left;
			child->left = now;

			return child;
		}

		return now;
	}

	static Node* minimum (Node* now)
	{
		if (now == nullptr)
		{
			return nullptr;
		}

		while (now->left != nullptr)
		{
			now = now->left;
		}

		return now;
	}

	static Node* maximum (Node* now)
	{
		if (now == nullptr)
		{
			return nullptr;
		}

		while (now->right != nullptr)
		{
			now = now->right;
		}

		return now;
	}

	static Node* decreaseLevel (Node* now)
	{
		if (now == nullptr)
		{
			return nullptr;
		}

		int leftLvl = (now->left == nullptr) ? 0 : now->left->level;
		int rightLvl = (now->right == nullptr) ? 0 : now->right->level;

		int correctLvl = std::min (leftLvl, rightLvl) + 1;

		if (correctLvl < now->level)
		{
			now->level = correctLvl;
			if (now->right != nullptr && correctLvl < now->right->level)
			{
				now->right->level = correctLvl;
			}
		}

		return now;
	}

	Node* insertR (Node* now, int x)
	{
		if (now == nullptr)
		{
			return new Node (x);
		}

		if (x < now->data)
		{
			now->left = insertR (now->left, x);
		} else if (x > now->data)
		{
			now->right = insertR (now->right, x);
		} else
		{
			return now;
		}

		now = skew (now);
		now = split (now);

		return now;
	}

	Node* eraseR (Node* now, int x)
	{
		if (now == nullptr)
		{
			return nullptr;
		}

		if (x < now->data)
		{
			now->left = eraseR (now->left, x);
		} else if (x > now->data)
		{
			now->right = eraseR (now->right, x);
		} else
		{
			if (now->left == nullptr || now->right == nullptr)
			{
				Node* child = (now->left != nullptr) ? now->left : now->right;
				delete now;

				return child;
			}

			Node* alt = minimum (now->right);
			now->data = alt->data;
			now->right = eraseR (now->right, alt->data);
		}

		if (now != nullptr)
		{
			now = decreaseLevel (now);
			now = skew (now);
			if (now->right != nullptr)
			{
				now->right = skew (now->right);
				if (now->right->right != nullptr)
				{
					now->right->right = skew (now->right->right);
				}
			}
			now = split (now);
			if (now->right != nullptr)
			{
				now->right = split (now->right);
			}
		}

		return now;
	}

public:
	AATree () : root (nullptr)
	{}

	void insert (int x)
	{
		root = insertR (root, x);
	}

	void erase (int x)
	{
		root = eraseR (root, x);
	}

	int balance () const
	{
		return (root == nullptr) ? 0 : root->level;
	}

	bool is_in (int x) const
	{
		Node* now = root;

		while (now != nullptr)
		{
			if (x < now->data)
			{
				now = now->left;
			} else if (x > now->data)
			{
				now = now->right;
			} else
			{
				return true;
			}

		}

		return false;
	}

	void clear (Node* now)
	{
		if (now == nullptr)
		{
			return;
		}
		clear (now->left);
		clear (now->right);
		delete now;
	}

	~AATree ()
	{
		clear (root);
	}
};

#endif //AA_TREE_