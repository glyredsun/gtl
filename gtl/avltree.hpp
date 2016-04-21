#ifdef _MSC_VER
#pragma once
#endif

#ifndef _AVLTREE_HPP_
#define _AVLTREE_HPP_

#include <macros.hpp>
#include <algorithm.hpp>

#include <functional>
#include <iostream>
#include <cassert>

NS_BEGIN(gtl);

template <typename ElemType>
class avltree
{
public:
	typedef std::function<bool(const ElemType &, const ElemType &)> comparator_type;

	class iterator;
public:

	avltree()
	{
		_less = [](const ElemType &a, const ElemType &b) {
			return a < b;
		};
	}

	avltree(const comparator_type less)
		: _less(less)
	{

	}

	~avltree()
	{
		makeEmpty();
	}

	iterator insert(const ElemType &elem)
	{
		return iterator(insert(std::move(ElemType(elem)), _root, _less));
	}

	iterator insert(ElemType &&elem)
	{
		return iterator(insert(std::move(elem), _root, _less));
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
		ElemType elem;
		Node *left, *right, *parent;
		int height;
		Node(const ElemType &elem, Node *parent = nullptr, Node *left = nullptr, Node *right = nullptr, int height = 0) : elem{ elem }, parent{ parent }, left{ left }, right{ right },  height{ height } { }
		Node(ElemType &&elem, Node *parent = nullptr, Node *left = nullptr, Node *right = nullptr, int height = 0) : elem{ std::move(elem) }, parent{ parent }, left{ left }, right{ right }, height{ height } { }
	};

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

	static int height(Node *t)
	{
		return t ? t->height : -1;
	}

	static Node* insert(ElemType &&elem, Node* &t, const comparator_type &less)
	{
		Node *ret = nullptr;

		if (t == nullptr) {
			t = new Node(std::move(elem));
			ret = t;
		}
		else if (less(elem, t->elem)) {
			if (t->left)
				ret = insert(std::move(elem), t->left, less);
			else {
				t->left = new Node(std::move(elem), t);
				ret = t->left;
			}
		}
		else if (less(t->elem, elem)) {
			if (t->right)
				ret = insert(std::move(elem), t->right, less);
			else {
				t->right = new Node(std::move(elem), t);
				ret = t->right;
			}
		}
		else {
			ret = t;
		}
		
		balance(t);
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

	static void balance(Node* &t)
	{
		if (t == nullptr) {
			return;
		}

		if (height(t->left) - height(t->right) > ALLOWED_IMBALANCE) {
			if (height(t->left->left) >= height(t->left->right))
				rotateWithLeftChild(t);
			else
				doubleWithLeftChild(t);
		}
		else if (height(t->right) - height(t->left) > ALLOWED_IMBALANCE) {
			if (height(t->right->right) >= height(t->right->left))
				rotateWithRightChild(t);
			else
				doubleWithRightChild(t);
		}
		
		t->height = 1 + max(height(t->left), height(t->right));
	}

	static void rotateWithLeftChild(Node* &k2)
	{
		Node *k1 = k2->left;
		k2->left = k1->right;
		k1->right = k2;

		k1->parent = k2->parent;
		k2->parent = k1;
		if (k2->left) {
			k2->left->parent = k2;
		}
		
		k2->height = max(height(k2->left), height(k2->right)) + 1;
		k1->height = max(height(k1->left), k2->height) + 1;
		k2 = k1;
	}

	static void rotateWithRightChild(Node* &k2)
	{
		Node *k1 = k2->right;
		k2->right = k1->left;
		k1->left = k2;

		k1->parent = k2->parent;
		k2->parent = k1;
		if (k2->right) {
			k2->right->parent = k2;
		}

		k2->height = max(height(k2->left), height(k2->right)) + 1;
		k1->height = max(height(k1->left), k2->height) + 1;
		k2 = k1;
	}

	static void doubleWithLeftChild(Node* &k3)
	{
		Node *k1 = k3->left;
		Node *k2 = k1->right;

		k3->left = k2->right;
		k1->right = k2->left;
		k2->left = k1;
		k2->right = k3;

		k2->parent = k3->parent;
		k1->parent = k2;
		k3->parent = k2;
		if (k3->left) {
			k3->left->parent = k3;
		}
		if (k1->right) {
			k1->right->parent = k1;
		}
		
		k1->height = max(height(k1->left), height(k1->right)) + 1;
		k3->height = max(height(k3->left), height(k3->right)) + 1;
		k2->height = max(k1->height, k3->height) + 1;

		k3 = k2;
	}

	static void doubleWithRightChild(Node* &k3)
	{
		Node *k1 = k3->right;
		Node *k2 = k1->left;

		k3->right = k2->left;
		k1->left = k2->right;
		k2->left = k3;
		k2->right = k1;

		k2->parent = k3->parent;
		k1->parent = k2;
		k3->parent = k2;
		if (k3->right) {
			k3->right->parent = k3;
		}
		if (k1->left) {
			k1->left->parent = k1;
		}
		
		k1->height = max(height(k1->left), height(k1->right)) + 1;
		k3->height = max(height(k3->left), height(k3->right)) + 1;
		k2->height = max(k1->height, k3->height) + 1;

		k3 = k2;
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

	static const int ALLOWED_IMBALANCE = 1;

public:
	class iterator
	{
	public:
		iterator(Node* curr)
			: _curr{curr}
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
	Node *_root{nullptr};
	comparator_type _less;
};

NS_END(gtl);

#endif