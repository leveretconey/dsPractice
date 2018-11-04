#pragma once
#define GetDpeth GetHeight
#include "BiTreeNode.h"

class BiTree
{
public:
	static const int MAX_NODE = 1000;

	static const int NULL_NODE = -9999;
	void CreateFromArray(int *a,int length);
	void CreateFromString(char *nodes_value);
	void CreateFromPreInString(char *pre, char *in);
	static BiTreeNodePointer CreateFromPreInStringRecursion(int *pre, int *in, int length);

	static const int PRE_ORDER = 0;
	static const int IN_ORDER = 1;
	static const int POST_ORDER = 2;
	static const int LEVEL_ORDER = 3;
	static const int NO_RECURSION = 4;
	static const int LEVEL_ORDER_REVERSE = 8;
	static const int TABLE_FORMAT = 9;
	void ShowAllData(int order= PRE_ORDER);
	void ReverseBiTree();
	void ShowAllDataLevelV2();

	BiTreeNodePointer GetRoot() { return root; };
	void SetRoot(BiTreeNodePointer node) { root = node; };


	static int GetHeight(BiTreeNodePointer root);
	int GetHeightV2();
	int IsComleteBiTree();
	int GetKthNodePreOrder(int k);
	int GetWidth();
	void ShowNodeAncestors(int node_value);
	int GetWeightedPathLength();
	BiTreeNodePointer GetParent(BiTreeNodePointer node_to_search);

	static BiTreeNodePointer CreateNewNode(int data);
	static int DeleteNode(BiTreeNodePointer Node);
	static int ShowNodeData(BiTreeNodePointer Node);
	static int ReverseChilds(BiTreeNodePointer Node);
	static void StringToArray(char *input, int *arr, int &length);
	static int CountOfChildren(BiTreeNodePointer root);
	static int BreakLink(BiTreeNodePointer parent, BiTreeNodePointer child);

	static void Traverse(BiTreeNodePointer tree, int, int(*visit)(BiTreeNodePointer));

	BiTree();
	~BiTree();
private:
	BiTreeNodePointer root;

	void ShowInTable();
	static void PreOrderTraverse(BiTreeNodePointer tree,int (*visit)(BiTreeNodePointer));
	static void InOrderTraverse(BiTreeNodePointer tree, int(*visit)(BiTreeNodePointer));
	static void PostOrderTraverse(BiTreeNodePointer tree, int(*visit)(BiTreeNodePointer));
	static void LevelOrderTraverse(BiTreeNodePointer tree, int(*visit)(BiTreeNodePointer));
	static void PreOrderTraverseNoRecursion(BiTreeNodePointer tree, int(*visit)(BiTreeNodePointer));
	static void InOrderTraverseNoRecursion(BiTreeNodePointer tree, int(*visit)(BiTreeNodePointer));
	static void PostOrderTraverseNoRecursion(BiTreeNodePointer tree, int(*visit)(BiTreeNodePointer));
	static void LevelOrderReverseTraverse(BiTreeNodePointer tree, int(*visit)(BiTreeNodePointer));
};
typedef BiTree *BiTreeP;