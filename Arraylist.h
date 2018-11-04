#pragma once
#include "List.h"
class ArrayList :
	public List
{
public:
	//创建类函数
	int CreateFromString(char *list);
	int CreateInOrder(int list_length);
	int CreateRandom(int list_length, int low,int high);
	void Shuffle();

	//线性表基本操作
	const static int MAXSIZE = 9999;
	const static int ERROR = 0x7FFFFFFF;
	int LocateElement(int element);
	int GetElement(int location);
	int Insert(int location,int element);
	int Delete(int location);
	void Initialize();
	int ShowAll();
	int IsEmpty();
	int IsFull();

	//排序相关函数
	static int Smaller(int a, int b);
	static int Greater(int a, int b);
	int IsSorted(int(*compare)(int, int));
	int IsSorted();

	static const int SORT_MONKEY = 0;
	static const int SORT_COUNT=1;
	static const int SORT_INSERT= 2;
	static const int SORT_BINARY_INSERT = 3;
	static const int SORT_SHELL = 4;
	static const int SORT_BUBBLE = 5;
	static const int SORT_QUICK = 6;
	static const int SORT_SELECT = 7;
	static const int SORT_DOUBLE_BUBBLE =8;
	static const int SORT_HEAP = 9;
	static const int SORT_MERGE = 10;
	static const int SORT_RADIX = 11;
	static const int SORT_GOBLIN = 12;

	int Sort(int sort_method, int(*compare)(int, int));
	int Sort(int sort_method);
	//构造与析构
	ArrayList();
	ArrayList(char *list);
	~ArrayList();
protected:
	int data[MAXSIZE];
	void MonkeySort(int(*compare)(int, int));
	void InsertSort(int(*compare)(int, int));
	void BinaryInsertSort(int(*compare)(int, int));
	void ShellSort(int(*compare)(int, int));
	void BubbleSort(int(*compare)(int, int));
	void DoubleBubbleSort(int(*compare)(int, int));
	void QuickSort(int(*compare)(int, int));
	void SelectSort(int(*compare)(int, int));
	void HeapSort();
	void MergeSort(int(*compare)(int, int));
	void RadixSort();
	void GoblinSort(int(*compare)(int, int));
	void CountSort(int(*compare)(int, int));
private:
	int SortQuickPartition(int(*compare)(int, int), int low, int high);
	void QuickSortRecursion(int(*compare)(int, int),int low,int high);
	void MergeSortRecursion(int(*compare)(int, int),int low, int high);
	void Merge(int(*compare)(int, int),int low, int mid, int high);
	static int GetDigit(int number, int position);
};

