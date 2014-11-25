#ifndef __1352847_RED_BLACK_TREE_H__
#define __1352847_RED_BLACK_TREE_H__

#include <iostream>
using namespace std;

typedef bool RBColor;
const bool RBT_BLACK = false;
const bool RBT_RED = true;

template <class T>
struct RBTNode {
	RBTNode(RBTNode* _pNode)
	{
		this->color = RBT_RED;
		this->parent = _pNode;
		this->left = nullptr;
		this->right = nullptr;
	}

	RBTNode(RBTNode* _pNode, const T& _key)
	{
		this->color = RBT_RED;
		this->parent = _pNode;
		this->left = nullptr;
		this->right = nullptr;
		this->key = _key;
	}

	T key;
	RBColor color;
	RBTNode *parent;
	RBTNode *left;
	RBTNode *right;
};

template<class T>
class RBTree {
public:
	RBTree()
	{
		//this->root = new RBTNode<T>(nullptr);
		height = 0;
		nil = new RBTNode<T>(nullptr);
		nil->color = RBT_BLACK;
		this->root = this->nil;
		//this->nil->parent = this->nil;
	}

	RBTree(const T& _root)
	{
		height = 0;
		nil = new RBTNode<T>(nullptr);
		nil->color = RBT_BLACK;
		this->root = this->nil;
		this->insert(_root);
	}

	~RBTree()
	{
		if (root != nullptr)
			delete root;
		if (nil != nullptr)
			delete nil;
	}

	int getHeight() const
	{
		return this->height;
	}

	void leftRotate(RBTNode<T> *x)
	{
		RBTNode<T> *y = x->right;
		x->right = y->left;
		if (y->left != this->nil)
			y->left->parent = x;
		y->parent = x->parent;
		if (x->parent == this->nil)
			this->root = y;
		else if (x == x->parent->left)
			x->parent->left = y;
		else
			x->parent->right = y;
		y->left = x;
		x->parent = y;
	}

	void rightRotate(RBTNode<T> *y)
	{
		RBTNode<T> *x = y->left;
		y->left = x->right;
		if (x->right != this->nil)
			x->right->parent = y;
		x->parent = y->parent;
		if (y->parent == this->nil)
			this->root = x;
		else if (y == y->parent->left)
			y->parent->left = x;
		else
			y->parent->right = x;
		x->right = y;
		y->parent = x;
	}

	void insert(const T& value)
	{
		RBTNode<T> *y = this->nil;
		RBTNode<T> *x = this->root;
		RBTNode<T> *z = nullptr;

		while (x != this->nil) {
			y = x;
			if (value < x->key)
				x = x->left;
			else
				x = x->right;
		}

		z = new RBTNode<T>(y, value);

		if (y == this->nil)
			this->root = z;
		else if (value < y->key)
			y->left = z;
		else
			y->right = z;

		z->left = this->nil;
		z->right = this->nil;
		z->color = RBT_RED;
		
		insertFixup(z);
		return;
	}

	void insertFixup(RBTNode<T>* z) {
		while (z->parent->color == RBT_RED) {
			if (z->parent == z->parent->parent->left) {
				RBTNode<T>* y = z->parent->parent->right;
				/* Case 1 */
				if (y->color == RBT_RED) {
					z->parent->color = RBT_BLACK;
					y->color = RBT_BLACK;
					z->parent->parent->color = RBT_RED;
					z = z->parent->parent;
					continue;
				}
				/* Case 2 */
				else if (z == z->parent->right) {
					z = z->parent;
					leftRotate(z);	/* Then it turns into case 3 */
				}
				/* Case 3 */
				z->parent->color = RBT_BLACK;
				if (z->parent->parent != nullptr) {
					z->parent->parent->color = RBT_RED;
					rightRotate(z->parent->parent);
				}
			}
			else if (z->parent == z->parent->parent->right) {
				RBTNode<T>* y = z->parent->parent->left;
				/* Case 1 */
				if (y->color == RBT_RED) {
					z->parent->color = RBT_BLACK;
					y->color = RBT_BLACK;
					z->parent->parent->color = RBT_RED;
					z = z->parent->parent;
					continue;
				}
				/* Case 2 */
				else if (z == z->parent->left) {
					z = z->parent;
					rightRotate(z);	/* Then it turns into case 3 */
				}
				/* Case 3 */
				z->parent->color = RBT_BLACK;
				if (z->parent->parent != nullptr) {
					z->parent->parent->color = RBT_RED;
					leftRotate(z->parent->parent);
				}
			} /* end if */ 
		} /* end while */
		this->root->color = RBT_BLACK;
	}

	unsigned int count(const T& value) const
	{
		if (root == this->nil) {
			return 0;
		}
		RBTNode<T> *p = this->root;
		unsigned int counter = 0;
		while (p != this->nil) {
			if (p->key == value) {
				counter += 1;
			}
			if (value < p->key) {
				p = p->left;
			} else {
				p = p->right;
			}
		}
		return counter;
	}

	void transplant(RBTNode<T>* z)
	{
		//TODO
	}

	void print(RBTNode<T> *subTree)
	{
		if (subTree->left != this->nil) {
			print(subTree->left);
		}
		std::cout << subTree->key << " ";
		if (subTree->right != this->nil) {
			print(subTree->right);
		}
		return;
	}

	void print()
	{
		this->print(this->root);
	}

private:
	RBTNode<T> *root;
	int height;
	RBTNode<T> *nil;
};

#endif