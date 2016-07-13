#ifdef _MSC_VER
#pragma once
#endif

#ifndef ALGORITHMS_HPP_
#define ALGORITHMS_HPP_

#include <macros.hpp>


#include <algorithm>

NS_BEGIN(gtl);

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

NS_END(gtl);

#endif