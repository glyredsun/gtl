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
void max(const T& a, const T& b)
{
	return a > b ? a : b;
}

template <typename T>
void min(const T& a, const T& b)
{
	return a < b ? a : b;
}

NS_END(gtl);

#endif