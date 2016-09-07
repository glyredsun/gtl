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

template <class T>
void deallocate(T* p)
{
	free(p);
}

template <class InputIterator, class ForwardIterator>
ForwardIterator uninitialized_copy(InputIterator first, InputIterator last, ForwardIterator result)
{
	return __uninitialized_copy(first, last, result, type_traits<iterator_traits<ForwardIterator>::value_type>::has_trivial_default_constructor());
}

template <class InputIterator, class ForwardIterator>
ForwardIterator __uninitialized_copy(InputIterator first, InputIterator last, ForwardIterator result, __true_type)
{
	return ::memcpy(result, first, last - first);
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

template <class ForwardIterator, class T>
void uninitialized_fill(ForwardIterator first, ForwardIterator last, const T& value)
{
	__uninitialized_fill(first, last, value, type_traits<iterator_traits<ForwardIterator>::value_type>::has_trivial_default_constructor());
}

template <class ForwardIterator, class T>
void __uninitialized_fill(ForwardIterator first, ForwardIterator last, const T& value, __true_type)
{
	while (first != last)
	{
		*first++ = value;
	}
}

template <class ForwardIterator, class T>
void __uninitialized_fill(ForwardIterator first, ForwardIterator last, const T& value, __false_type)
{
	while (first != last)
	{
		construct(&*first++, value);
	}
}

template <class ForwardIterator, class Size, class T>
void uninitialized_fill_n(ForwardIterator first, Size n, const T& value)
{
	__uninitialized_fill_n(first, n, value, type_traits<iterator_traits<ForwardIterator>::value_type>::has_trivial_default_constructor());
}

template <class ForwardIterator, class Size, class T>
void __uninitialized_fill_n(ForwardIterator first, Size n, const T& value, __true_type)
{
	while (n-- > 0)
	{
		*first++ = value;
	}
}

template <class ForwardIterator, class Size, class T>
void __uninitialized_fill_n(ForwardIterator first, Size n, const T& value, __false_type)
{
	while (n-- > 0)
	{
		construct(&*first++, value);
	}
}

NS_END(gtl);

#endif