#ifndef SEQUENCE_
#define SEQUENCE_

#include <fstream>
#include <iostream>

class Sequence
{
	int* data_;
	size_t size_;

	void QuickSelect (int left, int right, int k)
	{
		while (left <= right)
		{
			int p = data_[left + (right - left) / 2];
			int i = left;
			int j = right;

			// Partition
			while (i <= j)
			{
				while (data_[i] < p){
					++i;
				}

				while (data_[j] > p){
					--j;
				}

				if (i <= j)
				{
					std::swap (data_[i], data_[j]);
					++i;
					--j;
				}
			}

			// Выбор нужной части
			if (k <= j)
			{
				right = j;
			}
			else if (k >= i)
			{
				left = i;
			}
			else
			{
				return;
			}
		}
	}

	void QuickSort (int left, int right)
	{
		int p = data_[left + (right - left) / 2];
		int i = left;
		int j = right;

		while (i <= j)
		{
			while (data_[i] < p)
			{
				++i;
			}

			while (data_[j] > p)
			{
				--j;
			}

			if (i <= j)
			{
				std::swap (data_[i], data_[j]);
				++i;
				--j;
			}
		}

		if (left < j) {
			QuickSort (left, j);
		}

		if (i < right) {
			QuickSort (i, right);
		}
	}

public:
	Sequence (int A, int B, int C, int x0, int x1, size_t size) : size_ (size)
	{
		if (size_ == 0)
		{
			data_ = nullptr;
		} else
		{
			data_ = new int[size_];
			data_[0] = x0;
			if (size_ > 1)
			{
				data_[1] = x1;
			}

			for (size_t i = 2; i < size_; ++i)
			{
				data_[i] = A * data_[i - 2] + B * data_[i - 1] + C;
			}
		}
	}

	void print_kth (int begin, int end, std::ostream& out = std::cout)
	{
		// Частичная сортировка массива для поиска двух крайних порядковых характеристик
		QuickSelect (0, size_ - 1, end - 1);
		QuickSelect (0, end - 1, begin - 1);

		// Сортировка нужного отрезка
		QuickSort (begin - 1, end - 1);

		// Вывод результата
		for (int i = begin - 1; i < end - 1; ++i)
		{
			out << data_[i] << ' ';
		}
		out << data_[end - 1];
	}

	~Sequence ()
	{
		delete[] data_;
	}
};

#endif // SEQUENCE_