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

	vector(size_type initSize, const value_type &data) : vector(initSize)
	{
		for (iterator itr = begin(); itr != end(); ++itr)
		{
			*itr = data;
		}
	}

	vector(std::initializer_list<value_type> args)
		: vector(args.size())
	{
		gtl::move(args.begin(), args.end(), _start);
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
		moveFrom(gtl::move(other));
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

	bool empty() const {
		return _start == _finish;
	}

	size_type size() const {
		return _finish - _start;
	}

	size_type capacity() const {
		return _end_of_storage - _start;
	}

	void resize(size_type newSize) {
		if (newSize > capacity()) {
			reserve(newSize * 2);
		}
		_finish = _start + newSize;
	}

	void reserve(size_type newCapacity) {
		
		if (newCapacity <= size()) {
			return;
		}

		iterator newStart = _alloc.allocate(newCapacity);
		iterator newFinish = gtl::uninitialized_copy(_start, _finish, newStart);
		
		freeMomery();

		_start = newStart;
		_finish = newFinish;
		_end_of_storage = _start + newCapacity;
	}

	void push_back(rvalue_reference data) {
		if (_finish == _end_of_storage)
			reserve(2 * size());

		gtl::construct(&*_finish++, gtl::move(data));
	}

	void push_back(const_reference data) {
		push_back(gtl::move(value_type(data)));
	}

	void pop_back() {
		gtl::destroy(&*--_finish);
	}

	void clear() {
		erase(begin(), end());
	}

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

	iterator erase(const iterator &where)
	{
		return shiftElems(where + 1, -1);
	}

	iterator erase(const iterator &first, const iterator &last)
	{
		int shift = first - last;
		return shiftElems(last, shift);
	}

	iterator insert(iterator where, rvalue_reference data)
	{
		where = shiftElems(where, 1);
		*where++ = gtl::move(data);
		return where;
	}

	iterator insert(iterator where, const_reference data)
	{
		return insert(where, gtl::move(value_type(data)));
	}

	iterator insert(iterator where, size_type count, const_reference data)
	{
		where = shiftElems(where, count);
		while (count-- > 0)
		{
			*where++ = data;
		}
		return where;
	}

	iterator insert(iterator where, iterator first, iterator last)
	{
		where = shiftElems(where, last - first);
		return gtl::copy(first, last, where);
	}

	const_iterator insert(iterator where, const_iterator first, const_iterator last)
	{
		where = shiftElems(where, last - first);
		return gtl::copy(first, last, where);
	}

	iterator insert(iterator where, std::initializer_list<value_type> list)
	{
		where = shiftElems(where, list.end() - list.begin());
		for (std::initializer_list<value_type>::iterator itr = list.begin(); itr < list.end(); ++itr)
		{
			*where++ = *itr;
		}
		return where;
	}

protected:

	void copyFrom(const vector &other)
	{
		if (capacity() < other.capacity())
		{
			freeMomery();
		}

		resize(other.size());

		gtl::copy(other._start, other._finish, _start);
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
			gtl::destroy(_start, _finish);
			_alloc.deallocate(_start);
			_start = _finish = _end_of_storage = nullptr;
		}
	}

	iterator shiftElems(iterator pos, int shift)
	{
		
		size_type newSize = size() + shift;
		size_type posIdx = pos - begin();

		if (shift < 0)
		{
			gtl::move(pos, _finish, pos + shift);
			gtl::destroy(_finish + shift, _finish);
		}
		else if (shift > 0)
		{
			if (newSize > capacity())
			{
				size_type newCapacity = newSize * 2;
				iterator newStart = _alloc.allocate(newCapacity, nullptr);
				gtl::uninitialized_copy(_start, pos, newStart);
				gtl::uninitialized_copy(pos, _finish, newStart + posIdx + shift);

				for (size_type i = posIdx; i < posIdx + shift; ++i)
					gtl::construct(&*(newStart + i));

				freeMomery();
				_start = newStart;
				_end_of_storage = _start + newCapacity;
			}
			else
			{
				iterator p = _finish - 1;
				iterator q = _finish + shift - 1;

				while (q >= _finish)
					gtl::construct(&*q--, *p--);

				while (p >= pos)
					*q-- = *p--;
			}
		}
		_finish = begin() + newSize;
		return begin() + posIdx;
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