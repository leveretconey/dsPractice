#include "ThreadBiTree.h"
#include <iostream>

void ThreadBiTree::CopyNode(BiTreeNodePointer origin,ThreadBiTreePointer copier)
{
	ThreadBiTreePointer p;
	if (origin->lchild != NULL)
	{
		p = new ThreadBiTreeNode;
		copier->lchild = p;
		copier->ltag = ThreadBiTree::CHILD;
		p->lchild = NULL;
		p->rchild = NULL;
		p->data = origin->lchild->data;
		CopyNode(origin->lchild, p);
	}
	if (origin->rchild != NULL)
	{
		p = new ThreadBiTreeNode;
		copier->rchild = p;
		copier->rtag = ThreadBiTree::CHILD;
		p->lchild = NULL;
		p->rchild = NULL;
		p->data = origin->rchild->data;
		CopyNode(origin->rchild, p);
	}
}
ThreadBiTree::ThreadBiTree()
{
	root = NULL;
}


ThreadBiTree::~ThreadBiTree()
{
}

void ThreadBiTree::CreateFromBiTree(BiTree &t)
{
	BiTreeNodePointer troot = t.GetRoot();
	if (troot != NULL)
	{
		root = new ThreadBiTreeNode;
		root->data = troot->data;
		root->lchild = NULL;
		root->rchild = NULL;
		CopyNode(troot,root);
	}
}

void ThreadBiTree::MakeInThread()
{
	if (root != NULL)
	{
		/*
		ThreadBiTreePointer p=root,pre;
		while (p->lchild != NULL) 
			p = p->lchild;
		p->lchild = NULL;
		p->ltag = THREAD;
		pre = p;
		InThread(p, pre);
		pre->rchild = NULL;
		pre->rtag = THREAD;*/

		ThreadBiTreePointer pre = NULL;
		InThread(root, pre);
		pre->rtag = THREAD;
		pre->rchild = NULL;
	}
}

void ThreadBiTree::InThread(ThreadBiTreePointer p, ThreadBiTreePointer &pre)
{
	if (p != NULL)
	{
		if(p->lchild!=NULL)InThread(p->lchild, pre);
		if (p->lchild == NULL)
		{
			p->lchild = pre;
			p->ltag = THREAD;
		}
		if (pre!=NULL && pre->rchild == NULL)
		{
			pre->rchild = p;
			pre->rtag = THREAD;
		}
		pre = p;
		if (p->rchild != NULL)InThread(p->rchild, pre);
	}
}

void ThreadBiTree::ShowInfoPreOrder()
{
	ShowNodeInfoPreOrder(root);
}

void ThreadBiTree::ShowNodeInfoPreOrder(ThreadBiTreePointer p)
{
	if (p != NULL)
	{
		std::cout << p << '\t';
		std::cout << p->data << '\t' << p->ltag << '\t' << p->lchild << '\t';
		std::cout << p->rtag << '\t' << p->rchild << '\t'<<std::endl;
		if (p->ltag != THREAD)
	    	ShowNodeInfoPreOrder(p->lchild);
		if (p->rtag!= THREAD)
			ShowNodeInfoPreOrder(p->rchild);
	}
}