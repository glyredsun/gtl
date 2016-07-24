#ifdef _MSC_VER
#pragma once
#endif

#ifndef ALGORITHMS_HPP_
#define ALGORITHMS_HPP_

#include <macros.hpp>

#include <algorithm>
#include <cstdlib>

NS_BEGIN(gtl);

#define _MOVE_FUNC_FOR_PRIMARY_TYPE(type)								\
template <>																\
inline void move<type *>(type *inBegin, type *inEnd, type *outBegin)	\
{																		\
	::_memccpy(outBegin, inBegin, sizeof(type), inEnd - inBegin);		\
}

template <typename Iterator>
inline void move(Iterator inBegin, Iterator inEnd, Iterator outBegin)
{
	while (inBegin < inEnd)
		outBegin++ = inBegin++;
}

_MOVE_FUNC_FOR_PRIMARY_TYPE(char);
_MOVE_FUNC_FOR_PRIMARY_TYPE(int);
_MOVE_FUNC_FOR_PRIMARY_TYPE(float);
_MOVE_FUNC_FOR_PRIMARY_TYPE(double);
_MOVE_FUNC_FOR_PRIMARY_TYPE(short);

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
	return search(begin, end, target, gtl::less<Iterator::value_type>());
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
	T tmp = std::move(left);
	left = std::move(right);
	right = std::move(tmp);
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
inline int distance(const Iterator first, const Iterator last)
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

NS_END(gtl);

#endif