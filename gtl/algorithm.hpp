#ifdef _MSC_VER
#pragma once
#endif
#ifndef _ALGORITHM_HPP_
#define _ALGORITHM_HPP_

template<typename T>
void swap(T& a, T& b)
{
	T tmp = a;
	a = b;
	b = tmp;
}

template<typename T>
decltype(auto) move(T param)
{
	using ReturnType = std::remove_reference<T>::type&&;
	return static_cast<ReturnType>(param);
}

#endif // !_ALGORITHM_HPP_
