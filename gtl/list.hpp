#ifdef _MSC_VER
#pragma once
#endif

#ifndef _LIST_HPP_
#define _LIST_HPP_

#include <macros.hpp>
#include <type_traits.hpp>
#include <iterator.hpp>
#include <alloc.hpp>

#include <initializer_list>

NS_BEGIN(gtl);

template <class DataType>
struct __list_node
{
	DataType data;
	__list_node *prev;
	__list_node *next;
};

template <class DataType>
class __list_iterator
{
public:

	typedef DataType value_type;
	typedef __list_node<value_type> node_type;
	typedef ptrdiff_t difference_type;
	typedef DataType* pointer;
	typedef const DataType* const_pointer;
	typedef DataType& reference;
	typedef const DataType& const_reference;
	typedef bidirectional_iterator_tag iterator_category;
	typedef __list_node<DataType> node_type;

	__list_iterator() {}
	__list_iterator(node_type *n) :n(n) {}
	__list_iterator(const __list_iterator& other) : __list_iterator(other.n) {}

	__list_iterator& operator ++()
	{
		n = n->next;
		return *this;
	}

	__list_iterator operator ++(int)
	{
		__list_iterator copy(*this);
		++*this;
		return copy;
	}

	__list_iterator& operator --()
	{
		n = n->prev;
		return *this;
	}

	__list_iterator operator --(int)
	{
		__list_iterator copy(*this);
		--*this;
		return copy;
	}

	__list_iterator operator +(int count)
	{
		node_type *node = n;
		while (count-- > 0)
		{
			node = node->next;
		}
		return __list_iterator(node);
	}

	__list_iterator operator -(int count)
	{
		node_type *node = n;
		while (count-- > 0)
		{
			node = node->prev;
		}
		return __list_iterator(node);
	}

	reference operator *()
	{
		return n->data;
	}

	const_reference operator *() const
	{
		return n->data;
	}

	pointer operator ->()
	{
		return &n->data;
	}

	const_pointer operator ->() const
	{
		return &n->data;
	}

	bool operator == (const __list_iterator& other)
	{
		if (&other == this)
			return true;

		return n == other.n;
	}

	bool operator != (const __list_iterator& other)
	{
		return !(*this == other);
	}

	node_type* node() {
		return n;
	}

	const node_type* node() const {
		return n;
	}

private:
	node_type *n{ nullptr };
};

template <class DataType>
class __list_const_iterator
{
public:

	typedef DataType value_type;
	typedef __list_node<value_type> node_type;
	typedef size_t difference_type;
	typedef const value_type* pointer;
	typedef const value_type& reference;
	typedef bidirectional_iterator_tag iterator_category;

	__list_const_iterator() {}
	__list_const_iterator(const node_type *n) :n(n) {}
	__list_const_iterator(const __list_const_iterator& other) : __list_const_iterator(other.n) {}

	__list_const_iterator& operator ++()
	{
		n = n->next;
		return *this;
	}

	__list_const_iterator operator ++(int)
	{
		__list_const_iterator copy(*this);
		++*this;
		return copy;
	}

	__list_const_iterator& operator --()
	{
		n = n->prev;
		return *this;
	}

	__list_const_iterator operator --(int)
	{
		__list_const_iterator copy(*this);
		--*this;
		return copy;
	}

	__list_const_iterator operator +(difference_type count)
	{
		const node_type *node = n;
		while (count-- > 0)
		{
			node = node->next;
		}
		return __list_const_iterator(node);
	}

	__list_const_iterator operator -(difference_type count)
	{
		const node_type *node = n;
		while (count-- > 0)
		{
			node = node->prev;
		}
		return __list_const_iterator(node);
	}

	reference operator *() const
	{
		return n->data;
	}

	pointer operator ->() const
	{
		return &n->data;
	}

	bool operator == (const __list_const_iterator& other)
	{
		if (&other == this)
			return true;

		return n == other.n;
	}

	bool operator != (const __list_const_iterator& other)
	{
		return !(*this == other);
	}

private:
	const node_type *n{ nullptr };
};

template <class DataType, class Allocate = gtl::allocator<__list_node<DataType>>>
class list
{
public:

	typedef DataType value_type;
	typedef value_type* pointer;
	typedef value_type& reference;
	typedef const value_type* const_pointer;
	typedef const value_type& const_reference;
	typedef value_type&& rvalue_reference;
	typedef __list_node<DataType> node_type;
	typedef __list_iterator<DataType> iterator;
	typedef reverse_iterator<iterator> reverse_iterator;
	typedef __list_const_iterator<DataType> const_iterator;
	typedef gtl::reverse_iterator<const_iterator> const_reverse_iterator;

