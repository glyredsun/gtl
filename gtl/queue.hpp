#ifdef _MSC_VER
#pragma once
#endif

#ifndef _QUEUE_HPP_
#define _QUEUE_HPP_

#include <macros.hpp>
#include <vector.hpp>
#include <algorithm.hpp>

#include <algorithm>
#include <functional>

NS_BEGIN(gtl)

template <typename ElemType>
class queue
{
public:

	queue(size_t capacity = MIN_CAPACITY)
	{
		reserve(capacity > MIN_CAPACITY ? capacity : MIN_CAPACITY);
	}

	~queue()
	{
		freeMemory();
	}

	queue(const queue &other)
	{
		copyFrom(other);
	}

	queue(queue&& other)
	{
		moveFrom(other);
	}

	queue& operator =(const queue& other)
	{
		if (this != &other) {
			copyFrom(other);
		}
		return *this;
	}

	queue& operator =(queue&& other)
	{
		if (this != other) {
			moveFrom(other);
		}
		return *this;
	}

	bool empty() const {
		return _front == _back;
	}

	bool full() const {
		return (_back + 1) % _capacity == _front;
	}

	void clear() {
		_front = _back = 0;
	}

	size_t size() const {

		if (_front == _back) {
			return 0;
		}
		else if (_front < _back) {
			return _back - _front;
		}
		else {
			return _capacity - _front + _back;
		}
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

	const ElemType& front() const {
		return _elems[_front];
	}

protected:

	void copyFrom(const queue &other) {

		clear();

		if (other.size() + 1 > _capacity) {
			freeMemory();
			reserve(other._capacity);
		}

		duplicate(other._elems, other._front, other._back, other._capacity);
	}

	void moveFrom(queue &other) {

		freeMemory();

		std::swap(_front, other._front);
		std::swap(_back, other._back);
		std::swap(_capacity, other._capacity);
		std::swap(_elems, other._elems);
	}

	void reserve(size_t newCapacity) {
		
		ElemType *oldElems = _elems;
		_elems = new ElemType[newCapacity];

		if (oldElems) {
			duplicate(oldElems, _front, _back, _capacity);
			delete[] oldElems;
		}
		
		_capacity = newCapacity;
	}

	void duplicate(ElemType *elems, size_t front, size_t back, size_t capacity)
	{
		size_t idx = 0;

		if (front < back) {
			for (size_t i = front; i < back; i++)
			{
				_elems[idx++] = elems[i];
			}
		}
		else if (front > back) {
			for (size_t i = front; i < capacity; i++)
			{
				_elems[idx++] = elems[i];
			}
			for (size_t i = 0; i < back; i++)
			{
				_elems[idx++] = elems[i];
			}
		}

		_front = 0;
		_back = idx;
	}

	void freeMemory()
	{
		if (_elems) {
			delete[] _elems;
			_elems = nullptr;
			_front = _back = _capacity = 0;
		}
	}

private:
	static const int MIN_CAPACITY = 16;

private:
	ElemType *_elems{nullptr};
	size_t _front{0};
	size_t _back{0};
	size_t _capacity{0};
};

template <typename ElemType, typename ContainerType = gtl::vector<ElemType>, typename ComparatorType = gtl::less<ContainerType::value_type>>
class priority_queue
{
public:
	using value_type = typename ContainerType::value_type;

	priority_queue() {

	}

	priority_queue(const ComparatorType &comp) : comp(comp) {

	}

	template <typename InIterator>
	priority_queue(InIterator inBegin, InIterator inEnd) 
		: c(inBegin, inEnd)
	{
		make_heap(c.begin(), c.end());
	}

	const value_type & top() const {
		return *(c.begin());
	}

	void pop() {
		pop_heap(c.begin(), c.end());
		c.pop_back();
	}

	void push(const ElemType &elem) {
		c.push_back(elem);
		push_heap(c.begin(), c.end());
	}

	void push(ElemType &&elem) {
		c.push_back(elem);
		push_heap(c.begin(), c.end());
	}

	bool empty() {
		return c.empty();
	}

private:
	ContainerType c;
	ComparatorType comp;
};

NS_END(gtl)

#endif