#ifdef _MSC_VER
#pragma once
#endif

#ifndef ALGORITHMS_HPP_
#define ALGORITHMS_HPP_

#include <macros.hpp>
#include <algorithm.hpp>
#include <type_traits.hpp>
#include <iterator_base.hpp>

#include <cstring>

NS_BEGIN(gtl);

template <typename InIterator, typename OutIterator>
inline OutIterator move(InIterator srcBegin, InIterator srcEnd, OutIterator destBegin)
{
	while (srcBegin < srcEnd)
		*destBegin++ = gtl::move(*srcBegin++);
	return destBegin;
}

template <typename InIterator, typename OutIterator>
inline OutIterator move(InIterator srcBegin, InIterator srcEnd, OutIterator destBegin, OutIterator destEnd)
{
	while (srcBegin < srcEnd && destBegin < destEnd)
		*destBegin++ = gtl::move(*srcBegin++);
	return destBegin;
}

template <typename T>
inline T* move(T *srcBegin, T *srcEnd, T *destBegin)
{
	size_t count = srcEnd - srcBegin;
	memcpy(destBegin, srcBegin, sizeof(T) * count);
	return destBegin + count;
}

template <typename T>
inline T* move(T *srcBegin, T *srcEnd, T *destBegin, T *destEnd)
{
	size_t count = srcEnd - srcBegin < destEnd - destBegin ? srcEnd - srcBegin : destEnd - destBegin;
	memcpy(destBegin, srcBegin, sizeof(T) * count);
	return destBegin + count;
}

// binary search
template <typename Iterator, typename DataType, typename Comparator>
inline Iterator search(Iterator begin, Iterator end, const DataType &target, Comparator &lessThan)
{
	Iterator endCopy = end;
	Iterator middle;

	while (begin < end) {
		middle = begin + (end - begin)/2;
		if (lessThan(*middle, target)) {
			begin = middle;
		} else if (lessThan(target, *middle)) {
			end = middle;
		} else {
			return middle;
		}
	}

	return endCopy;
}

template <typename Iterator, typename DataType>
inline Iterator search(Iterator begin, Iterator end, const DataType &target)
{
	return search(begin, end, target, gtl::less<typename iterator_traits<Iterator>::value_type>());
}

// get the power of two number big than num
template <typename T>
inline T nextPOT(T num)
{
	for (size_t i = 1; i <= sizeof(T) * 8 / 2; i *= 2)
	{
		num = num | num >> i;
	}
	return num + 1;
}

// get the power of two number not big than num
template <typename T>
inline T lastPOT(T num)
{
	return nextPOT(num) >> 1;
}

template <typename T>
inline void swap(T& left, T& right)
{
	if (&left != &right)
	{
		T tmp = gtl::move(left);
		left = gtl::move(right);
		right = gtl::move(tmp);
	}
}

template <typename T>
inline const T& max(const T& a, const T& b)
{
	return a > b ? a : b;
}

template <typename T>
inline const T& min(const T& a, const T& b)
{
	return a < b ? a : b;
}

template <typename Iterator>
typename iterator_traits<Iterator>::defference_type distance(const Iterator first, const Iterator last)
{
	return last - first;
}

template <typename ArgType = void>
struct less
{
	constexpr bool operator() (const ArgType &left, const ArgType &right) const 
	{
		return left < right;
	}
};

template <typename Iterator>
void __percolateDown(Iterator begin, int len, int hole)
{
	typename iterator_traits<Iterator>::value_type tmp = gtl::move(*(begin + hole));
	for (int child; hole * 2 + 1 <= len - 1; hole = child)
	{
		child = hole * 2 + 1;

		if (child != len - 1 && *(begin + child) < *(begin + child + 1))
			++child;

		if (tmp < *(begin + child))
			*(begin + hole) = gtl::move(*(begin + child));
		else
			break;
	}
	*(begin + hole) = gtl::move(tmp);
}

template <typename Iterator>
void __percolateUp(Iterator begin, int hole)
{
	typename iterator_traits<Iterator>::value_type tmp = gtl::move(*(begin + hole));
	int parent = (hole - 1) / 2;
	while (hole > 0 && *(begin + parent) < tmp)
	{
		*(begin + hole) = gtl::move(*(begin + parent));
		hole = parent;
		parent = (hole - 1) / 2;
	}

	*(begin + hole) = gtl::move(tmp);
}

template <typename Iterator>
void make_heap(Iterator begin, Iterator end)
{
	int len = end - begin;
	for (int i = len / 2; i >= 0; --i)
	{
		__percolateDown(begin, len, i);
	}
}

template <typename Iterator>
void push_heap(Iterator begin, Iterator end)
{
	int len = end - begin;
	__percolateUp(begin, len - 1);
}

template <typename Iterator>
void pop_heap(Iterator begin, Iterator end)
{
	gtl::swap(*begin, *(end - 1));
	__percolateDown(begin, end - begin - 1, 0);
}

template <typename Iterator>
void sort_heap(Iterator begin, Iterator end)
{
	while (end - begin > 1)
	{
		pop_heap(begin, end--);
	}
}

NS_END(gtl);

#endif