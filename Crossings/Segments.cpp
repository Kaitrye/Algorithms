#include "Segments.hpp"

ull Crossings::mergeSort (bool (*comp)(const seg&, const seg&))
{
	ull res = 0;
	if (size_ < 2)
	{
		return res;
	}

	seg* tmp = new seg[size_];
	seg* from = M;
	seg* to = tmp;

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
				to[ind_to++] = (comp (from[start1], from[start2])) ? from[start1++] : from[start2++];
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

	if (from != M)
	{
		for (size_t i = 0; i < size_; ++i)
		{
			M[i] = tmp[i];
		}
	}

	delete[] tmp;
	return res;
}

ull Crossings::merge (size_t first, size_t middle, size_t last, bool (*comp)(const seg&, const seg&))
{
	size_t size = last - first + 1;
	seg* tmp = new seg[size];
	ull res = 0;

	size_t i = 0;
	size_t start1 = first;
	size_t end1 = middle;
	size_t start2 = middle + 1;
	size_t end2 = last;

	while (start1 <= end1 && start2 <= end2)
	{
		if (comp (M[start1], M[start2]))
		{
			tmp[i++] = M[start1++];
		} else
		{
			tmp[i++] = M[start2++];
			res += end1 - start1 + 1;
		}
	}

	while (start1 <= end1)
	{
		tmp[i++] = M[start1++];
	}
	while (start2 <= end2)
	{
		tmp[i++] = M[start2++];
	}

	// Копируем обратно в M
	i = 0;
	while (first <= last)
	{
		M[first++] = tmp[i++];
	}

	delete[] tmp;
	return res;
}

ull Crossings::count_inv (size_t first, size_t last, bool (*comp)(const seg&, const seg&))
{
	ull res = 0;

	if (first < last)
	{
		size_t middle = first + (last - first) / 2;
		res += count_inv (first, middle, comp);
		res += count_inv (middle + 1, last, comp);
		res += merge (first, middle, last, comp);
	}

	return res;
}