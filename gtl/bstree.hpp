#ifdef _MSC_VER
#pragma once
#endif
#ifndef _BSTREE_HPP_
#define _BSTREE_HPP_

#include <macros.hpp>

#include <functional>

NS_BEGIN(gtl)

template <typename ElemType>
class bstree
{
public:

	~bstree()
	{
		makeEmpty(_root);
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

	void insert(ElemType &&elem, Node* &root)
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

	bool contain(const ElemType &elem, Node *root)
	{
		if (root)
		{
			if (elem < root->elem)
				return contain(elem, root->left);
			else if (root->elem < elem)
				return contain(elem, root->right);
			else
				return true;
		}
		return false;
	}

	Node* findMin(Node *root)
	{
		while (root && root->left)
			root = root->left;

		return root;
	}

	Node* findMax(Node *root)
	{
		while (root && root->right)
			root = root->right;

		return root;
	}

	void remove(const ElemType &elem, Node* &root)
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

	void makeEmpty(Node* &root)
	{
		if (root) {
			makeEmpty(root->left);
			makeEmpty(root->right);
			delete root;
			root = nullptr;
		}
	}

private:
	Node *_root{nullptr};
};

NS_END(gtl);

#endif