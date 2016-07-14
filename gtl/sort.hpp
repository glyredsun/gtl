#ifndef _SORT_HPP_
#define _SORT_HPP_

#include <algorithm.hpp>
#include <vector.hpp>

#include <thread>

NS_BEGIN(gtl)

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

template <typename Iterator, typename BufIterator, typename Comparator>
void merge(Iterator begin, Iterator end, BufIterator bufBegin, const Comparator &lessThan)
{
	int count = gtl::distance(begin, end);
	Iterator left = begin;
	Iterator leftEnd = begin + count / 2;
	Iterator right = leftEnd;
	Iterator rightEnd = end;
	BufIterator bufCur = bufBegin;

	while (left < leftEnd && right < rightEnd)
		if (lessThan(*left, *right))
			*bufCur++ = std::move(*left++);
		else
			*bufCur++ = std::move(*right++);

	while (left < leftEnd)
		*bufCur++ = std::move(*left++);

	while (right < rightEnd)
		*bufCur++ = std::move(*right++);

	while (begin < end)
		*begin++ = std::move(*bufBegin++);
}

template <typename Iterator, typename BufIterator, typename Comparator>
void mergeSort(Iterator begin, Iterator end, BufIterator bufBegin, const Comparator &lessThan)
{
	int count = gtl::distance(begin, end);
	if (count > 1) {
		Iterator center = begin + count / 2;
		BufIterator bufCenter = bufBegin + count / 2;
		mergeSort(begin, center, bufBegin, lessThan);
		mergeSort(center, end, bufCenter, lessThan);
		merge(begin, end, bufBegin, lessThan);
	}
}

template <typename Iterator, typename Comparator>
void mergeSort(Iterator begin, Iterator end, const Comparator &lessThan)
{
	vector<Iterator::value_type> tmp(distance(begin, end));
	mergeSort(begin, end, tmp.begin(), lessThan);
}

template <typename Iterator>
void mergeSort(Iterator begin, Iterator end)
{
	mergeSort(begin, end, [](const decltype(*begin) &left, const decltype(*begin) &right) { return left < right; });
}

template <typename Iterator, typename Comparator>
void mergeSortParallel(Iterator begin, Iterator end, const Comparator &lessThan)
{
	vector<Iterator::value_type> tmp(distance(begin, end));
	
	unsigned threadsNum = std::thread::hardware_concurrency() / 2 * 2;
	if (threadsNum) {
		unsigned int count = end - begin;
		unsigned int countPerThread = count / threadsNum;
		unsigned int newThreadsNum = threadsNum - 1;
		unsigned int slices = threadsNum;
		gtl::vector<std::thread> threadsVec(newThreadsNum);
		
		for (unsigned int i = 0; i < slices; ++i)
		{
			auto func = [&tmp, =i]() {
				mergeSort(begin + i * countPerThread, begin + (i + 1) * countPerThread, tmp.begin() + i * countPerThread, lessThan);
			};
			if (i < newThreadsNum) {
				threadsVec[i] = std::move(std::thread(func));
			}
			else {
				func();
			}
		}
		for (std::thread &t : threadsVec)
		{
			t.join();
		}
		for (; slices > 0; slices /= 2)
		{

		}
	}
	else {
		mergeSort(begin, end, tmp.begin(), lessThan);
	}
}

NS_END(gtl)

#endif // !_SORT_HPP_
