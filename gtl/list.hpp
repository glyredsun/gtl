#ifdef _MSC_VER
#pragma once
#endif

#ifndef _LIST_HPP_
#define _LIST_HPP_

template <typename ElemType>
class List
{
public:

private:
	struct Node {
		ElemType elem;
		Node *pre;
		Node *next;
	};
};

#endif // ! _LIST_HPP_