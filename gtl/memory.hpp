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

NS_END(gtl);

#endif