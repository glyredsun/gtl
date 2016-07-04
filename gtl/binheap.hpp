#ifdef _MSC_VER
#pragma once
#endif // _MSC_VER
#ifndef _BINHEAP_HPP_
#define _BINHEAP_HPP_

#include <macros.hpp>
#include <vector.hpp>

#include <functional>

NS_BEGIN(gtl)

template <typename ElemType, typename Comparator = std::function<bool (const ElemType &, const ElemType &)>>
class binheap
{
public:
	binheap(int capacity = 64) : _size{ 0 }, _elems{ capacity } {}

	size_t size() { return _size; }

	bool empty() { return size() == 0; }

	void push(const ElemType & elem)
	{
		push(elem, [](const ElemType &a, const ElemType &b) { return a < b; });
	}

	void push(const ElemType &elem, const Comparator &lessThan)
	{
		ElemType copy = elem;
		push(std::move(elem), lessThan);
	}

	void push(const ElemType &&elem)
	{
		push(std::move(elem), [](const ElemType &a, const ElemType &b) { return a < b; });
	}

	void push(const ElemType &&elem, const Comparator &lessThan)
	{
		if (_size == _elems.size() - 1) 
		{
			_elems.resize(_elems.size() * 2);
		}

		int hole = ++_size;
		
		for (; hole > 1 && lessThan(elem, _elems[hole / 2]); hole /= 2)
		{
			_elems[hole] = std::move(_elems[hole / 2]);
		}

		_elems[hole] = std::move(elem);
	}

	const vector<ElemType> & container() const
	{
		return _elems;
	}

private:
	size_t _size;
	vector<ElemType> _elems;
};

NS_END(gtl)

#endif // !_BINHEAP_HPP_