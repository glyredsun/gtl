#ifdef _MSC_VER
#pragma once
#endif

#ifndef _MAP_HPP_
#define	_MAP_HPP_

#include <macros.hpp>
#include <avltree.hpp>

NS_BEGIN(gtl);

template <typename K, typename V>
class map
{
public:
	struct pair
	{
		K key;
		V value;
		bool operator < (const pair &other) const
		{
			return key < other.key;
		}
	};

	V& operator [] (const K &key)
	{

	}

protected:
	avltree<pair> _tree;
};

NS_END(gtl);

#endif