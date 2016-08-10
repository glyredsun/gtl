#ifdef _MSC_VER
#pragma once
#endif
#ifndef _TYPE_TRAITS_HPP_
#define _TYPE_TRAITS_HPP_

#include "macros.hpp"

NS_BEGIN(gtl)

struct __true_type {};
struct __false_type {};



template <class Type>
struct remove_reference
{
	using type = Type;
};

template <class Type>
struct remove_reference<Type&>
{
	using type = Type;
};

template <class Type>
struct remove_reference<Type&&>
{
	using type = Type;
};

template <class Type>
constexpr inline typename remove_reference<Type>::type&& move(Type&& value)
{
	return static_cast<typename remove_reference<Type>::type&&>(value);
}

template <class Type>
struct type_traits
{
	typedef __false_type has_trivial_default_constructor;
	typedef __false_type has_trivial_copy_constructor;
	typedef __false_type has_trivial_assignment_operator;
	typedef __false_type has_trivial_destructor;
};

#define __TYPE_TRAITS_SIMPLE_DECLEAR(value_type, type)	\
template <>												\
struct type_traits<value_type>							\
{														\
	typedef type has_trivial_default_constructor;		\
	typedef type has_trivial_copy_constructor;			\
	typedef type has_trivial_assignment_operator;		\
	typedef type has_trivial_destructor;				\
};

//__TYPE_TRAITS_SIMPLE_DECLEAR(bool, __true_type)
//__TYPE_TRAITS_SIMPLE_DECLEAR(char, __true_type)
//__TYPE_TRAITS_SIMPLE_DECLEAR(signed char, __true_type)
//__TYPE_TRAITS_SIMPLE_DECLEAR(unsigned char, __true_type)
//__TYPE_TRAITS_SIMPLE_DECLEAR(wchar_t, __true_type)
//__TYPE_TRAITS_SIMPLE_DECLEAR(short, __true_type)
//__TYPE_TRAITS_SIMPLE_DECLEAR(unsigned short, __true_type)
//__TYPE_TRAITS_SIMPLE_DECLEAR(int, __true_type)
//__TYPE_TRAITS_SIMPLE_DECLEAR(unsigned int, __true_type)
//__TYPE_TRAITS_SIMPLE_DECLEAR(long, __true_type)
//__TYPE_TRAITS_SIMPLE_DECLEAR(unsigned long, __true_type)
//__TYPE_TRAITS_SIMPLE_DECLEAR(long long, __true_type)

DECLEAR_FOR_EVERY_PRIMARYTYPE(__TYPE_TRAITS_SIMPLE_DECLEAR, __true_type);

NS_END(gtl)

#endif // ! _TYPE_TRAITS_HPP_