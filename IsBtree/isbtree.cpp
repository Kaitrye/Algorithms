#include <fstream>
#include <iostream>
#include "BTreeNode.hpp"
#include "AVLTree.hpp"

int main (int argc, char* argv[])
{
	if (argc < 3)
	{
		return -1;
	}

	std::ifstream inFile (argv[1]);
	if (!inFile.is_open ())
	{
		return -2;
	}

	size_t N, t, root;
	inFile >> N >> t >> root;
	inFile.ignore();

	char str[1024];
	size_t d_size = 4 * t + 4;
	char** data = new char* [4 * t + 3]; // 4 + (2 * t - 1) + (2 * t) - этого размера хватит для правильного B-дерева

	AVLTree<Node> tree;
	for (size_t i = 0; i < N; ++i)
	{
		inFile.getline(str, 1024);

		// Парсерим строку, убирая ненужные символы
		int cnt = 0;
		bool in_word = false;
		for (size_t j = 0; str[j] != '\0'; ++j)
		{
			if (str[j] == ':' || str[j] == '(' || str[j] == ')' || str[j] == ' ')
			{
				str[j] = '\0';
				in_word = false;
			}
			else if (str[j] == '0' && str[j + 1] == 'x') // '0x'
			{
				str[j] = '\0';
				str[++j] = '\0';
				in_word = false;
			}
			else if (!in_word)
			{
				in_word = true;
				if (cnt == d_size)
				{
					std::cout << "no" << std::endl;
					delete[] data;
					inFile.close ();
					return 0;
				}

				data[cnt++] = str + j;
			}
		}

		tree.insert(Node(data));
	}

	auto it = tree.find(Node(root));

	int leaf_depth = -1;
	if ((*it).check (t, root, tree, leaf_depth, 0))
	{
		std::cout << "yes" << std::endl;
	}
	else
	{
		std::cout << "no" << std::endl;
	}

	delete[] data;
	inFile.close();
	return 0;
}


