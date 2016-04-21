#ifdef _MSC_VER
#pragma once
#endif

#ifndef _MAP_HPP_
#define	_MAP_HPP_

#include <macros.hpp>
#include <avltree.hpp>
#include <utility.hpp>

NS_BEGIN(gtl);

template <typename K, typename V>
class map : public avltree<gtl::pair<K, V>>
{
public:
	typedef gtl::pair<K, V> value_type;

public:

	map()
		: avltree<value_type>(value_less)
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