#ifndef RADIX_
#define RADIX_

#include <fstream>
#include <iostream>

class Dict
{
	char** data_;
	size_t n;
	size_t len;
	
public:
	Dict(size_t rows, int chars) : data_(nullptr), n(rows), len(chars)
	{
		if (n != 0)
		{
			data_ = new char*[n];
			for (size_t i = 0; i < n; ++i)
			{
				data_[i] = new char[len + 1];
			}
		}
	}

	void load (std::istream& inFile = std::cin)
	{
		char* row = new char[n + 1];
		for (size_t i = 0; i < len; ++i)
		{
			inFile >> row;
			for (size_t j = 0; j < n; ++j)
			{
				data_[j][i] = row[j];
			}
		}
		delete[] row;
	}

	void sort (int k)
	{
		if (n < 2)
		{
			return;
		}

		char** res = new char* [n];

		for (int i = len - 1; i >= int(len) - k; --i)
		{
			int sym[256] { 0 };

			for (size_t j = 0; j < n; ++j)
			{
				++sym[data_[j][i]];
			}

			int cnt = 0;
			int tmp = 0;
			for (size_t j = 0; j < 256; ++j)
			{
				tmp = sym[j];
				sym[j] = cnt;
				cnt += tmp;
			}

			for (size_t j = 0; j < n; ++j)
			{
				char d = data_[j][i];
				res[sym[d]] = data_[j];
				++sym[d];
			}

			for (size_t i = 0; i < n; ++i)
			{
				data_[i] = res[i];
			}
		}

		delete[] res;
	}

	void print_first (std::ostream& outFile = std::cout)
	{
		for (size_t i = 0; i < n; ++i)
		{
			outFile << data_[i][0];
		}
	}

	~Dict ()
	{
		for (size_t i = 0; i < n; ++i)
		{
			delete[] data_[i];
		}
		delete[] data_;
	}
};

#endif // !RADIX_

