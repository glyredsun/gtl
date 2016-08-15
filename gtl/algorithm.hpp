#ifdef _MSC_VER
#pragma once
#endif

#ifndef _ALGORITHMS_HPP_
#define _ALGORITHMS_HPP_

#include <macros.hpp>
#include <algorithm.hpp>
#include <type_traits.hpp>
#include <iterator_base.hpp>

#include <cstring>

NS_BEGIN(gtl);

template <class InIterator, class OutIterator>
inline OutIterator _move(InIterator srcBegin, InIterator srcEnd, OutIterator destBegin, __true_type)
{
	auto count = gtl::distance(srcBegin, srcEnd);
	::memmove(&(*destBegin), &(*srcBegin), count * sizeof(iterator_traits<InIterator>::value_type));
	return destBegin + count;
}

template <class InIterator, class OutIterator>
inline OutIterator _move(InIterator srcBegin, InIterator srcEnd, OutIterator destBegin, __false_type)
{
	while (srcBegin < srcEnd)
		*destBegin++ = gtl::move(*srcBegin++);
	return destBegin;
}

template <class InIterator, class OutIterator>
inline OutIterator move(InIterator srcBegin, InIterator srcEnd, OutIterator destBegin)
{
	return _move(srcBegin, srcEnd, destBegin, type_traits<iterator_traits<OutIterator>::value_type>::has_trivial_assignment_operator());
}

template <class InIterator, class OutIterator>
inline OutIterator move(InIterator srcBegin, InIterator srcEnd, OutIterator destBegin, OutIterator destEnd)
{
	auto count1 = gtl::distance(srcBegin, srcEnd);
	auto count2 = gtl::distance(destBegin, destEnd);
	return move(srcBegin, srcBegin + (count1 <= count2 ? count1 : count2), destBegin);
}

template <class InIterator, class OutIterator>
inline OutIterator _copy(InIterator srcBegin, InIterator srcEnd, OutIterator destBegin, __true_type)
{
	return _move(srcBegin, srcEnd, destBegin, __true_type());
}

template <class InIterator, class OutIterator>
inline OutIterator _copy(InIterator srcBegin, InIterator srcEnd, OutIterator destBegin, __false_type)
{
	while (srcBegin < srcEnd)
		*destBegin++ = *srcBegin++;
	return destBegin;
}

template <class InIterator, class OutIterator>
inline OutIterator copy(InIterator srcBegin, InIterator srcEnd, OutIterator destBegin)
{
	return _copy(srcBegin, srcEnd, destBegin, type_traits<iterator_traits<OutIterator>::value_type>::has_trivial_assignment_operator());
}

template <class InIterator, class OutIterator>
inline OutIterator copy(InIterator srcBegin, InIterator srcEnd, OutIterator destBegin, OutIterator destEnd)
{
	auto count1 = gtl::distance(srcBegin, srcEnd);
	auto count2 = gtl::distance(destBegin, destEnd);
	return copy(srcBegin, srcBegin + (count1 <= count2 ? count1 : count2), destBegin);
}

// binary search
template <class Iterator, class DataType, class Comparator>
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

template <class Iterator, class DataType>
inline Iterator search(Iterator begin, Iterator end, const DataType &target)
{
	return search(begin, end, target, gtl::less<typename iterator_traits<Iterator>::value_type>());
}

// get the power of two number big than num
template <class T>
inline T nextPOT(T num)
{
	for (size_t i = 1; i <= sizeof(T) * 8 / 2; i *= 2)
	{
		num = num | num >> i;
	}
	return num + 1;
}

// get the power of two number not big than num
template <class T>
inline T lastPOT(T num)
{
	return nextPOT(num) >> 1;
}

template <class T>
inline void swap(T& left, T& right)
{
	if (&left != &right)
	{
		T tmp = gtl::move(left);
		left = gtl::move(right);
		right = gtl::move(tmp);
	}
}

template <class T>
inline const T& max(const T& a, const T& b)
{
	return a > b ? a : b;
}

template <class T>
inline const T& min(const T& a, const T& b)
{
	return a < b ? a : b;
}

template <class Iterator>
typename iterator_traits<Iterator>::defference_type distance(const Iterator first, const Iterator last)
{
	return last - first;
}

template <class ArgType = void>
struct less
{
	constexpr bool operator() (const ArgType &left, const ArgType &right) const 
	{
		return left < right;
	}
};

template <class Iterator, class Comparator>
inline void __percolateDown(Iterator begin, int len, int hole, const Comparator &predicate)
{
	typename iterator_traits<Iterator>::value_type tmp = gtl::move(*(begin + hole));
	for (int child; hole * 2 + 1 <= len - 1; hole = child)
	{
		child = hole * 2 + 1;

		if (child != len - 1 && predicate(*(begin + child), *(begin + child + 1)))
			++child;

		if (predicate(tmp, *(begin + child)))
			*(begin + hole) = gtl::move(*(begin + child));
		else
			break;
	}
	*(begin + hole) = gtl::move(tmp);
}

template <class Iterator, class Comparator>
inline void __percolateUp(Iterator begin, int hole, const Comparator &predicate)
{
	typename iterator_traits<Iterator>::value_type tmp = gtl::move(*(begin + hole));
	int parent = (hole - 1) / 2;
	while (hole > 0 && predicate(*(begin + parent), tmp))
	{
		*(begin + hole) = gtl::move(*(begin + parent));
		hole = parent;
		parent = (hole - 1) / 2;
	}

	*(begin + hole) = gtl::move(tmp);
}

template <class Iterator, class Comparator>
inline void make_heap(Iterator begin, Iterator end, const Comparator &predicate)
{
	int len = end - begin;
	for (int i = len / 2; i >= 0; --i)
	{
		__percolateDown(begin, len, i, predicate);
	}
}

template <class Iterator>
inline void make_heap(Iterator begin, Iterator end)
{
	make_heap(begin, end, gtl::less<typename iterator_traits<Iterator>::reference>());
}

template <class Iterator, class Comparator>
inline void push_heap(Iterator begin, Iterator end, const Comparator &predicate)
{
	int len = end - begin;
	__percolateUp(begin, len - 1, predicate);
}

template <class Iterator>
inline void push_heap(Iterator begin, Iterator end)
{
	push_heap(begin, end, gtl::less<typename iterator_traits<Iterator>::reference>());
}

template <class Iterator, class Comparator>
inline void pop_heap(Iterator begin, Iterator end, const Comparator &predicate)
{
	gtl::swap(*begin, *(end - 1));
	__percolateDown(begin, end - begin - 1, 0, predicate);
}

template <class Iterator>
inline void pop_heap(Iterator begin, Iterator end)
{
	pop_heap(begin, end, gtl::less<typename iterator_traits<Iterator>::reference>());
}

template <class Iterator, class Comparator>
inline void sort_heap(Iterator begin, Iterator end, const Comparator &predicate)
{
	while (end - begin > 1)
	{
		pop_heap(begin, end--, predicate);
	}
}

template <class Iterator>
inline void sort_heap(Iterator begin, Iterator end)
{
	typedef iterator_traits<Iterator>::reference reference;
	sort_heap(begin, end, gtl::less<typename iterator_traits<Iterator>::reference>());
}

NS_END(gtl);

#endif // !_ALGORITHMS_HPP_