	list()
	{

	}

	~list()
	{
		clear();
	}

	list(const list &other)
	{
		assign(other);
	}

	list(list &&other)
	{
		assign(gtl::move(other));
	}

	list& operator =(const list &other)
	{
		if (this != &other) {
			assign(other);
		}
		return *this;
	}

	list& operator =(list &&other)
	{
		if (this != &other) {
			assign(gtl::move(other));
		}
		return *this;
	}

	void assign(const list& other)
	{
		if (other.empty()) {
			clear();
			return;
		}

		node_type *p = other._head.next;
		node_type *n = _head.next;

		while (n != &_head && p != &other._head)
		{
			n->data = p->data;
			n = n->next;
			p = p->next;
		}

		if (n != &_head) {
			n->prev->next = &_head;
			_head.prev = n->prev;
			freeMemory(n, &_head);
		}

		while (p != &other._head) {
			push_back(p->data);
			p = p->next;
		}
	}

	void assign(list &&other)
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

	void push_back(const_reference elem)
	{
		node_type *newNode = createNode(elem);
		newNode->prev = _head.prev;
		newNode->next = &_head;
		_head.prev->next = newNode;
		_head.prev = newNode;
	}

	void push_front(const_reference elem)
	{
		node_type *newNode = createNode(elem);
		newNode->prev = &_head;
		newNode->next = _head.next;
		_head.next->prev = newNode;
		_head.next = newNode;
	}

	reference front()
	{
		return _head.next->data;
	}

	const_reference front() const
	{
		return _head.next->data;
	}

	reference back()
	{
		return _head.prev->data;
	}

	const_reference back() const
	{
		return _head.prev->data;
	}

	void pop_front()
	{
		node_type *frontNode = _head.next;
		_head.next = frontNode->next;
		frontNode->next->prev = &_head;
		destroyNode(frontNode);
	}

	void pop_back()
	{
		node_type *backNode = _head.prev;
		_head.prev = backNode->prev;
		backNode->prev->next = &_head;
		destroyNode(backNode);
	}

	void reverse()
	{
		node_type head = _head;
		head.next->prev = head.prev->next = &head;
		
		_head.next = _head.prev = &_head;
		
		for (node_type *cur = head.next; cur != &head;)
		{
			node_type *next = cur->next;
			_head.next->prev = cur;
			cur->next = _head.next;
			cur->prev = &_head;
			_head.next = cur;
			cur = next;
		}
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

	const_reverse_iterator rbegin() const {
		return const_reverse_iterator(end());
	}

	const_reverse_iterator rend() const {
		return const_reverse_iterator(begin());
	}

	void insert(iterator &where, rvalue_reference elem) {
		node_type *newNode = createNode(elem);
		node_type* n = where.node();
		newNode->next = n;
		newNode->prev = n->prev;
		n->prev->next = newNode;
		n->prev = newNode;
	}

	void insert(iterator &where, const_reference elem) {
		node_type *newNode = createNode(elem);
		node_type* n = where.node();
		newNode->next = n;
		newNode->prev = n->prev;
		n->prev->next = newNode;
		n->prev = newNode;
	}

	void insert(const iterator &where, size_t count, const_reference elem) {
		while (count-- > 0)
		{
			insert(where, elem);
		}
	}

	void insert(iterator &where, std::initializer_list<DataType> list)
	{
		for (const DataType &elem : list)
		{
			insert(where, gtl::move(elem));
		}
	}

	void erase(iterator &where)
	{
		node_type *n = where.node();
		n->next->prev = n->prev;
		n->prev->next = n->next;
		destroyNode(n);
	}

	void erase(iterator &first, iterator &last)
	{
		node_type* n1 = first.node();
		node_type* n2 = last.node();
		n1->prev->next = n2;
		n2->prev = n1->prev;

		freeMemory(n1, n2);
	}

protected:

	void freeMemory(node_type *first, node_type *head)
	{
		for (node_type *p = first, *n = p->next; p != head; p = n, n = p->next) {
			destroyNode(p);
		}
	}

	node_type* createNode() {
		node_type* node = _alloc.allocate(1);
		construct(&node->data);
		return node;
	}

	node_type* createNode(const_reference data) {
		node_type* node = _alloc.allocate(1);
		construct(&node->data, data);
		return node;
	}

	node_type* createNode(rvalue_reference data) {
		node_type* node = _alloc.allocate(1);
		construct(&node->data, data);
		return node;
	}

	void destroyNode(node_type* node) {
		destroy(&node->data);
		_alloc.deallocate(node);
	}

private:
	Allocate _alloc;
	node_type _head{DataType(), &_head, &_head};
};


NS_END(gtl);

#endif // ! _LIST_HPP_