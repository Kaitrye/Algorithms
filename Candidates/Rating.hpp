#ifndef RATING_
#define RATING_

#include <fstream>
#include <iostream>

struct Student
{
	size_t id_;
	double score_;
};

class Rating
{
	Student* data_;
	size_t size_;

public:
	Rating () : data_ (nullptr), size_ (0) {}

	void load (char* filename)
	{
		std::ifstream inFile (filename);
		if (!inFile.is_open ())
		{
			throw -1;
		}

		// считываем размер массива и выделяем память.
		inFile >> size_;
		if (size_ > 0)
		{
			data_ = new Student[size_];
		} else
		{
			throw -2;
		}

		// считываем значения массива.
		double x;
		for (size_t i = 0; i < size_; ++i)
		{
			inFile >> x;
			data_[i] = Student { i + 1, x };
		}

		inFile.close ();
	}

	void sort () // Merge sort (итеративный вариант)
	{
		if (size_ < 2)
		{
			return;
		}

		Student* tmp = new Student[size_];
		Student* from = data_;
		Student* to = tmp;

		for (size_t step = 1; step < size_; step *= 2)
		{
			size_t start1;
			size_t end1;
			size_t start2;
			size_t end2;

			size_t ind_to = 0;

			for (size_t start = 0; start < size_; start += 2 * step)
			{
				start1 = start;
				end1 = start + step;
				end1 = (end1 < size_) ? end1 : size_;

				start2 = end1;
				end2 = start2 + step;
				end2 = (end2 < size_) ? end2 : size_;


				while (start1 < end1 && start2 < end2)
				{
					to[ind_to++] = (from[start1].score_ < from[start2].score_) ? from[start1++] : from[start2++];
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

		if (from != data_)
		{
			for (size_t i = 0; i < size_; ++i)
			{
				data_[i] = tmp[i];
			}
		}

		delete[] tmp;
	}

	void print_stat ()
	{
		std::cout << data_[0].id_ << ' ' << data_[(size_ - 1) / 2].id_ << ' ' << data_[size_ - 1].id_ << std::endl;
	}

	~Rating ()
	{
		delete[] data_;
	}
};

#endif // RATING_