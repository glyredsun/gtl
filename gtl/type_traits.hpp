#ifdef _MSC_VER
#pragma once
#endif
#ifndef _TYPE_TRAITS_HPP_
#define _TYPE_TRAITS_HPP_

#include "macros.hpp"

NS_BEGIN(gtl)

template <typename Type>
struct remove_reference
{
	using type = Type;
};

template <typename Type>
struct remove_reference<Type&>
{
	using type = Type;
};

template <typename Type>
struct remove_reference<Type&&>
{
	using type = Type;
};

template <typename Type>
constexpr inline typename remove_reference<Type>::type&& move(Type&& value)
{
	return static_cast<typename remove_reference<Type>::type&&>(value);
}

NS_END(gtl)

#endif // ! _TYPE_TRAITS_HPP_