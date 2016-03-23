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

	list() : _head(ElemType(), &_head, &_head)
	{
	}

	~list()
	{
		Node *p = _head.next;
		while (p != &_head)
		{
			Node *next = p->next;
			delete p;
			p = next;
		}
	}

	void push_back(const ElemType &elem)
	{
		Node *newNode = new Node(elem, _head.pre, &_head);
		_head.pre->next = newNode;
		_head.pre = newNode;
	}

	void push_front(const ElemType &elem)
	{
		Node *newNode = new Node(elem, &_head, _head.next);
		_head.next->pre = newNode;
		_head.next = newNode;
	}

	ElemType &front()
	{
		return _head.next->elem;
	}

	const ElemType &front() const
	{
		return _head.next->elem;
	}

	ElemType &back()
	{
		return _head.pre->elem;
	}

	const ElemType &back() const
	{
		return _head.pre->elem;
	}

	void pop_front()
	{
		Node *frontNode = _head.next;
		_head.next = frontNode->next;
		frontNode->next->pre = &_head;
		delete frontNode;
	}

	void pop_back()
	{
		Node *backNode = _head.pre;
		_head.pre = backNode->pre;
		backNode->pre->next = &_head;
		delete backNode;
	}

	bool empty()
	{
		return _head.next == &_head;
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
		return iterator(_head.next);
	}

	iterator end() {
		return iterator(&_head);
	}

	reverse_iterator rbegin() {
		return iterator(_head.pre);
	}

	reverse_iterator rend() {
		return iterator(&_head);
	}

private:
	Node _head;
};


NS_END(gtl);

#endif // ! _LIST_HPP_