#ifdef _MSC_VER
#pragma once
#endif // _MSC_VER

#ifndef _ALLOC_HPP_
#define _ALLOC_HPP_

#include <memory.hpp>

GTL_BEGIN_NS

template <class Type>
class allocator
{
public:
	typedef Type				value_type;
	typedef size_t				size_type;
	typedef ptrdiff_t			difference_type;
	typedef value_type*			pointer;
	typedef value_type&			reference;
	typedef value_type&&		rvalue_reference;
	typedef const value_type*	const_pointer;
	typedef const value_type&	const_reference;

	template <class U>
	struct rebind
	{
		typedef allocator<U> other;
	};

	allocator() noexcept {}
	allocator(const allocator&) noexcept {}
	template <class U> allocator(const allocator<U>&) noexcept {}
	~allocator() noexcept {}

	pointer allocate(size_type n, const void *p = nullptr)
	{
		return gtl::allocate<value_type>(n, p);
	}
	
	void deallocate(pointer p)
	{
		gtl::deallocate(p);
	}
};

GTL_END_NS

#endif // !_ALLOC_HPP_
