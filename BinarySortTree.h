#pragma once
#include "BiTree.h"
class BinarySortTree :
	public BiTree
{

public:
	BiTreeNodePointer SearchNodeWithValue(int value);
	BiTreeNodePointer InsertNodeWithValue(int value);
	int DeleteBSTreeNodeWithValue(int value);
	
	int CreateBSTreeFromString(char *nodes_data);
	BiTreeNodePointer GetParent(BiTreeNodePointer child);

	int IsLegalBST();

	BinarySortTree();
	~BinarySortTree();

private:
};

