#ifdef _MSC_VER
#pragma once
#endif // _MSC_VER

#ifndef _ITERATOR_BASE_HPP_
#define _ITERATOR_BASE_HPP_

#include <macros.hpp>

#include <cstddef>

NS_BEGIN(gtl)

struct input_iterator_tag {};
struct output_iterator_tag {};
struct forward_iterator_tag : public input_iterator_tag {};
struct bidirectional_iterator_tag : public forward_iterator_tag {};
struct random_access_iterator_tag : public bidirectional_iterator_tag {};

template <class Iterator>
struct iterator_traits {
	typedef typename Iterator::value_type value_type;
	typedef typename Iterator::difference_type defference_type;
	typedef typename Iterator::pointer pointer;
	typedef typename Iterator::reference reference;
	typedef typename Iterator::iterator_category iterator_category;
};

template <class Type>
struct iterator_traits<Type *>
{
	typedef Type value_type;
	typedef ptrdiff_t defference_type;
	typedef Type* pointer;
	typedef Type& reference;
	typedef random_access_iterator_tag iterator_category;
};

template <class Type>
struct iterator_traits<const Type *>
{
	typedef Type value_type;
	typedef ptrdiff_t defference_type;
	typedef const Type* pointer;
	typedef const Type& reference;
	typedef random_access_iterator_tag iterator_category;
};



NS_END(gtl)

#endif // !_ITERATOR_BASE_HPP_
