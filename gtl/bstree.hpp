#ifdef _MSC_VER
#pragma once
#endif
#ifndef _BSTREE_HPP_
#define _BSTREE_HPP_

#include <macros.hpp>
#include <type_traits.hpp>
#include <algorithm.hpp>

#include <functional>

NS_BEGIN(gtl)

template <class ElemType>
class bstree
{
public:

	bstree()
	{

	}

	bstree(const bstree &other)
	{
		copyFrom(other);
	}

	bstree(bstree&& other)
	{
		moveFrom(gtl::move(other));
	}

	~bstree()
	{
		makeEmpty(_root);
	}

	bstree& operator = (const bstree &other)
	{
		if (this != &other) {
			copyFrom(other);
		}
		return *this;
	}

	bstree& operator = (bstree &&other)
	{
		if (this != &other) {
			moveFrom(gtl::move(other));
		}
		return *this;
	}

	void insert(const ElemType &elem)
	{
		insert(gtl::move(ElemType(elem)), _root);
	}

	void insert(ElemType &&elem)
	{
		insert(gtl::move(elem), _root);
	}

	bool contain(const ElemType &elem)
	{
		return contain(elem, _root);
	}

	void remove(const ElemType &elem)
	{	
		remove(elem, _root);
	}

	void midorderTraverse(const std::function<void(const ElemType&)> &handler)
	{
		midorderTraverse(_root, handler);
	}

	void print()
	{
		print(_root, 0);
	}

protected:

	struct Node {
		ElemType elem;
		Node *left, *right;
		
		Node(ElemType &&elem, Node *left = nullptr, Node *right = nullptr) : elem(elem), left(left), right(right) {
			std::cout << __FUNCTION__ << std::endl;
		}
	};

	static void insert(ElemType &&elem, Node* &t)
	{
		if (t) {
			if (elem < t->elem)
				insert(gtl::move(elem), t->left);
			else if (t->elem < elem)
				insert(gtl::move(elem), t->right);
		}
		else {
			t = new Node(gtl::move(elem));
		}
	}

	static bool contain(const ElemType &elem, Node *t)
	{
		if (t) {
			if (elem < t->elem)
				return contain(elem, t->left);
			else if (t->elem < elem)
				return contain(elem, t->right);
			else
				return true;
		}
		return false;
	}

	static Node* findMin(Node *t)
	{
		if (t) {
			while (t->left) {
				t = t->left;
			}
		}
		
		return t;
	}

	static Node* findMax(Node *t)
	{
		if (t) {
			while (t->right) {
				t = t->right;
			}
		}
		
		return t;
	}

	static void remove(const ElemType &elem, Node* &t)
	{
		if (!t)
			return;

		if (elem < t->elem)
			remove(elem, t->left);
		else if (t->elem < elem)
			remove(elem, t->right);
		else if (t->left && t->right) {
			t->elem = findMin(t->right)->elem;
			remove(t->elem, t->right);
		}
		else {
			Node *old = t;
			t = t->left ? t->left : t->right;
			delete old;
		}
	}

	static void makeEmpty(Node* &t)
	{
		if (t) {
			makeEmpty(t->left);
			makeEmpty(t->right);
			delete t;
			t = nullptr;
		}
	}

	static Node* clone(Node *t)
	{
		if (t) {

			return new Node(t->elem, clone(t->left), clone(t->right));
		}
		return nullptr;
	}

	static void midorderTraverse(Node *t, const std::function<void(const ElemType&)> &handler)
	{
		if (t)
		{
			midorderTraverse(t->left, handler);
			handler(t->elem);
			midorderTraverse(t->right, handler);
		}
	}

	static void print(Node *t, int depth)
	{
		if (t == nullptr) {
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

protected:

	void copyFrom(const bstree &other)
	{
		makeEmpty(_root);
		_root = clone(other._root);
	}

	void moveFrom(bstree &&other)
	{
		makeEmpty(_root);
		gtl::swap(_root, other._root);
	}

private:
	Node *_root{nullptr};
};

NS_END(gtl);

#endif