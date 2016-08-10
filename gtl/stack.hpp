#ifdef _MSC_VER
#pragma once
#endif // _MSC_VER

#ifndef _STACK_HPP_
#define _STACK_HPP_

#include <macros.hpp>
#include <vector.hpp>

NS_BEGIN(gtl)

template<class T>
class stack
{
public:

	stack(int capacity = 0)
		: _container(capacity)
	{
	}

	~stack()
	{
	}

	stack(const stack& other)
		: _container(other._container)
	{
	}

	stack(stack&& other)
		: _container(gtl::move(other._container))
	{
	}

	stack& operator =(const stack& other)
	{
		if (this != &other)
		{
			_container = other._container;
		}
		return *this;
	}

	stack& operator =(const stack&& other)
	{
		if (this != &other)
		{
			_container = gtl::move(other._container);
		}
		return *this;
	}


	void push(const T &elem) {
		T copy = elem;
		push(gtl::move(copy));
	}

	void push(T &&elem) {
		_container.push_back(elem);
	}

	T& top() {
		return _container[_container.size() - 1];
	}

	const T& top() const {
		return top();
	}

	void pop() {
		_container.resize(_container.size() - 1);
	}

	bool empty() {
		return _container.empty();
	}

private:
	vector<T> _container;
};

NS_END(gtl)

#endif // ! _STACK_HPP_