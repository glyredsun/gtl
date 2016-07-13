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

template <typename Iterator, typename BufType, typename Comparator>
void merge(Iterator first, Iterator last, BufType::iterator bufFirst, Comparator lessThan)
{
	int count = gtl::distance(first, last);
	Iterator left = first;
	Iterator leftEnd = first + cout / 2;
	Iterator right = leftEnd + 1;
	Iterator rightEnd = last;
	Iterator bufCur = bufFirst;

	while (left <= leftEnd && right <= rightEnd) {
		if (lessThan(*left, *right))
			*bufCur++ = *left++;
		else
			*bufCur++ = *right++;
	}

	while (left <= leftEnd)
		*bufCur++ = *left++;

	while (right <= rightEnd)
		*bufCur++ = *right++;


}

template <typename Iterator, typename BufType, typename Comparator>
void mergetSort(Iterator first, Iterator last, BufType::iterator bufFirst, Comparator lessThan)
{
	if (first < last)
	{
		int count = gtl::distance(first, last);
		Iterator center = first + count / 2;
		BufType::iterator bufCenter = bufFirst + count / 2;
		mergetSort(first, center, bufFirst, lessThan);
		mergetSort(center + 1, last, bufCenter + 1, lessThan);
		merge(first, last, bufFirst, lessThan);
	}
}

template <typename Iterator, typename Comparator>
void mergeSort(Iterator first, Iterator last, Comparator lessThan)
{
	vector<decltype(*Iterator)> tmp(distance(first, last));
	mergeSort(first, last, tmp.begin(), lessThan);
}

template <typename Iterator>
void mergeSort(Iterator first, Iterator last)
{
	mergeSort(first, last, [](const decltype(*Iterator) &left, const decltype(*Iterator) &right) { return *left < *last; });
}

#endif // !_SORT_HPP_
