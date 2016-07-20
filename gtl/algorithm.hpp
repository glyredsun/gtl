#ifdef _MSC_VER
#pragma once
#endif

#ifndef ALGORITHMS_HPP_
#define ALGORITHMS_HPP_

#include <macros.hpp>


#include <algorithm>

NS_BEGIN(gtl);

template <typename T>
T nextPOT(T num)
{
	for (size_t i = 1; i <= sizeof(T) * 8 / 2; i *= 2)
	{
		num = num | num >> i;
	}
	return num + 1;
}

template <typename T>
T lastPOT(T num)
{
	return nextPOT(num) >> 1;
}

template <typename T>
void swap(T& left, T& right)
{
	T tmp = std::move(left);
	left = std::move(right);
	right = std::move(tmp);
}

template <typename T>
const T& max(const T& a, const T& b)
{
	return a > b ? a : b;
}

template <typename T>
const T& min(const T& a, const T& b)
{
	return a < b ? a : b;
}

template <typename Iterator>
int distance(const Iterator first, const Iterator last)
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