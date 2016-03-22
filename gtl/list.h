#ifdef _MSC_VER
#pragma once
#endif

#ifndef _LIST_H_
#define	_LIST_H_

#ifdef __cplusplus
extern "C" {
#endif

struct list {
	struct list *prev;
	struct list *next;
};

#define	LIST_HEADER_INIT(h)	{&(h), &(h)}	

#ifdef __cplusplus
};
#endif

#endif