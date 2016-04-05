#ifdef _MSC_VER
#pragma once
#endif

#ifndef _AVLTREE_HPP_
#define _AVLTREE_HPP_

template <typename ElemType>
class avltree
{
protected:
	struct Node
	{
		ElemType elem;
		Node *left, *right;
		int heigh;
		Node(const ElemType &elem, Node *left = nullptr, Node *right = nullptr, int height = 0) : elem{ elem }, left{ left }, right{ right }, height{ height } { }
		Node(ElemType &&elem, Node *left = nullptr, Node *right = nullptr, int height = 0) : elem{ elem }, left{ left }, right{ right }, height{ height } { }
	};

	static int height(Node *root)
	{
		return root ? root->height : -1;
	}

	static void insert(ElemType &&elem, Node* &root)
	{
		if (root == nullptr) {
			root = new Node(std::move(elem));
		}
		else if (elem < root->elem) {
			insert(std::move(elem), root->left);
		}
		else if (root->elem < elem) {
			insert(std::move(elem), root->right);
		}
		
		balance(root);
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
		
		root->height = 1 + max(height(root->left), height(root->right));
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
		k2->right = = k1->left;
		k1->left = k2;
		k2->height = max(height(k2->left), height(k2->right)) + 1;
		k1->height = max(height(k1->left), k2->height) + 1;
		k2 = k1;
	}

	static doubleWithLeftChild(Node* &k3)
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

	static doubleWithRightChild(Node* &k3)
	{

	}

	static const int ALLOWED_IMBALANCE = 1;
};

#endif