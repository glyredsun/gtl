#ifdef _MSC_VER
#pragma once
#endif

#ifndef _QUEUE_HPP_
#define _QUEUE_HPP_

#include <macros.hpp>

#include <algorithm>

NS_BEGIN(gtl)

template <typename ElemType>
class queue
{
public:

	queue(size_t capacity = 16)
		: _front(0), _back(0), _capacity(capacity), _elems(nullptr)
	{
		if (_capacity != 0) {
			_elems = new ElemType[_capacity];
		}
	}

	~queue()
	{
		if (_elems)
			delete[] _elems;
	}

	queue(const queue &other)
		: queue(other._capacity)
	{
		_front = other._front;
		_back = other._back;

		if (_front < _back) {
			for (size_t i = _front; i < _back; i++)
			{
				_elems[i] = other._elems[i];
			}
		}
		else if (_front > _back) {
			for (size_t i = 0; i < _back; i++)
			{

				_elems[i] = other._elems[i];
			}
			for (size_t i = _front; i < _capacity; i++)
			{
				_elems[i] = other._elems[i];
			}
		}
	}

	queue(queue&& other)
		: queue(0)
	{
		std::swap(_front, other._front);
		std::swap(_back, other._back);
		std::swap(_capacity, other._capacity);
		std::swap(_elems, other._elems);
	}

	bool empty() {
		return _front == _back;
	}

	bool full() {
		return (_back + 1) % _capacity == _front;
	}

	void push(const ElemType &elem) {
		if (full()) {
			reserve(_capacity * 2);
		}
		_elems[_back] = elem;
		_back = (_back + 1) % _capacity;
	}

	void pop() {
		_front = (_front + 1) % _capacity;
	}

	ElemType& front() {
		return _elems[_front];
	}

protected:

	void reserve(size_t newCapacity) {
		ElemType *newElems = new ElemType[newCapacity];
		size_t idx = 0;
		if (_front < _back) {
			for (size_t i = _front; i < _back && idx < newCapacity - 1; i++)
			{
				newElems[idx++] = _elems[i];
			}
		}
		else if (_front > _back) {
			for (size_t i = 0; i < _back && idx < newCapacity - 1; i++)
			{
				newElems[idx++] = _elems[i];
			}
			for (size_t i = _front; i < _capacity && idx < newCapacity - 1; i++)
			{
				newElems[idx++] = _elems[i];
			}
		}

		if (_elems)
			delete[] _elems;

		_front = 0;
		_back = idx;
		_capacity = newCapacity;
		_elems = newElems;
	}

private:
	ElemType *_elems;
	size_t _front;
	size_t _back;
	size_t _capacity;
};

NS_END(gtl)

#endif