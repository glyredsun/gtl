#ifdef _MSC_VER
#pragma once
#endif

#ifndef _RBTREE_HPP
#define _RBTREE_HPP

#include <macros.hpp>
#include <algorithm.hpp>

#include <functional>
#include <iostream>
#include <cassert>

NS_BEGIN(gtl);

template <class ElemType>
class rbtree
{
public:
	typedef std::function<bool(const ElemType &, const ElemType &)> comparator_type;

	class iterator;
public:

	rbtree()
	{
		_less = [](const ElemType &a, const ElemType &b) {
			return a < b;
		};
	}

	rbtree(const comparator_type less)
		: _less(less)
	{

	}

	~rbtree()
	{
		makeEmpty();
	}

	iterator insert(const ElemType &elem)
	{
		return iterator(insert(gtl::move(ElemType(elem)), _root, _less));
	}

	iterator insert(ElemType &&elem)
	{
		return iterator(insert(gtl::move(elem), _root, _less));
	}

	iterator find(const ElemType &elem)
	{
		return iterator(find(elem, _root, _less));
	}

	void remove(const ElemType &elem)
	{
		remove(elem, _root, _less);
	}

	void makeEmpty()
	{
		makeEmpty(_root);
	}

	void print()
	{
		print(_root, 0);
	}

protected:

	struct Node
	{
		using Color = bool;
		static const Color RED = true;
		static const Color BLACK = false;

		ElemType elem;
		Node *left, *right, *parent;
		Color color;
		Node(const ElemType &elem, Node *parent = nullptr, Node *left = nullptr, Node *right = nullptr, Color color = RED) : elem{ elem }, parent{ parent }, left{ left }, right{ right }, color{ color } { }
		Node(ElemType &&elem, Node *parent = nullptr, Node *left = nullptr, Node *right = nullptr, Color color = RED) : elem{ gtl::move(elem) }, parent{ parent }, left{ left }, right{ right }, color{ color } { }
	};

	static bool isRed(Node *n)
	{
		return n != nullptr && n->color;
	}

	static Node* findMin(Node *t)
	{
		if (t)
			while (t->left)
				t = t->left;

		return t;
	}

	static Node* findMax(Node *t)
	{
		if (t)
			while (t->right)
				t = t->right;

		return t;
	}

	static Node* find(const ElemType &elem, Node *t, const comparator_type &less)
	{
		if (t == nullptr)
		{
			return nullptr;
		}
		else if (less(elem, t->elem))
		{
			return find(elem, t->left, less);
		}
		else if (less(t->elem, elem))
		{
			return find(elem, t->right, less);
		}
		else
		{
			return t;
		}
	}

	static void print(Node *t, int depth)
	{
		if (t == nullptr)
		{
			std::cout << std::endl;
			return;
		}

		print(t->left, depth + 1);

		for (int i = 0; i < depth; i++)
		{
			std::cout << "\t";
		}
		std::cout << t->elem;

		print(t->right, depth + 1);
	}

	static Node* insert(ElemType &&elem, Node* &t, const comparator_type &less)
	{
		Node *ret = nullptr;

		if (t == nullptr) {
			t = new Node(gtl::move(elem));
			ret = t;
		}
		else {

			if (isRed(t->left) && isRed(t->right)) {
				colorFlip(*t);
			}

			if (less(elem, t->elem)) {
				if (t->left)
					ret = insert(gtl::move(elem), t->left, less);
				else {
					t->left = new Node(gtl::move(elem), t);
					ret = t->left;
				}
			}
			else if (less(t->elem, elem)) {
				if (t->right)
					ret = insert(gtl::move(elem), t->right, less);
				else {
					t->right = new Node(gtl::move(elem), t);
					ret = t->right;
				}
			}
			else {
				ret = t;
			}

			if (isRed(t->right)) {
				rotateLeft(t);
			}

			if (isRed(t->left) && isRed(t->left->left)) {
				rotateRight(t);
			}
		} 

		return ret;
	}

	static void remove(const ElemType &elem, Node* &t, const comparator_type &less)
	{
		if (t == nullptr) {
			return;
		}

		if (less(elem, t->elem))
			remove(elem, t->left, less);
		else if (less(t->elem, elem))
			remove(elem, t->right, less);
		else if (t->left && t->right)
		{
			t->elem = findMin(t->right)->elem;
			remove(t->elem, t->right, less);
		}
		else
		{
			Node *oldNode = t;
			t = t->left ? t->left : t->right;
			delete oldNode;
		}

		balance(t);
	}

	static Node* rotateLeft(Node* &h)
	{
		Node *x = h->right;
		h->right = x->left;
		x->left = h;
		x->color = x->left->color;
		x->left->color = Node::RED;
		return x;
	}

	static Node* rotateRight(Node* &h)
	{
		Node *x = h->left;
		h->left = x->right;
		x->right = h;
		x->color = x->right->color;
		x->right->color = Node::RED;
		return x;
	}

	static Node* colorFlip(Node &h)
	{
		h.color = !h.color;
		h.left->color = !h.left->color;
		h.right->color = !h.right->color;
		return &h;
	}

	static void makeEmpty(Node* &t)
	{
		if (t == nullptr) {
			return;
		}

		makeEmpty(t->left);
		makeEmpty(t->right);
		delete t;
		t = nullptr;
	}

public:
	class iterator
	{
	public:
		iterator(Node* curr)
			: _curr{ curr }
		{

		}

		ElemType& operator *()
		{
			return _curr->elem;
		}

		ElemType* operator ->()
		{
			return &_curr->elem;
		}

		iterator& operator ++()
		{
			assert(_curr != nullptr);

			if (_curr->right != nullptr) {
				_curr = findMin(_curr->right);
			}
			else {
				Node *curr = _curr;
				Node *parent = curr->parent;
				while (parent && parent->right == curr) {
					curr = parent;
					parent = parent->parent;
				}
				_curr = parent;
			}

			return *this;
		}

		iterator operator ++(int) const
		{
			iterator itr(this->_tree);
			++itr;
			return itr;
		}

		bool operator == (const iterator &other) const
		{
			return _curr == other._curr;
		}

		bool operator != (const iterator &other) const
		{
			return !(*this == other);
		}

	protected:
		Node *_curr{ nullptr };
	};

public:

	iterator begin() {
		return iterator(findMin(_root));
	}

	iterator end() {
		return iterator(nullptr);
	}

private:
	Node *_root{ nullptr };
	comparator_type _less;
};

NS_END(gtl);

#endif