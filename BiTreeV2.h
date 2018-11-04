#pragma once
#include "BiTreeNode.h"

class BiTreeV2
{
public:
	static const int PRE_ORDER = 0;
	static const int IN_ORDER = 1;
	static const int POST_ORDER = 2;
	static const int LEVEL_ORDER = 3;
	static const int MAX_NODE = 1000;
	static const int NULL_NODE = -9999;

	void CreateFromArray(int *a, int length);
	void CreateFromString(char *nodes_value);
	void CreateFromPreInString(char *pre, char *in);

	void ShowAllData(int order = PRE_ORDER);

	BiTreeV2();
	~BiTreeV2();
protected:
	BiTreeNodePointer GetRoot();
private:
	BiTreeNodePointer root;

	void DestroyTreeRecursion(BiTreeNodePointer bnp);
	void ShowDataPreOrder();
	void ShowDataInOrder();
	void ShowDataPostOrder();
	void ShowDataLevelOrder();

};

