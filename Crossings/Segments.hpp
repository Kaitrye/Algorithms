#ifndef Segments_
#define Segments_

#include <fstream>

typedef unsigned long long ull;

class Crossings
{
	struct seg
	{
		int x1;
		int x2;
	};

	static bool comp_by_x1 (const seg& left, const seg& right)
	{
		return left.x1 < right.x1;
	}

	static bool comp_by_x2 (const seg& left, const seg& right)
	{
		return left.x2 < right.x2;
	}

	seg* M;
	size_t size_;

	// Merge sort (итеративный вариант)
	ull mergeSort (bool (*comp)(const seg&, const seg&));

	// Merge sort - рекурсивный вариант с подсчетом инверсий
	ull merge (size_t first, size_t middle, size_t last, bool (*comp)(const seg&, const seg&));
	ull count_inv (size_t first, size_t last, bool (*comp)(const seg&, const seg&));

public:
	Crossings () : M(nullptr), size_(0) {}

	void load (char* filename)
	{
		std::ifstream inFile (filename);
		if (!inFile.is_open ())
		{
			throw -1;
		}

		inFile >> size_;
		M = new seg[size_];

		for (size_t i = 0; i < size_; ++i)
		{
			seg cur;
			inFile >> cur.x1 >> cur.x2;
			M[i] = cur;
		}

		inFile.close();
	}

	ull count ()
	{
		mergeSort(comp_by_x1);
		return count_inv (0, size_ - 1, comp_by_x2);
	}

	~Crossings() {
		delete[] M;
	}
};

#endif // Segments_