#include "RBTree.h"
#include <iostream>
#include <fstream>

using namespace leveretconey;
using namespace std;

RBTreeNodePointer leveretconey::RBTree::getNewNode(Color color, 
	int key,RBTreeNodePointer parent)
{
	RBTreeNodePointer node=new RBTreeNode();
	node->color = color; 
	node->key = key;
	node->left = node->right = nil;
	node->parent = parent;
	return node;
}
void leveretconey::RBTree::deleteNode(RBTreeNodePointer node)
{
	if (node != nil) {
		deleteNode(node->left);
		deleteNode(node->right);
		delete node;
	}
}
void leveretconey::RBTree::rotateLeft(RBTreeNodePointer node)
{
	//为了方便起见，就不去检查参数了
	//默认 node->right!=nil
	RBTreeNodePointer x=node,xp = node->parent, xr = node->right, xrl = xr->left;
	if (x == root) {
		root = xr;
		xr->parent = nil;
	}
	else {
		xr->parent = xp;
		if (x == xp->left)
			xp->left = xr;
		else
			xp->right = xr;
	}
	x->parent = xr;
	xr->left = x;
	x->right = xrl;
	if (xrl != nil) {
		xrl->parent = x;
	}
}
void leveretconey::RBTree::rotateRight(RBTreeNodePointer node)
{
	RBTreeNodePointer x = node, xp = node->parent, xl = node->left, xlr = xl->right;
	if (x == root) {
		root = xl;
		xl->parent = nil;
	}
	else {
		xl->parent = xp;
		if (x == xp->left)
			xp->left = xl;
		else
			xp->right = xl;
	}
	x->parent = xl;
	xl->right = x;
	x->left = xlr;
	if (xlr != nil) {
		xlr->parent = x;
	}
}
void leveretconey::RBTree::adjustInsert(RBTreeNodePointer node)
{
	while (true) {
		if (root == node)
		{
			node->color = BLACK;
			return;
		}
		if (node->parent->color == BLACK) {
			return;
		}
		if (node->parent == node->parent->parent->left) {
			//case 1
			RBTreeNodePointer uncle = node->parent->parent->right;
			if (uncle->color == RED) {
				uncle->color = node->parent->color = BLACK;
				uncle->parent->color = RED;
				node = uncle->parent;
			}
			else {
				//case 2
				if (node->parent->right == node) {
					node = node->parent;
					rotateLeft(node);
				}
				//case 3
				node->parent->color = BLACK;
				node->parent->parent->color = RED;
				rotateRight(node->parent->parent);
			}
		}
		else {
			//case 1
			RBTreeNodePointer uncle = node->parent->parent->left;
			if (uncle->color == RED) {
				uncle->color = node->parent->color = BLACK;
				uncle->parent->color = RED;
				node = uncle->parent;
			}
			else {
				//case 2
				if (node->parent->left == node) {
					node = node->parent;
					rotateRight(node);
				}
				//case 3
				node->parent->color = BLACK;
				node->parent->parent->color = RED;
				rotateLeft(node->parent->parent);
			}
		}
	}
}
void leveretconey::RBTree::traversePre(RBTreeNodePointer node, void(*callback)(RBTreeNodePointer))
{
	if (node != nil) {
		callback(node);
		traversePre(node->left,callback);
		traversePre(node->right,callback);
	}
}
void leveretconey::RBTree::traverseIn(RBTreeNodePointer node, void(*callback)(RBTreeNodePointer))
{
	if (node != nil) {
		traverseIn(node->left, callback);
		callback(node);
		traverseIn(node->right, callback);
	}
}
void leveretconey::RBTree::traversePost(RBTreeNodePointer node, void(*callback)(RBTreeNodePointer))
{
	if (node != nil) {
		traversePost(node->left, callback);
		traversePost(node->right, callback);
		callback(node);
	}
}
void leveretconey::RBTree::insert(int key)
{
	RBTreeNodePointer p = root, pp = nil;
	while(p != nil) {
		pp = p;
		if (p->key == key) {
			return;
		}
		else if (p->key < key) {
			p = p->right;
		}
		else {
			p = p->left;
		}
	}
	RBTreeNodePointer newNode = getNewNode(RED, key, pp);
	if ( pp== nil)
	{
		root = newNode;
	}
	else {
		if (key < pp->key)
			pp->left = newNode;
		else
			pp->right = newNode;
	}
	adjustInsert(newNode);
}

void printNode(RBTreeNodePointer node) {
	cout << " " << node->key << "(" << node->color << ") ";
}
void leveretconey::RBTree::show()
{
	cout << "[";
	traverse(PRE, printNode);
	cout << "]\n";
	//cout << "[";
	//traverse(IN, printNode);
	//cout << "]\n";
}
RBTreeNodePointer leveretconey::RBTree::getNil()
{
	return nil;
}
void leveretconey::RBTree::del(int key)
{
	RBTreeNodePointer node = search(key);
	del(node);
}
void leveretconey::RBTree::del(RBTreeNodePointer node)
{
	if (node == nil) {
		return;
	}

}
RBTreeNodePointer leveretconey::RBTree::search(int key)
{
	RBTreeNodePointer node = this->root;
	while (node != nil) {
		if (node->key == key) {
			return node;
		}
		else if (node->key > key) {
			node = node->left;
		}
		else {
			node = node->right;
		}
	}
	return nil;
}
void leveretconey::RBTree::traverse(TraverseType type, void(*callback)(RBTreeNodePointer))
{
	switch (type)
	{
	case leveretconey::PRE:
		traversePre(root, callback);
		break;
	case leveretconey::IN:
		traverseIn(root, callback);
		break;
	case leveretconey::POST:
		traversePost(root, callback);
		break;
	default:
		break;
	}
}
void leveretconey::RBTree::createFromFile(string path)
{
	ifstream file;
	file.open(path, ios::in);
	if (!file) {
		cout << "文件读取错误";
		return;
	}
	int key;
	while (file >> key) {
		this->insert(key);
	}
	file.close();
	cout << "创建完成";
	this->show();
}
RBTree::RBTree()
{
	nil = new RBTreeNode;
	nil->color = BLACK;
	root = nil;
}


RBTree::~RBTree()
{
	deleteNode(root);
	delete nil;
}

