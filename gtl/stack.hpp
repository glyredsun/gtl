#ifdef _MSC_VER
#pragma once
#endif // _MSC_VER

#ifndef _STACK_HPP_
#define _STACK_HPP_

#include <macros.hpp>
#include <vector.hpp>

NS_BEGIN(gtl)

template<typename T>
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

	void push(const T &elem) {
		T copy = elem;
		push(std::move(copy));
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