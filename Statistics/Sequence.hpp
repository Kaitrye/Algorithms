#ifndef SEQUENCE_
#define SEQUENCE_

#include <fstream>
#include <iostream>

class Sequence
{
	int* heap_; // Куча для поиска характеристик

	int A_;
	int B_;
	int C_;
	int x0_;
	int x1_;

	size_t size_;

	int get ()
	{
		int x2 = A_ * x0_ + B_ * x1_ + C_;
		x0_ = x1_;
		x1_ = x2;

		return x2;
	}

	void shift_down (int pos, size_t size)
	{
		while (2 * pos + 1 < size)
		{
			int posMaxChild = 2 * pos + 1;
			if (2 * pos + 2 < size)
			{
				if (heap_[posMaxChild] < heap_[posMaxChild + 1])
				{
					++posMaxChild;
				}
			}

			if (heap_[pos] < heap_[posMaxChild])
			{
				std::swap (heap_[pos], heap_[posMaxChild]);
				pos = posMaxChild;
			} else
			{
				break;
			}
		}
	}

public:
	Sequence (int A, int B, int C, int x0, int x1, size_t size) : heap_ (nullptr),
		A_ (A), B_ (B), C_ (C), x0_ (x0), x1_ (x1), size_ (size)
	{}

	void print_kth (int begin, int end, std::ostream& out = std::cout)
	{
		// Создаем кучу с end наименьшими элементами
		heap_ = new int[end];
		heap_[0] = x0_;
		heap_[1] = x1_;

		for (size_t i = 2; i < end; ++i)
		{
			heap_[i] = get ();
		}

		for (int i = end / 2 - 1; i >= 0; --i)
		{
			shift_down (i, end);
		}

		for (size_t i = end; i < size_; ++i)
		{
			int x = get ();
			if (heap_[0] > x)
			{
				heap_[0] = x;
				shift_down (0, end);
			}
		}

		// Сортируем получившуюся кучу
		for (int i = end - 1; i > 0; --i)
		{
			std::swap (heap_[0], heap_[i]);
			shift_down (0, i);
		}

		// Выводим нужные элементы
		for (size_t i = begin - 1; i < end - 1; ++i)
		{
			out << heap_[i] << ' ';
		}
		out << heap_[end - 1];
	}

	~Sequence ()
	{
		delete[] heap_;
	}
};

#endif // SEQUENCE_