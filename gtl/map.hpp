#ifdef _MSC_VER
#pragma once
#endif

#ifndef _MAP_HPP_
#define	_MAP_HPP_

#include <macros.hpp>
#include <avltree.hpp>
#include <rbtree.hpp>
#include <utility.hpp>

NS_BEGIN(gtl);

template <class K, class V, class BaseType = avltree<gtl::pair<K, V>>>
//template <class K, class V, class BaseType = rbtree<gtl::pair<K, V>>>
class map : public BaseType
{
public:
	typedef gtl::pair<K, V> value_type;

public:

	map() : BaseType(value_less)
	{

	}
	
	V& operator [] (const K &key)
	{
		return insert(value_type{ key, V() })->second;
	}

public:

	static bool value_less(const value_type &a, const value_type &b)
	{
		return a.first < b.first;
	}

};

NS_END(gtl);

#endif