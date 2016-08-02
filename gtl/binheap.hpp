#ifdef _MSC_VER
#pragma once
#endif // _MSC_VER
#ifndef _BINHEAP_HPP_
#define _BINHEAP_HPP_

#include <macros.hpp>
#include <vector.hpp>

#include <functional>

NS_BEGIN(gtl)

template <typename ElemType>
class binheap
{
public:

	using Comparator = std::function<bool(const ElemType &, const ElemType &)>;

	binheap(int capacity = 64) : _size{ 0 }, _elems{ capacity } {}

	size_t size() { return _size; }

	bool empty() { return size() == 0; }

	void push(const ElemType & elem)
	{
		ElemType copy = elem;
		push(gtl::move(copy));
	}

	void push(const ElemType &elem, const Comparator &lessThan)
	{
		ElemType copy = elem;
		push(gtl::move(copy), lessThan);
	}

	void push(const ElemType &&elem)
	{
		push(gtl::move(elem), [](const ElemType &a, const ElemType &b) { return a < b; });
	}

	void push(const ElemType &&elem, const Comparator &lessThan)
	{
		if (_size == _elems.size() - 1) 
		{
			_elems.resize(_elems.size() * 2);
		}

		int hole = ++_size;
		_elems[0] = gtl::move(elem);

		for (; lessThan(_elems[0], _elems[hole / 2]); hole /= 2)
		{
			_elems[hole] = gtl::move(_elems[hole / 2]);
		}

		_elems[hole] = gtl::move(_elems[0]);
	}

	void pop()
	{
		_elems[1] = gtl::move(_elems[_size--]);
		percolateDown(1);
	}

	void pop(ElemType &min)
	{
		min = gtl::move(_elems[1]);
		pop();
	}

protected:

	void percolateDown(size_t hole)
	{
		ElemType tmp = gtl::move(_elems[hole]);
		for (size_t child; hole * 2 <= _size; hole = child)
		{
			child = hole * 2;
			if (child != _size && _elems[child + 1] < _elems[child])
				++child;

			if (_elems[child] < tmp)
				_elems[hole] = gtl::move(_elems[child]);
			else
				break;
		}
		_elems[hole] = tmp;
	}

private:
	size_t _size;
	vector<ElemType> _elems;
};

NS_END(gtl)

#endif // !_BINHEAP_HPP_