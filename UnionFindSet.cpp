#include "UnionFindSet.h"



UnionFindSet::UnionFindSet()
{
	Initialize();
}


UnionFindSet::~UnionFindSet()
{
}

void UnionFindSet::Initialize()
{
	for (int i = 0; i < MAX_SIZE; i++)
	{
	    father[i] = -1;
	}
}

int UnionFindSet::FindSet(int element_to_find)
{
	while (father[element_to_find] >= 0)
		element_to_find = father[element_to_find];
	return element_to_find;
}


void UnionFindSet::Union(int element1, int element2)
{
	int root1 = FindSet(element1);
	int root2 = FindSet(element2);
	if (root1 != root2)
		father[root1] = root2;
}
