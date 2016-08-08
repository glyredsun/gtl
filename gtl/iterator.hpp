#ifdef _MSC_VER
#pragma once
#endif // _MSC_VER

#ifndef _ITERATOR_HPP_
#define _ITERATOR_HPP_

#include <macros.hpp>
#include <iterator_base.hpp>

NS_BEGIN(gtl)

template <class Iterator>
class reverse_iterator
{
public:
	typedef Iterator iterator_type;
	typedef reverse_iterator<iterator_type> _SelfType;

	typedef iterator_traits<iterator_type>::value_type value_type;
	typedef iterator_traits<iterator_type>::defference_type defference_type;
	typedef iterator_traits<iterator_type>::pointer pointer;
	typedef iterator_traits<iterator_type>::reference reference;
	typedef iterator_traits<iterator_type>::iterator_category iterator_category;

	explicit reverse_iterator(const iterator_type &itr) : _current(itr) { }
	explicit reverse_iterator(const _SelfType &other) : _current(other._current) {}

	iterator_type base() const
	{
		return _current;
	}

	reference operator* ()
	{
		iterator_type tmp = _current;
		return *--tmp;
	}

	pointer operator->()
	{
		return &(*this);
	}

	_SelfType& operator++()
	{
		--_current;
		return *this;
	}

	_SelfType operator++(int)
	{
		_SelfType tmp = *this;
		--_current;
		return tmp;
	}

	_SelfType& operator--()
	{
		++_current;
		return *this;
	}

	_SelfType operator--(int)
	{
		_SelfType tmp = *this;
		++_current;
		return tmp;
	}

	_SelfType operator+(defference_type n) const
	{
		return _SelfType(_current - n);
	}

	_SelfType operator+=(defference_type n)
	{
		_current -= n;
		return *this;
	}

	_SelfType operator-(defference_type n) const
	{
		return _SelfType(_current + n);
	}

	_SelfType operator-=(defference_type n)
	{
		_current += n;
		return *this;
	}

	reference operator[](defference_type n) const
	{
		return *(*this + n);
	}

private:
	iterator_type _current;
};

NS_END(gtl)

#endif // !_ITERATOR_HPP_
