#pragma once
#include "BiTree.h"

typedef struct ThreadBiTreeNode
{
	int data;
	ThreadBiTreeNode *lchild, *rchild;
	int ltag, rtag;
} *ThreadBiTreePointer;
class ThreadBiTree
{
public:
	void ShowInfoPreOrder();
	void CreateFromBiTree(BiTree &);
	void MakeInThread();

	ThreadBiTree();
	~ThreadBiTree();
	

private:
	ThreadBiTreePointer root;

	static const int CHILD = 1;
	static const int THREAD = 2;

	static void ShowNodeInfoPreOrder(ThreadBiTreePointer);
	static void CopyNode(BiTreeNodePointer origin, ThreadBiTreePointer copier);
	static void InThread(ThreadBiTreePointer, ThreadBiTreePointer &);
};

