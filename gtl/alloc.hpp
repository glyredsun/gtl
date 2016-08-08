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

	value_type * allocate(size_type n, const void *)
	{
		return static_cast<pointer>(malloc(sizeof(value_type) * n));
	}
	
	void construct(pointer p, const_reference x)
	{
		new(p) value_type(x);
	}

	void destroy(pointer p)
	{
		p->~value_type();
	}

	void deallocate(pointer p)
	{
		free(p);
	}
};

#endif // !_ALLOC_HPP_
