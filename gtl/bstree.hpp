#ifdef _MSC_VER
#pragma once
#endif
#ifndef _BSTREE_HPP_
#define _BSTREE_HPP_

#include <macros.hpp>
#include <algorithm.hpp>

#include <functional>

NS_BEGIN(gtl)

template <typename ElemType>
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

	bstree(bstree &&other)
	{
		moveFrom(other);
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
			moveFrom(other);
		}
		return *this;
	}

	void insert(const ElemType &elem)
	{
		insert(std::move(ElemType(elem));
	}

	void insert(ElemType &&elem)
	{
		insert(elem, _root);
	}

	bool contain(const ElemType &elem)
	{
		return contain(elem, _root);
	}

	ElemType& findMin()
	{
		return *findMin(_root);
	}

	const ElemType& findMin() const
	{
		return findMin();
	}

	ElemType& findMax()
	{
		return *findMax(_root);
	}

	const ElemType& findMax() const
	{
		return findMax();
	}

	void remove(const ElemType &elem)
	{	
		remove(elem, _root);
	}

	void preorderTraverse(const std::function<void(const ElemType&)> &handler)
	{

	}

protected:

	struct Node {
		ElemType elem;
		Node *left, *right;
		Node(const ElemType &elem, Node *left = nullptr, Node *right = nullptr) : elem(elem), left(left), right(right) {}
		Node(ElemType &&elem, Node *left = nullptr, Node *right = nullptr) : elem(elem), left(left), right(right) {}
	};

	static void insert(ElemType &&elem, Node* &root)
	{
		if (root) {
			if (elem < root->elem)
				insert(elem, root->left);
			else if (root->elem < elem)
				insert(elem, root->right);
		}
		else {
			root = new Node(elem);
		}
	}

	static bool contain(const ElemType &elem, Node *root) const
	{
		if (root) {
			if (elem < root->elem)
				return contain(elem, root->left);
			else if (root->elem < elem)
				return contain(elem, root->right);
			else
				return true;
		}
		return false;
	}

	static Node* findMin(Node *root)
	{
		if (root) {
			while (root->left) {
				root = root->left;
			}
		}
		
		return root;
	}

	static Node* findMax(Node *root)
	{
		if (root) {
			while (root->right) {
				root = root->right;
			}
		}
		
		return root;
	}

	static void remove(const ElemType &elem, Node* &root)
	{
		if (!root)
			return

		if (elem < root->elem)
			remove(elem, root->left);
		else if (root->elem < elem)
			remove(elem, root->right);
		else if (root->left && root->right) {
			root->elem = findMin(root->right)->elem;
			remove(root->elem, root->right);
		}
		else {
			Node *old = root;
			root = root->left ? root->left : root->right;
			delete old;
		}
	}

	static void makeEmpty(Node* &root)
	{
		if (root) {
			makeEmpty(root->left);
			makeEmpty(root->right);
			delete root;
			root = nullptr;
		}
	}

	static Node* clone(Node *root) const
	{
		if (root) {

			return new Node(root->elem, clone(root->left), clone(root->right));
		}
		return nullptr;
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