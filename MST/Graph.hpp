#ifndef GRAPH_
#define GRAPH_
#include "Set.hpp"

class Graph
{
	struct Edge
	{
		int begin;
		int end;
		int weight;
	};

	Edge* E;
	Set* V;
	size_t cnt_E;
	size_t cnt_V;

public:
	Graph () : E (nullptr), V (nullptr), cnt_E (0), cnt_V (0)
	{}
	void load (char* filename)
	{
		std::ifstream inFile (filename);
		if (!inFile.is_open ())
		{
			throw - 1;
		}

		inFile >> cnt_V >> cnt_E;
		if (cnt_E > 0)
		{
			E = new Edge[cnt_E];
		} else
		{
			E = nullptr;
		}

		V = new Set (cnt_V);

		int begin;
		int end;
		int weight;
		for (size_t i = 0; i < cnt_E; ++i)
		{
			inFile >> begin >> end >> weight;
			E[i] = Edge { begin, end, weight };
		}

		inFile.close ();
	}

	void sort () // Merge sort (итеративный вариант)
	{
		if (cnt_E < 2)
		{
			return;
		}

		Edge* tmp = new Edge[cnt_E];
		Edge* from = E;
		Edge* to = tmp;

		for (size_t step = 1; step < cnt_E; step *= 2)
		{
			size_t start1;
			size_t end1;
			size_t start2;
			size_t end2;

			size_t ind_to = 0;

			for (size_t start = 0; start < cnt_E; start += 2 * step)
			{
				start1 = start;
				end1 = start + step;
				end1 = (end1 < cnt_E) ? end1 : cnt_E;

				start2 = end1;
				end2 = start2 + step;
				end2 = (end2 < cnt_E) ? end2 : cnt_E;


				while (start1 < end1 && start2 < end2)
				{
					to[ind_to++] = (from[start1].weight < from[start2].weight) ? from[start1++] : from[start2++];
				}

				while (start1 < end1)
				{
					to[ind_to++] = from[start1++];
				}
				while (start2 < end2)
				{
					to[ind_to++] = from[start2++];
				}

			}

			std::swap (from, to);
		}

		if (from != E)
		{
			for (size_t i = 0; i < cnt_E; ++i)
			{
				E[i] = tmp[i];
			}
		}

		delete[] tmp;
	}

	int MST ()
	{
		sort ();

		int result = 0;
		for (size_t i = 0; i < cnt_E; ++i)
		{
			int x = E[i].begin;
			int y = E[i].end;

			if (V->find (x) != V->find (y))
			{
				V->Union (x, y);
				result += E[i].weight;
			}
		}

		return result;
	}

	~Graph ()
	{
		delete[] E;
		delete V;
	}
};

#endif // GRAPH_
