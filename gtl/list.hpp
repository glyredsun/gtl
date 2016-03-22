#ifdef _MSC_VER
#pragma once
#endif

#ifndef _LIST_HPP_
#define _LIST_HPP_

#include <macros.hpp>

NS_BEGIN(gtl);

template <typename ElemType>
class list
{
public:

	list() : _header(ElemType(), &_header, &_header)
	{
	}

	~list()
	{
		Node *p = _header.next;
		while (p != &_header)
		{
			Node *next = p->next;
			delete p;
			p = next;
		}
	}

	void push_back(const ElemType &elem)
	{
		Node *newNode = new Node(elem, _header.pre, &_header);
		_header.pre->next = newNode;
		_header.pre = newNode;
	}

	void push_front(const ElemType &elem)
	{
		Node *newNode = new Node(elem, &_header, _header.next);
		_header.next->pre = newNode;
		_header.next = newNode;
	}

	ElemType &front()
	{
		return _header.next->elem;
	}

	const ElemType &front() const
	{
		return _header.next->elem;
	}

	ElemType &back()
	{
		return _header.pre->elem;
	}

	const ElemType &back() const
	{
		return _header.pre->elem;
	}

	void pop_front()
	{
		Node *frontNode = _header.next;
		_header.next = frontNode->next;
		frontNode->next->pre = &_header;
		delete frontNode;
	}

	void pop_back()
	{
		Node *backNode = _header.pre;
		_header.pre = backNode->pre;
		backNode->pre->next = &_header;
		delete backNode;
	}

	bool empty()
	{
		return _header.next == &_header;
	}

private:
	struct Node {
		ElemType elem;
		Node *pre;
		Node *next;

		Node(const ElemType &elem, Node *pre, Node *next) : elem(elem), pre(pre), next(next) {
			printf("%s %p\n", __FUNCTION__, this);
		}
		~Node() {
			printf("%s %p\n", __FUNCTION__, this);
		}
	};

public:

	class iterator
	{
	public:
		iterator(Node *n) :n(n) {}
		iterator(const iterator& other) : iterator(other.n) {}

		iterator& operator ++()
		{
			n = n->next;
			return *this;
		}

		iterator operator ++(int)
		{
			iterator copy(*this);
			n = n->next;
			return copy;
		}

		ElemType& operator *()
		{
			return n->elem;
		}

		const ElemType& operator *() const
		{
			return n->elem;
		}

		ElemType& operator ->()
		{
			return n->elem;
		}

		const ElemType& operator ->() const
		{
			return n->elem;
		}

		bool operator == (const iterator& other)
		{
			if (&other == this)
				return true;

			return n == other.n;
		}

		bool operator != (const iterator& other)
		{
			return !(*this == other);
		}

	private:
		Node *n;
	};

	class reverse_iterator : public iterator
	{
	public:
		reverse_iterator& operator ++()
		{
			n = n->pre;
			return *this;
		}

		reverse_iterator operator ++(int)
		{
			reverse_iterator copy(*this);
			n = n->pre;
			return copy;
		}

	};

public:
	iterator begin() {
		return iterator(_header.next);
	}

	iterator end() {
		return iterator(&_header);
	}

	reverse_iterator rbegin() {
		return iterator(_header.pre);
	}

	reverse_iterator rend() {
		return iterator(&_header);
	}

private:
	Node _header;
};


NS_END(gtl);

#endif // ! _LIST_HPP_