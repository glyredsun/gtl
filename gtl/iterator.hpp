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

	typedef typename iterator_traits<iterator_type>::value_type value_type;
	typedef typename iterator_traits<iterator_type>::difference_type difference_type;
	typedef typename iterator_traits<iterator_type>::pointer pointer;
	typedef typename iterator_traits<iterator_type>::reference reference;
	typedef typename iterator_traits<iterator_type>::iterator_category iterator_category;

	reverse_iterator() {}
	explicit reverse_iterator(const iterator_type &itr) : _current(itr) { }
	reverse_iterator(const _SelfType &other) : _current(other._current) {}

	_SelfType operator= (const _SelfType& other)
	{
		if (&other != this)
		{
			_current = other->_current;
		}
		return *this;
	}

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
		return &(this->operator*());
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

	_SelfType operator+(difference_type n) const
	{
		return _SelfType(_current - n);
	}

	_SelfType operator+=(difference_type n)
	{
		_current -= n;
		return *this;
	}

	_SelfType operator-(difference_type n) const
	{
		return _SelfType(_current + n);
	}

	_SelfType operator-=(difference_type n)
	{
		_current += n;
		return *this;
	}

	reference operator[](difference_type n) const
	{
		return *(*this + n);
	}

private:
	iterator_type _current;
};

template <class Iterator>
bool operator==(const reverse_iterator<Iterator>& left, const reverse_iterator<Iterator>& right)
{
	return left.base() == right.base();
}

template <class Iterator>
bool operator!=(const reverse_iterator<Iterator>& left, const reverse_iterator<Iterator>& right)
{
	return !(left == right);
}

template <class Iterator>
bool operator<(const reverse_iterator<Iterator>& left, const reverse_iterator<Iterator>& right)
{
	return left.base() > right.base();
}

template <class Iterator>
bool operator>(const reverse_iterator<Iterator>& left, const reverse_iterator<Iterator>& right)
{
	return left.base() < right.base();
}

template <class Iterator>
bool operator<=(const reverse_iterator<Iterator>& left, const reverse_iterator<Iterator>& right)
{
	return !(left > right);
}

template <class Iterator>
bool operator>=(const reverse_iterator<Iterator>& left, const reverse_iterator<Iterator>& right)
{
	return !(left < right);
}

template <class Iterator>
class const_iterator
{
public:
	typedef Iterator iterator_type;
	typedef const_iterator<iterator_type> _SelfType;

	typedef typename iterator_traits<iterator_type>::value_type value_type;
	typedef typename iterator_traits<iterator_type>::difference_type difference_type;
	typedef const value_type& reference;
	typedef const value_type* pointer;
	typedef typename iterator_traits<iterator_type>::iterator_category iterator_category;

	const_iterator() {}
	explicit const_iterator(const iterator_type &itr) : _current(itr) { }
	const_iterator(const _SelfType &other) : _current(other._current) {}

	_SelfType operator= (const _SelfType& other)
	{
		if (&other != this)
		{
			_current = other->_current;
		}
		return *this;
	}

	iterator_type base() const
	{
		return _current;
	}

	reference operator* () const
	{
		return *_current;
	}

	pointer operator->() const
	{
		return &(this->operator*());
	}

	_SelfType& operator++()
	{
		++_current;
		return *this;
	}

	_SelfType operator++(int)
	{
		_SelfType tmp = *this;
		++_current;
		return tmp;
	}

	_SelfType& operator--()
	{
		--_current;
		return *this;
	}

	_SelfType operator--(int)
	{
		_SelfType tmp = *this;
		--_current;
		return tmp;
	}

	_SelfType operator+(difference_type n) const
	{
		return _SelfType(_current + n);
	}

	_SelfType operator+=(difference_type n)
	{
		_current += n;
		return *this;
	}

	_SelfType operator-(difference_type n) const
	{
		return _SelfType(_current - n);
	}

	_SelfType operator-=(difference_type n)
	{
		_current -= n;
		return *this;
	}

	reference operator[](difference_type n) const
	{
		return *(*this + n);
	}

private:
	iterator_type _current;
};

template <class Iterator>
bool operator==(const const_iterator<Iterator>& left, const const_iterator<Iterator>& right)
{
	return left.base() == right.base();
}

template <class Iterator>
bool operator!=(const const_iterator<Iterator>& left, const const_iterator<Iterator>& right)
{
	return !(left == right);
}

template <class Iterator>
bool operator<(const const_iterator<Iterator>& left, const const_iterator<Iterator>& right)
{
	return left.base() < right.base();
}

template <class Iterator>
bool operator>(const const_iterator<Iterator>& left, const const_iterator<Iterator>& right)
{
	return left.base() > right.base();
}

template <class Iterator>
bool operator<=(const const_iterator<Iterator>& left, const const_iterator<Iterator>& right)
{
	return !(left > right);
}

template <class Iterator>
bool operator>=(const const_iterator<Iterator>& left, const const_iterator<Iterator>& right)
{
	return !(left < right);
}

NS_END(gtl)

#endif // !_ITERATOR_HPP_
