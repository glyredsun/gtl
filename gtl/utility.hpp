#ifdef _MSC_VER
#pragma once
#endif
#ifndef _UTILITY_HPP_
#define _UTILITY_HPP_

#include <macros.hpp>

NS_BEGIN(gtl)

template <class T, class U>
struct pair
{
	pair() : first(), second() {}
	pair(const T& f, const U& s) : first(f), second(s) {}

	T first;
	U second;
};

NS_END(gtl)

#endif