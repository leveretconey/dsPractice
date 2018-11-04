#pragma once
class UnionFindSet
{
public:
	static const int MAX_SIZE = 100;

	void Initialize();
	int FindSet(int element_to_find);
	void Union(int element1, int element2);

	UnionFindSet();
	~UnionFindSet();
private:
	int father[MAX_SIZE];
};

