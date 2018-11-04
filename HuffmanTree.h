#pragma once
#include "BiTree.h"
class HuffmanTree :
	public BiTree
{
public:
	int CreateFromWeightString(char *weights_string);
	int ShowHuffanCode(int weight_to_find);
	HuffmanTree();
	~HuffmanTree();
};

