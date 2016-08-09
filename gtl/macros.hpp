#ifdef _MSC_VER
#pragma once
#endif // _MSC_VER

#ifndef _MACROS_HPP_
#define _MACROS_HPP_

#define	NS_BEGIN(ns)	namespace ns {

#define NS_END(ns)		};

#define GTL_BEGIN_NS	NS_BEGIN(gtl)

#define GTL_END_NS		NS_END(gtl)

#define DECLEAR_FOR_EVERY_PRIMARYTYPE(macro, ...)	\
macro(char, __VA_ARGS__);							\
macro(signed char, __VA_ARGS__);					\
macro(unsigned char, __VA_ARGS__);					\
macro(wchar_t, __VA_ARGS__);						\
macro(short, __VA_ARGS__);							\
macro(unsigned short, __VA_ARGS__);					\
macro(int, __VA_ARGS__);							\
macro(unsigned int, __VA_ARGS__);					\
macro(long, __VA_ARGS__);							\
macro(unsigned long, __VA_ARGS__);					\
macro(long long, __VA_ARGS__);						\
macro(unsigned long long, __VA_ARGS__);				\
macro(float, __VA_ARGS__);							\
macro(double, __VA_ARGS__);							\


#endif // !_MACROS_HPP_
