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
		auto tmp = gtl::move(*p);
		for (j = p; j != begin && lessThan(tmp, *(j - 1)); --j)
		{
			*j = gtl::move(*(j - 1));
		}
		*j = gtl::move(tmp);
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
			auto tmp = gtl::move(*(begin + i));
			int j = i;

			for (; j >= gap && lessThan(tmp, *(begin + j - gap)); j -= gap)
			{
				*(begin + j) = gtl::move(*(begin + j - gap));
			}
			*(begin + j) = gtl::move(tmp);
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
			*bufCur++ = gtl::move(*left++);
		else
			*bufCur++ = gtl::move(*right++);

	while (left < leftEnd)
		*bufCur++ = gtl::move(*left++);

	while (right < rightEnd)
		*bufCur++ = gtl::move(*right++);

	while (begin < end)
		*begin++ = gtl::move(*bufBegin++);
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
	typedef vector<Iterator::value_type> BufType;
	BufType tmp(distance(begin, end));
	BufType::iterator bufBegin = tmp.begin();

	unsigned int threadsNum = std::thread::hardware_concurrency() / 2 * 2;
	
	if (threadsNum) {

		unsigned int slices = lastPOT(threadsNum);
		unsigned int count = end - begin;
		unsigned int countPerSlice = count / slices;
		unsigned int newThreadsNum = slices - 1;
		
		gtl::vector<std::thread> threadsVec(newThreadsNum);
		
		// merge sort little slices in every thread
		for (unsigned int i = 0; i < slices; ++i)
		{
			auto func = [=]() {
				mergeSort(begin + i * countPerSlice, begin + (i + 1) * countPerSlice, bufBegin + i * countPerSlice, lessThan);
			};
			if (i < newThreadsNum) {
				// do work in new thread
				threadsVec[i] = gtl::move(std::thread(func));
			} else {
				// do work in current thread
				func();
			}
		}

		// wait for every new thread done work
		for (std::thread &t : threadsVec)
		{
			t.join();
		}

		// merge little slice to twice one
		while ((slices /= 2) > 0)
		{
			countPerSlice = count / slices;
			newThreadsNum = slices - 1;

			threadsVec.resize(newThreadsNum);

			for (unsigned int i = 0; i < slices; ++i)
			{
				auto func = [=]() {
					merge(begin + i * countPerSlice, begin + (i + 1) * countPerSlice, bufBegin + i * countPerSlice, lessThan);
				};
				if (i < newThreadsNum) {
					threadsVec[i] = gtl::move(std::thread(func));
				}
				else {
					func();
				}
			}

			for (std::thread &t : threadsVec)
			{
				t.join();
			}
		}
	}
	else {
		mergeSort(begin, end, tmp.begin(), lessThan);
	}
}

template <typename Iterator>
void mergeSortParallel(Iterator begin, Iterator end)
{
	mergeSortParallel(begin, end, [](const decltype(*begin) &left, const decltype(*begin) &right) { return left < right; });
}

NS_END(gtl)

#endif // !_SORT_HPP_
