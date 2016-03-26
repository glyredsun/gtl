#ifdef _MSC_VER
#pragma once
#endif

#ifndef _LIST_HPP_
#define _LIST_HPP_

#include <macros.hpp>

#include <initializer_list>

NS_BEGIN(gtl);

template <typename ElemType>
class list
{
public:

	list()
	{

	}

	~list()
	{
		clear();
	}

	list(const list &other)
	{
		copyFrom(other);
	}

	list(list &&other)
	{
		moveFrom(other);
	}

	list& operator =(const list &other)
	{
		if (this != &other) {
			copyFrom(other);
		}
		return *this;
	}

	list& operator =(list &&other)
	{
		if (this != &other) {
			moveFrom(other);
		}
		return *this;
	}

	void push_back(const ElemType &elem)
	{
		Node *newNode = new Node(elem, _head.prev, &_head);
		_head.prev->next = newNode;
		_head.prev = newNode;
	}

	void push_front(const ElemType &elem)
	{
		Node *newNode = new Node(elem, &_head, _head.next);
		_head.next->prev = newNode;
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
		return _head.prev->elem;
	}

	const ElemType &back() const
	{
		return _head.prev->elem;
	}

	void pop_front()
	{
		Node *frontNode = _head.next;
		_head.next = frontNode->next;
		frontNode->next->prev = &_head;
		delete frontNode;
	}

	void pop_back()
	{
		Node *backNode = _head.prev;
		_head.prev = backNode->prev;
		backNode->prev->next = &_head;
		delete backNode;
	}

	void clear()
	{
		freeMemory(_head.next, &_head);
		_head.prev = _head.next = &_head;
	}

	bool empty() const
	{
		return _head.next == &_head;
	}

protected:

	struct Node {
		ElemType elem;
		Node *prev;
		Node *next;


		Node(const ElemType &&elem, Node *prev = nullptr, Node *next = nullptr) : elem(elem), prev(prev), next(next) {
			printf("%s %p\n", __FUNCTION__, this);
		}

		Node(const ElemType &elem, Node *prev = nullptr, Node *next = nullptr) : elem(elem), prev(prev), next(next) {
			printf("%s %p\n", __FUNCTION__, this);
		}

		~Node() {
			printf("%s %p\n", __FUNCTION__, this);
		}
	};

	void freeMemory(Node *first, Node *head)
	{
		for (Node *p = first, *n = p->next; p != head; p = n, n = p->next) {
			delete p;
		}
	}

	void copyFrom(const list& other) 
	{
		if (other.empty()) {
			clear();
			return;
		}

		Node *p = other._head.next;
		Node *n = _head.next;

		while (n != &_head && p != &other._head)
		{
			n->elem = p->elem;
			n = n->next;
			p = p->next;
		}

		if (n != &_head) {
			n->prev->next = &_head;
			_head.prev = n->prev;
			freeMemory(n, &_head);
		}

		while (p != &other._head) {
			push_back(p->elem);
			p = p->next;
		}
	}

	void moveFrom(list &other)
	{
		clear();

		if (other.empty()) {
			return;
		}

		_head.next = other._head.next;
		_head.prev = other._head.prev;
		other._head.next->prev = &_head;
		other._head.prev->next = &_head;

		other._head.next = &other._head;
		other._head.prev = &other._head;
	}


public:

	class iterator
	{
		friend class list;
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
			++*this;
			return copy;
		}

		iterator& operator --()
		{
			n = n->prev;
			return *this;
		}

		iterator operator --(int)
		{
			iterator copy(*this);
			--*this;
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
			n = n->prev;
			return *this;
		}

		reverse_iterator operator ++(int)
		{
			reverse_iterator copy(*this);
			n = n->prev;
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
		return iterator(_head.prev);
	}

	reverse_iterator rend() {
		return iterator(&_head);
	}

	void insert(const iterator &where, const ElemType &&elem) {
		Node *newNode = new Node(elem);
		newNode->next = where.n;
		newNode->prev = where.n->prev;
		where.n->prev->next = newNode;
		where.n->prev = newNode;
	}

	void insert(const iterator &where, const ElemType &elem) {
		insert(where, std::move(ElemType(elem)));
	}

	void insert(const iterator &where, size_t count, const ElemType &elem) {
		while (count-- >0)
		{
			insert(where, elem);
		}
	}

	void insert(const iterator &where, std::initializer_list<ElemType> list)
	{
		for(const ElemType &elem : list)
		{
			insert(where, std::move(elem));
		}
	}

private:
	Node _head{ElemType(), &_head, &_head};
};


NS_END(gtl);

#endif // ! _LIST_HPP_