#ifdef _MSC_VER
#pragma once
#endif

#ifndef _MEMORY_HPP_
#define _MEMORY_HPP_

NS_BEGIN(gtl);

template <typename T>
class unique_ptr
{
	typedef T* pointer;
public:
	explicit unique_ptr(pointer ptr)
		: _ptr(ptr)
	{

	}

	~unique_ptr()
	{
		delete[] ptr;
	}

private:
	pointer _ptr;
};

template <class T, class Size>
T* allocate(Size n, const void *)
{
	return n > 0 ? static_cast<T*>(malloc(sizeof(T) * n)) : nullptr;
}

template <class T>
inline void deallocate(T* data)
{
	free(data);
}

template <class T>
void construct(T* p)
{
	new(p) T();
}

template <class T1, class T2>
inline void construct(T1* p, const T2& value)
{
	new (p) T1(value);
}

template <class T1, class T2>
void construct(T1* p, T2&& val)
{
	new(p) T1(val);
}

template <class T>
inline void destroy(T *p)
{
	p->~T();
}

template <class Iterator>
void destroy(Iterator first, Iterator last)
{
	_destroy(first, last, type_traits<value_type>::has_trivial_destructor());
}

template <class T>
void deallocate(T* p)
{
	free(p);
}

template <class InputIterator, class ForwardIterator>
ForwardIterator uninitialized_copy(InputIterator first, InputIterator last, ForwardIterator result)
{
	__uninitialized_copy(first, last, result, type_traits<iterator_traits<ForwardIterator>::value_type>::has_trivial_default_constructor());
}

template <class InputIterator, class ForwardIterator>
ForwardIterator __uninitialized_copy(InputIterator first, InputIterator last, ForwardIterator result, __true_type)
{
	::memcpy(result, first, last - first);
}

template <class InputIterator, class ForwardIterator>
ForwardIterator __uninitialized_copy(InputIterator first, InputIterator last, ForwardIterator result, __false_type)
{
	while (first < last)
	{
		construct(&*result++, &*first++);
	}
	return result;
}

template <class Iterator>
void __destroy(Iterator first, Iterator last, __true_type)
{
	// do nothing
}

template <class Iterator>
void __destroy(Iterator first, Iterator last, __false_type)
{
	while (first < last)
	{
		destroy(&*first++);
	}
}

NS_END(gtl);

#endif