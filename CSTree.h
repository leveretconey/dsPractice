#pragma once
#include"BiTree.h"

typedef struct CSTreeNode
{
	int data;
	CSTreeNode *first_child, *next_subling;
}CSTreeNode,*CSTreePointer;
class CSTree
{
public:
	void CreateFromBiTree(BiTree *bi_tree);

	static const int MAX_NODE=100;
	static const int ROOT_FISRT_ORDER = 0;
	static const int ROOT_LAST_ORDER = 1;
	static const int ROOT_LAST_REVERSE_ORDER = 2;
	void ShowAllData(int order);
	int LeafCount();
	void CreateFromLevelDegree(int *level,int *degree,int length);
	CSTreePointer GetRoot();

	CSTree();
	~CSTree();
private:
	CSTreePointer root;
	static CSTreePointer CreateFromBiTreeRecursion(BiTreeNodePointer bi_tree_root);

	static void Traverse(CSTreePointer tree, int, int(*visit)(CSTreePointer));
	static void RootFisrtOrderTraverse(CSTreePointer tree, int(*visit)(CSTreePointer));
	static void RootLastOrderTraverse(CSTreePointer tree, int(*visit)(CSTreePointer));
	static void RootLastReverseOrderTraverse(CSTreePointer tree, int(*visit)(CSTreePointer));

	static int ShowNodeData(CSTreePointer Node);
	static int DeleteNode(CSTreePointer Node);
	static int LeafCountRecursion(CSTreePointer Node);
};
