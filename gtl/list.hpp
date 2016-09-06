#ifdef _MSC_VER
#pragma once
#endif

#ifndef _LIST_HPP_
#define _LIST_HPP_

#include <macros.hpp>
#include <type_traits.hpp>
#include <iterator.hpp>

#include <initializer_list>

NS_BEGIN(gtl);

template <class ElemType>
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
		moveFrom(gtl::move(other));
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
			moveFrom(gtl::move(other));
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
			//printf("%s %p\n", __FUNCTION__, this);
		}

		Node(const ElemType &elem, Node *prev = nullptr, Node *next = nullptr) : elem(elem), prev(prev), next(next) {
			//printf("%s %p\n", __FUNCTION__, this);
		}

		~Node() {
			//printf("%s %p\n", __FUNCTION__, this);
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

	void moveFrom(list &&other)
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
		friend list;
	public:

		typedef ElemType value_type;
		typedef ptrdiff_t difference_type;
		typedef ElemType* pointer;
		typedef const ElemType* const_pointer;
		typedef ElemType& reference;
		typedef const ElemType& const_reference;
		typedef bidirectional_iterator_tag iterator_category;

		iterator() {}
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

		iterator operator +(int count)
		{
			Node *node = n;
			while (count-- > 0)
			{
				node = node->next;
			}
			return iterator(node);
		}

		iterator operator -(int count)
		{
			Node *node = n;
			while (count-- > 0)
			{
				node = node->prev;
			}
			return iterator(node);
		}

		reference operator *()
		{
			return n->elem;
		}

		const_reference operator *() const
		{
			return n->elem;
		}

		pointer operator ->()
		{
			return &n->elem;
		}

		const_pointer operator ->() const
		{
			return &n->elem;
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
		Node *n{nullptr};
	};

	typedef reverse_iterator<iterator> reverse_iterator;
	
	class const_iterator
	{
		friend list;
	public:

		typedef ElemType value_type;
		typedef size_t difference_type;
		typedef const value_type* pointer;
		typedef const value_type& reference;
		typedef bidirectional_iterator_tag iterator_category;

		const_iterator() {}
		const_iterator(const Node *n) :n(n) {}
		const_iterator(const const_iterator& other) : const_iterator(other.n) {}

		const_iterator& operator ++()
		{
			n = n->next;
			return *this;
		}

		const_iterator operator ++(int)
		{
			const_iterator copy(*this);
			++*this;
			return copy;
		}

		const_iterator& operator --()
		{
			n = n->prev;
			return *this;
		}

		const_iterator operator --(int)
		{
			const_iterator copy(*this);
			--*this;
			return copy;
		}

		const_iterator operator +(difference_type count)
		{
			const Node *node = n;
			while (count-- > 0)
			{
				node = node->next;
			}
			return const_iterator(node);
		}

		const_iterator operator -(difference_type count)
		{
			const Node *node = n;
			while (count-- > 0)
			{
				node = node->prev;
			}
			return const_iterator(node);
		}

		reference operator *() const
		{
			return n->elem;
		}

		pointer operator ->() const
		{
			return &n->elem;
		}

		bool operator == (const const_iterator& other)
		{
			if (&other == this)
				return true;

			return n == other.n;
		}

		bool operator != (const const_iterator& other)
		{
			return !(*this == other);
		}

	private:
		const Node *n{ nullptr };
	};

public:
	iterator begin() {
		return iterator(_head.next);
	}

	iterator end() {
		return iterator(&_head);
	}

	const_iterator begin() const {
		return const_iterator(_head.next);
	}

	const_iterator end() const {
		return const_iterator(&_head);
	}

	reverse_iterator rbegin() {
		return reverse_iterator(end());
	}

	reverse_iterator rend() {
		return reverse_iterator(begin());
	}

	void insert(const iterator &where, const ElemType &&elem) {
		Node *newNode = new Node(elem);
		newNode->next = where.n;
		newNode->prev = where.n->prev;
		where.n->prev->next = newNode;
		where.n->prev = newNode;
	}

	void insert(const iterator &where, const ElemType &elem) {
		insert(where, gtl::move(ElemType(elem)));
	}

	void insert(const iterator &where, size_t count, const ElemType &elem) {
		while (count-- > 0)
		{
			insert(where, elem);
		}
	}

	void insert(const iterator &where, std::initializer_list<ElemType> list)
	{
		for (const ElemType &elem : list)
		{
			insert(where, gtl::move(elem));
		}
	}

	void erase(const iterator &where)
	{
		Node *n = where.n;
		n->next->prev = n->prev;
		n->prev->next = n->next;
		delete n;
	}

	void erase(const iterator &first, const iterator &last)
	{
		first.n->prev->next = last.n;
		last.n->prev = first.n->prev;

		freeMemory(first.n, last.n);
	}

private:
	Node _head{ElemType(), &_head, &_head};
};


NS_END(gtl);

#endif // ! _LIST_HPP_