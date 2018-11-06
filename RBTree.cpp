#include "RBTree.h"
#include <iostream>

using namespace leveretconey;
RBTreeNodePointer leveretconey::RBTree::getNewNode(Color color, int key)
{
	RBTreeNodePointer node=new RBTreeNode();
	node->color = color;
	node->key = key;
	return node;
}
void leveretconey::RBTree::deleteNode(RBTreeNodePointer node)
{
	if (node != nullptr) {
		deleteNode(node->left);
		deleteNode(node->right);
		delete node;
	}
	
}
RBTree::RBTree()
{
	nil = getNewNode(BLACK, 0);
	root = nullptr;
}


RBTree::~RBTree()
{
	deleteNode(root);
	deleteNode(nil);
}

