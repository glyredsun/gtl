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

	pointer allocate(size_type n, const void *)
	{
		return n > 0 ? static_cast<pointer>(malloc(sizeof(value_type) * n)) : nullptr;
	}
	
	void construct(pointer p)
	{
		new(p) value_type();
	}

	void construct(pointer p, const_reference val)
	{
		new(p) value_type(val);
	}

	void construct(pointer p, rvalue_reference val)
	{
		new(p) value_type(val);
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
