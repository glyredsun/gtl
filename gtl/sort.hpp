#ifndef _SORT_HPP_
#define _SORT_HPP_

#include <algorithm.hpp>
#include <vector.hpp>

template <typename Iterator, typename Comparator>
void insertionSort(const Iterator &begin, const Iterator &end, Comparator lessThan)
{
	if (begin == end) {
		return;
	}

	Iterator j;

	for (Iterator p = begin + 1; p != end; ++p)
	{
		auto tmp = std::move(*p);
		for (j = p; j != begin && lessThan(tmp, *(j - 1)); --j)
		{
			*j = std::move(*(j - 1));
		}
		*j = std::move(tmp);
	}
}

template <typename Iterator>
void insertionSort(const Iterator &begin, const Iterator &end)
{
	insertionSort(begin, end, [](const decltype(*begin) &first, const decltype(*begin) second) { return first < second; });
}

template <typename Iterator, typename Comparator>
void shellSort(const Iterator &begin, const Iterator &end, Comparator lessThan)
{
	for (int gap = (end - begin) / 2; gap > 0; gap /= 2)
	{
		for (int i = gap; i < end - begin; ++i)
		{
			auto tmp = std::move(*(begin + i));
			int j = i;

			for (; j >= gap && lessThan(tmp, *(begin + j - gap)); j -= gap)
			{
				*(begin + j) = std::move(*(begin + j - gap));
			}
			*(begin + j) = std::move(tmp);
		}
	}
}

template <typename Iterator>
void shellSort(const Iterator &begin, const Iterator &end)
{
	shellSort(begin, end, [](const decltype(*begin) first, const decltype(*begin) second) { return first < second; });
}

template <typename Iterator>
void merge(Iterator first, Iterator last, gtl::vector<decltype(*Iterator)>::iterator bufFirst, gtl::vector<decltype(*Iterator)>::iterator bufLast)
{
	
}

template <typename Iterator>
void mergetSort(Iterator first, Iterator last, gtl::vector<decltype(*Iterator)>::iterator bufFirst, gtl::vector<decltype(*Iterator)>::iterator bufLast)
{
	if (first < last)
	{
		Iterator center = first + gtl::distance(first, last) / 2;
		gtl::vector<decltype(*Iterator)>::iterator bufCenter = bufFirst + gtl::distance(bufFirst, bufLast) / 2;
		mergetSort(first, center, bufFirst, bufCenter);
		mergetSort(center + 1, last, bufCenter + 1, bufLast);
		merge(first, last, bufFirst, bufLast);
	}
}

template <typename Iterator>
void mergeSort(Iterator first, Iterator last, const std::function<bool (const decltype(*Iterator) &left, const decltype(*Iterator) &right)> &lessThan)
{
	vector<decltype(*Iterator)> tmp(distance(first, last));
	mergeSort(first, last, tmp.begin(), tmp.end());
}

#endif // !_SORT_HPP_
