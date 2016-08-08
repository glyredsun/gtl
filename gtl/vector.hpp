#ifdef _MSC_VER
#pragma once
#endif // _MSC_VER

#ifndef _VECTOR_HPP_
#define _VECTOR_HPP_

#include <macros.hpp>
#include <memory.hpp>
#include <iterator_base.hpp>
#include <algorithm.hpp>

NS_BEGIN(gtl)

template<typename ElemType>
class vector
{
public:
	
	typedef ElemType value_type;
	typedef value_type* iterator;
	typedef const value_type* const_iterator;
	typedef reverse_iterator<iterator> reverse_iterator;
	typedef reverse_iterator<const_iterator> const_reverse_iterator;
	typedef vector<value_type> SelfType;

	vector(size_t initSize = 0)
	{
		reserve(initSize + SPARE_SIZE);
		_size = initSize;
	}

	vector(std::initializer_list<ElemType> args)
		: vector(args.size())
	{
		gtl::move(args.begin(), args.end(), _datas, _datas + _size);
	}

	template <typename Iterator>
	vector(Iterator inBegin, Iterator inEnd)
		: vector(inEnd - inBegin)
	{
		gtl::move(inBegin, inEnd, _datas);
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

	ElemType& operator[](size_t idx) {
		return _datas[idx];
	}

	const ElemType& operator[](size_t idx) const {
		return _datas[idx];
	}

	bool empty() {
		return _size == 0;
	}

	size_t size() {
		return _size;
	}

	size_t capacity() {
		return _capacity;
	}

	void resize(size_t newSize) {
		if (newSize > _capacity) {
			reserve(newSize * 2);
		}
		_size = newSize;
	}

	void reserve(size_t newCapacity) {
		if (newCapacity <= _size) {
			return;
		}

		ElemType *newDatas = new ElemType[newCapacity];

		for (size_t i = 0; i < _size; i++)
		{
			newDatas[i] = gtl::move(_datas[i]);
		}

		_capacity = newCapacity;

		if (_datas)
			delete[] _datas;

		_datas = newDatas;
	}

	void push_back(ElemType&& data) {
		resize(_size + 1);
		_datas[_size - 1] = data;
	}

	void push_back(const ElemType& data) {
		ElemType copy = data;
		push_back(gtl::move(copy));
	}

	void pop_back() {
		--_size;
	}

	void clear() {
		_size = 0;
	}

protected:

	void copyFrom(const vector &other)
	{
		if (_capacity < other._size)
		{
			freeMomery();
		}

		resize(other._size);

		for (size_t i = 0; i < _size; i++)
		{
			_datas[i] = other._datas[i];
		}
	}

	void moveFrom(vector &other)
	{
		freeMomery();
		gtl::swap(_size, other._size);
		gtl::swap(_capacity, other._capacity);
		gtl::swap(_datas, other._datas);
	}

	void freeMomery()
	{
		if (_datas) {
			delete[] _datas;
			_datas = nullptr;
			_size = 0;
			_capacity = 0;
		}
	}

	void shiftElems(size_t begin, int shift)
	{
		ElemType *src = _datas;
		size_t newSize = _size + shift;

		if (shift < 0) {

			for (size_t i = begin; i < _size; ++i)
			{
				_datas[i + shift] = gtl::move(src[i]);
			}
		}
		else if (shift > 0) {

			if (newSize > _capacity) {
				_datas = new ElemType[newSize * 2];
				for (size_t i = 0; i < begin; i++)
				{
					_datas[i] = gtl::move(src[i]);
				}
			}

			for (size_t i = _size - 1; i >= begin; --i)
			{
				_datas[i + shift] = gtl::move(src[i]);
			}

			if (src != _datas) {
				delete[] src;
			}
		}
		_size = newSize;
	}

public:

	iterator begin()
	{
		return iterator(_datas);
	}

	iterator end()
	{
		return iterator(_datas + _size);
	}

	const_iterator begin() const
	{
		return const_iterator(_datas);
	}

	const_iterator end() const
	{
		return const_iterator(_datas + _size);
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
		shiftElems(where.idx + 1, -1);
	}

	void erase(const iterator &first, const iterator &last)
	{
		if (first == begin() && last == end()) {
			clear();
			return;
		}

		int shift = last - first;
		shiftElems(last.idx, -shift);
	}

	void insert(const iterator &where, ElemType &&data)
	{
		shiftElems(where.idx, 1);
		_datas[where.idx] = data;
	}

	void insert(const iterator &where, const ElemType &data)
	{
		insert(where, gtl::move(ElemType(data)));
	}

	void insert(iterator &where, size_t count, const ElemType &data)
	{
		shiftElems(where.idx, count);
		while (count-- > 0)
		{
			insert(where++, gtl::move(ElemType(data)));
		}
	}

	void insert(iterator where, std::initializer_list<ElemType> list)
	{

		for (std::initializer_list<ElemType>::iterator itr = list.begin(); itr < list.end(); ++itr)
		{
			insert(where++, gtl::move(*itr));
		}
	}

private:
	static const size_t SPARE_SIZE = 16;
	size_t _capacity{0};
	size_t _size{0};
	ElemType *_datas{nullptr};
};

NS_END(gtl)

#endif // !_VECTOR_HPP_