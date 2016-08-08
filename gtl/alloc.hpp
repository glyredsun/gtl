#ifdef _MSC_VER
#pragma once
#endif // _MSC_VER

#ifndef _ALLOC_HPP_
#define _ALLOC_HPP_

template <class Type>
class allocator
{
public:
	typedef Type				value_type;
	typedef size_t				size_type;
	typedef ptrdiff_t			difference_type;
	typedef value_type*			pointer;
	typedef value_type&			reference;
	typedef const value_type*	const_pointer;
	typedef const value_type&	const_reference;

	value_type * allocate(size_type n)
	{

	}
	
};

#endif // !_ALLOC_HPP_
