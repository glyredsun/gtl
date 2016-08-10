#ifdef _MSC_VER
#pragma once
#endif // _MSC_VER

#ifndef _VECTOR_HPP_
#define _VECTOR_HPP_

#include <macros.hpp>
#include <memory.hpp>
#include <iterator_base.hpp>
#include <iterator.hpp>
#include <algorithm.hpp>
#include <alloc.hpp>

#include <initializer_list>

NS_BEGIN(gtl)

template<class ElemType, class Allocator = allocator<ElemType>>
class vector
{
public:
	
	typedef Allocator allocator_type;
	typedef size_t size_type;
	typedef ElemType value_type;
	typedef value_type* pointer;
	typedef const value_type* const_pointer;
	typedef value_type& reference;
	typedef const value_type& const_reference;
	typedef value_type&& rvalue_reference;
	typedef pointer iterator;
	typedef const_pointer const_iterator;
	typedef reverse_iterator<const_iterator> const_reverse_iterator;
	typedef reverse_iterator<iterator> reverse_iterator;
	typedef vector<value_type> _SelfType;

	vector(size_type initSize = 0)
	{
		reserve(initSize + SPARE_SIZE);
		_finish = _start + initSize;
	}

	vector(std::initializer_list<value_type> args)
		: vector(args.size())
	{
		gtl::move(args.begin(), args.end(), _datas, _datas + _size);
	}

	template <typename Iterator>
	vector(Iterator inBegin, Iterator inEnd)
		: vector(inEnd - inBegin)
	{
		gtl::move(inBegin, inEnd, _start);
	}

	~vector()
	{
		freeMomery();
	}

	vector(const vector& other)
	{
		copyFrom(other);
	}

	vector(vector&& other)
	{
		moveFrom(other);
	}

	vector& operator=(const vector& other)
	{
		if (this != &other) {
			copyFrom(other);
		}
		return *this;
	}

	vector& operator=(vector&& other)
	{
		if (this != &other) {
			moveFrom(other);
		}
		return *this;
	}

	reference operator[](size_type idx) {
		return _start[idx];
	}

	const_reference operator[](size_type idx) const {
		return _start[idx];
	}

	bool empty() {
		return _start == _finish;
	}

	size_type size() {
		return _finish - _start;
	}

	size_type capacity() {
		return _end_of_storage - _start;
	}

	void resize(size_type newSize) {
		if (newSize > _capacity) {
			reserve(newSize * 2);
		}
		_finish = _start + newSize;
	}

	void reserve(size_type newCapacity) {
		if (newCapacity <= _finish - _start) {
			return;
		}

		value_type *newStart = new value_type[newCapacity];

		std::move(_start, _finish, newStart);

		if (_start)
			delete[] _start;

		_start = newStart;
	}

	void push_back(rvalue_reference data) {
		resize(_size + 1);
		_finish++ = std::move(data);
	}

	void push_back(const_reference data) {
		resize(_size + 1);
		_finish++ = data;
	}

	void pop_back() {
		--_finish;
	}

	void clear() {
		_finish = _start;
	}

protected:

	void copyFrom(const vector &other)
	{
		if (capacity() < other.capacity())
		{
			freeMomery();
		}

		resize(other.size());

		gtl::move(other._start, other._finish, _start);
	}

	void moveFrom(vector&& other)
	{
		freeMomery();
		gtl::swap(_start, other._start);
		gtl::swap(_finish, other._finish);
		gtl::swap(_end_of_storage, other._end_of_storage);
	}

	void freeMomery()
	{
		if (_start) {
			delete[] _start;
			_start = _finish = _end_of_storage = nullptr;
		}
	}

	iterator shiftElems(iterator pos, int shift)
	{
		size_t first = pos - begin();
		value_type *src = _start;
		size_type newSize = size() + shift;

		if (shift < 0) {
			gtl::move(pos, _finish, pos + shift);
		}
		else if (shift > 0) {

			if (newSize > capacity()) {
				size_type newCapacity = newSize * 2;
				_start = new value_type[newCapacity];
				_end_of_storage = _start + newCapacity;
				gtl::move(src, pos, _start);
			}
			else if {
				for (size_t i = _size - 1; i >= first; --i)
				{
					_start[i + shift] = gtl::move(src[i]);
				}
			}
			
			if (src != _start) {
				delete[] src;
			}
		}
		_finish = _start + newSize;
		return begin() + first;
	}

public:

	iterator begin()
	{
		return _start;
	}

	iterator end()
	{
		return _finish;
	}

	const_iterator begin() const
	{
		return _start;
	}

	const_iterator end() const
	{
		return _finish;
	}

	reverse_iterator rbegin()
	{
		return reverse_iterator(end());
	}

	reverse_iterator rend()
	{
		return reverse_iterator(begin());
	}

	void erase(const iterator &where)
	{
		shiftElems(where + 1, -1);
	}

	void erase(const iterator &first, const iterator &last)
	{
		if (first == begin() && last == end()) {
			clear();
			return;
		}

		int shift = last - first;
		shiftElems(last, -shift);
	}

	iterator insert(iterator where, rvalue_reference data)
	{
		shiftElems(where, 1);
		*where++ = gtl::move(data);
		return where;
	}

	iterator insert(iterator where, const_reference data)
	{
		return insert(where, gtl::move(value_type(data)));
	}

	iterator insert(iterator where, size_type count, const_reference data)
	{
		shiftElems(where, count);
		while (count-- > 0)
		{
			*where++ = data;
		}
		return where;
	}

	iterator insert(iterator where, std::initializer_list<value_type> list)
	{
		shiftElems(where, list.end() - list.begin());
		for (std::initializer_list<value_type>::iterator itr = list.begin(); itr < list.end(); ++itr)
		{
			*where++ = *itr;
		}
		return where;
	}

private:
	allocator_type _alloc;
	static const size_t SPARE_SIZE = 16;
	iterator _start{ nullptr };
	iterator _finish{ nullptr };
	iterator _end_of_storage{ nullptr };
};

NS_END(gtl)

#endif // !_VECTOR_HPP_