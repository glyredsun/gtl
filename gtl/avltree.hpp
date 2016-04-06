#ifdef _MSC_VER
#pragma once
#endif

#ifndef _AVLTREE_HPP_
#define _AVLTREE_HPP_

#include <macros.hpp>
#include <algorithm.hpp>

#include <iostream>

NS_BEGIN(gtl);

template <typename ElemType>
class avltree
{
public:

	~avltree()
	{
		makeEmpty();
	}

	bool insert(const ElemType &elem)
	{
		return insert(std::move(ElemType(elem)), _root);
	}

	bool insert(ElemType &&elem)
	{
		return insert(std::move(elem), _root);
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
		Node *left, *right;
		int height;
		Node(const ElemType &elem, Node *left = nullptr, Node *right = nullptr, int height = 0) : elem{ elem }, left{ left }, right{ right }, height{ height } { }
		Node(ElemType &&elem, Node *left = nullptr, Node *right = nullptr, int height = 0) : elem{ std::move(elem) }, left{ left }, right{ right }, height{ height } { }
	};

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

	static bool insert(ElemType &&elem, Node* &t)
	{
		bool ret = false;

		if (t == nullptr) {
			t = new Node(std::move(elem));
			ret = true;
		}
		else if (elem < t->elem) {
			ret = insert(std::move(elem), t->left);
		}
		else if (t->elem < elem) {
			ret = insert(std::move(elem), t->right);
		}
		
		balance(t);
		return ret;
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
		k2->height = max(height(k2->left), height(k2->right)) + 1;
		k1->height = max(height(k1->left), k2->height) + 1;
		k2 = k1;
	}

	static void rotateWithRightChild(Node* &k2)
	{
		Node *k1 = k2->right;
		k2->right = k1->left;
		k1->left = k2;
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

private:
	Node *_root{nullptr};
};

NS_END(gtl);

#endif