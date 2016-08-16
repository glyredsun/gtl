#ifndef _SORT_HPP_
#define _SORT_HPP_

#include <algorithm.hpp>
#include <vector.hpp>

#include <thread>

NS_BEGIN(gtl)

template <class RandomAccessIterator, class Comparator>
void insertionSort(const RandomAccessIterator &begin, const RandomAccessIterator &end, Comparator lessThan)
{
	if (begin == end) {
		return;
	}

	RandomAccessIterator j;

	for (RandomAccessIterator p = begin + 1; p != end; ++p)
	{
		auto tmp = gtl::move(*p);
		for (j = p; j != begin && lessThan(tmp, *(j - 1)); --j)
		{
			*j = gtl::move(*(j - 1));
		}
		*j = gtl::move(tmp);
	}
}

template <class RandomAccessIterator>
void insertionSort(const RandomAccessIterator &begin, const RandomAccessIterator &end)
{
	insertionSort(begin, end, gtl::less<typename iterator_traits<RandomAccessIterator>::value_type>());
}

template <class RandomAccessIterator, class Comparator>
void shellSort(const RandomAccessIterator &begin, const RandomAccessIterator &end, Comparator lessThan)
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

template <class RandomAccessIterator>
void shellSort(const RandomAccessIterator &begin, const RandomAccessIterator &end)
{
	shellSort(begin, end, gtl::less<iterator_traits<RandomAccessIterator>::value_type>());
}

template <class RandomAccessIterator, class Comparator>
void heapSort(const RandomAccessIterator &begin, const RandomAccessIterator &end, const Comparator &predicate)
{
	make_heap(begin, end, predicate);
	sort_heap(begin, end, predicate);
}

template <class RandomAccessIterator>
void heapSort(const RandomAccessIterator &begin, const RandomAccessIterator &end)
{
	auto predicate = gtl::less<typename iterator_traits<RandomAccessIterator>::value_type>();
	make_heap(begin, end, predicate);
	sort_heap(begin, end, predicate);
}

template <class RandomAccessIterator, class BufIterator, class Comparator>
void merge(RandomAccessIterator begin, RandomAccessIterator end, BufIterator bufBegin, const Comparator &lessThan)
{
	int count = gtl::distance(begin, end);
	RandomAccessIterator left = begin;
	RandomAccessIterator leftEnd = begin + count / 2;
	RandomAccessIterator right = leftEnd;
	RandomAccessIterator rightEnd = end;
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

template <class RandomAccessIterator, class BufIterator, class Comparator>
void mergeSort(RandomAccessIterator begin, RandomAccessIterator end, BufIterator bufBegin, const Comparator &lessThan)
{
	int count = gtl::distance(begin, end);
	if (count > 16) {
		RandomAccessIterator center = begin + count / 2;
		BufIterator bufCenter = bufBegin + count / 2;
		mergeSort(begin, center, bufBegin, lessThan);
		mergeSort(center, end, bufCenter, lessThan);
		merge(begin, end, bufBegin, lessThan);
	} else {
		insertionSort(begin, end, lessThan);
	}
}

template <class RandomAccessIterator, class Comparator>
void mergeSort(RandomAccessIterator begin, RandomAccessIterator end, const Comparator &lessThan)
{
	if (end - begin > 16) {
		vector<iterator_traits<RandomAccessIterator>::value_type> buf(distance(begin, end));
		mergeSort(begin, end, buf.begin(), lessThan);
	}
	else {
		insertionSort(begin, end);
	}
	
}

template <class RandomAccessIterator>
void mergeSort(RandomAccessIterator begin, RandomAccessIterator end)
{
	mergeSort(begin, end, gtl::less<typename iterator_traits<RandomAccessIterator>::value_type>());
}

template <class RandomAccessIterator, class Comparator>
void mergeSortParallel(RandomAccessIterator begin, RandomAccessIterator end, const Comparator &predicate)
{
	typedef vector<iterator_traits<RandomAccessIterator>::value_type> BufType;
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
				mergeSort(begin + i * countPerSlice, begin + (i + 1) * countPerSlice, bufBegin + i * countPerSlice, predicate);
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
					merge(begin + i * countPerSlice, begin + (i + 1) * countPerSlice, bufBegin + i * countPerSlice, predicate);
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
		mergeSort(begin, end, tmp.begin(), predicate);
	}
}

template <class RandomAccessIterator>
void mergeSortParallel(RandomAccessIterator begin, RandomAccessIterator end)
{
	mergeSortParallel(begin, end, gtl::less<typename iterator_traits<RandomAccessIterator>::value_type>());
}

template <class RandomAccessIterator, class Comparator>
void quickSort(RandomAccessIterator begin, RandomAccessIterator end, const Comparator &predicate)
{
	auto count = gtl::distance(begin, end);
	
	if (count >= 10) {

		auto first = 0;
		auto center = count / 2;
		auto last = count - 1;

		if (predicate(begin[center], begin[first])) {
			gtl::swap(begin[center], begin[first]);
		}

		if (predicate(begin[last], begin[first])) {
			gtl::swap(begin[last], begin[first]);
		}

		if (predicate(begin[last], begin[center])) {
			gtl::swap(begin[last], begin[center]);
		}

		gtl::swap(begin[center], begin[last - 1]);

		const auto &pivot = begin[last - 1];

		auto i = first;
		auto j = last - 1;

		while (true)
		{
			while (predicate(begin[++i]), pivot);
			while (predicate(pivot, begin[--j]));
			
			if (i < j)
				gtl::swap(begin[i], begin[j]);
			else
				break;
		}

		gtl::swap(begin[i], begin[last - 1]);

		quickSort(begin, begin + center, predicate);
		quickSort(begin + center, begin + count, predicate);
	}
	else
		insertionSort(begin, end, predicate);
}

template <class RandomAccessIterator>
void quickSort(RandomAccessIterator begin, RandomAccessIterator end)
{
	quickSort(begin, end, gtl::less<>(typename gtl::iterator_traits<RandomAccessIterator>::value_type));
}

NS_END(gtl)

#endif // !_SORT_HPP_
