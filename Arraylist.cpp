#include "Arraylist.h"
#include <iostream>
#include "Heap.h"
#include "CycleQueue.h"
#include <Windows.h>
#pragma comment( lib,"winmm.lib" )
using namespace std;

int ArrayList::LocateElement(int element)
{
	int i;
	for (i = length - 1; i >= 0; i--)
		if (data[i] == element)
			return i;
	return -1;
}

int ArrayList::GetElement(int location)
{
	if (location<0 || location>=length)
		return ERROR;
	else
		return data[location];
}

int ArrayList::Insert(int location, int element)
{
	if (location<0 || location>length||IsFull())
		return ERROR;
	for (int i = length; i > location; i--)
		data[i ]= data[i - 1];
	data[location] = element;
	length++;
	return 0;
}

int ArrayList::Delete(int location)
{
	if (location<0 || location>=length)
		return ERROR;
	for (int i = location; i <length-1 ; i++)
		data[i] = data[i + 1];
	length--;
	return 0;
}

void ArrayList::Initialize()
{
	length = 0;
}

int ArrayList::ShowAll()
{
	if (IsEmpty())
		cout << "表为空";
	else
	{
		for (int i = 0; i < length; i++)
			cout << data[i] << " ";
		cout << endl;
	}
	return 0;
}

int ArrayList::IsEmpty()
{
	return length == 0;
}

int ArrayList::IsFull()
{
	return length == MAXSIZE;
}

int ArrayList::CreateFromString(char * list)
{
	length = 0;
	char *pointer = list;
	while (*pointer != '\0')
	{
		if (!IsFull())
			sscanf_s(pointer, "%d", &data[length++]);
		else
		{
			return -1;
		}
		while (*pointer == ' ')
			pointer++;
		while (*pointer != ' '&& *pointer != '\0')
			pointer++;
	}
	return 0;
}

int ArrayList::CreateInOrder(int list_length)
{
	if (list_length < 0|| list_length > MAXSIZE)
		return -1;
	length = list_length;
	for (int i = 0; i < length; i++)
		data[i] = i;
	return 0;
}

int ArrayList::CreateRandom(int list_length, int low, int high)
{
	if (list_length < 0 || list_length > MAXSIZE)
		return -1;
	length = list_length;
	srand((unsigned int)timeGetTime());
	for (int i = 0; i < length; i++)
		data[i] = low + rand() % (high - low);
	return 0;

	
}

void ArrayList::Shuffle()
{
	int i, p;
	srand((unsigned int)timeGetTime());
	for (i = 1; i < length; i++)//i循环令A[i]与a[p]交换，p属于[0,i]
	{
		p = rand() % (i + 1);
		std::swap(data[i], data[p]);
	}

}

inline int ArrayList::Smaller(int a, int b)
{
	return a < b;
}

inline int ArrayList::Greater(int a, int b)
{
	return a > b;
}
int ArrayList::IsSorted(int(*compare)(int, int))
{
	if (length < 2)
		return true;
	for (int i = 0; i < length-1; i++)
	{
		if (compare(data[i+1], data[i]))
			return false;
	}
	return true;
}

int ArrayList::IsSorted()
{
	return IsSorted(Smaller);
}

int ArrayList::Sort(int sort_method, int(*compare)(int, int))
{
	switch (sort_method)
	{
	case SORT_MONKEY:MonkeySort(compare); break;
	case SORT_INSERT:InsertSort(compare); break;
	case SORT_BINARY_INSERT:BinaryInsertSort(compare); break;
	case SORT_SHELL: ShellSort(compare);break;
	case SORT_BUBBLE: BubbleSort(compare); break;
	case SORT_QUICK: QuickSort(compare); break;
	case SORT_SELECT:SelectSort(compare); break;
	case SORT_DOUBLE_BUBBLE:DoubleBubbleSort(compare); break;
	case SORT_HEAP:HeapSort(); break;
	case SORT_GOBLIN:GoblinSort(compare); break;
	case SORT_MERGE:MergeSort(compare); break;
	case SORT_RADIX:RadixSort(); break;
	case SORT_COUNT:CountSort(compare); break;
	default:return 1;
	}
	return 0;
}

int ArrayList::Sort(int sort_method)
{
	return Sort(sort_method, Smaller);
}

ArrayList::ArrayList()
{
	length = 0;
}

ArrayList::ArrayList(char * list)
{
	CreateFromString(list);
}


ArrayList::~ArrayList()
{
}

void ArrayList::MonkeySort(int(*compare)(int, int))
{
	LONGLONG count = 0;
	while (!IsSorted(compare))
	{
		count++;
		Shuffle();
	}
}

void ArrayList::InsertSort(int(*compare)(int, int))
{
	int i, j, data_to_insert;
	for (i = 1; i < length; i++)
	{
		if (!compare(data[i - 1], data[i]))
		{
			//需要插入
			data_to_insert = data[i];
			for (j = i; j > 0&&compare(data_to_insert,data[j-1]); j--)
				data[j ] = data[j-1];
			data[j] = data_to_insert;
		}
		/*std::cout << "第 " << i << "次:";
		ShowAll();*/
	}
}

void ArrayList::BinaryInsertSort(int(*compare)(int, int))
{
	//折半插入
	int i, j, data_to_insert;
	int low, mid, high;
	for (i = 1; i < length; i++)
	{
		data_to_insert = data[i];
		low = 0; high = i - 1;
		while (low <= high)
		{
			mid = (low + high) / 2;
			if (compare(data[mid], data_to_insert))	
			    low = mid + 1;
			else
				high = mid - 1;
		}
		//low即为正确的位置
		for (j = i; j >low; j--)
			data[j ] = data[j-1];
		data[low] = data_to_insert;
		/*std::cout << "第 "<< i << "次:";
		ShowAll();*/
	}
}

void ArrayList::ShellSort(int(*compare)(int, int))
{
	int d, i, j, data_to_insert;
	for (d = length / 2; d > 0; d /= 2)
	{
		for (i = d; i < length; i++)
		{
			//将data[i]向前寻找正确的位置进行插入
			data_to_insert = data[i];
			if (compare(data_to_insert, data[i - d]))
			{
				for (j = i; j >= d &&compare(data_to_insert,data[j - d]);j-=d)
					data[j ]= data[j - d];
				data[j] = data_to_insert;
			}
		}
		/*std::cout << "增量为 " <<d << ":";
		ShowAll();*/
	}
}

void ArrayList::BubbleSort(int(*compare)(int, int))
{
	int i, j,swap_flag;
	for (i = 0; i < length-1; i++)
	{
		swap_flag = false;
		for (j = length - 1; j > i; j--)
		{
			if (compare(data[j], data[j - 1]))
			{
				std::swap(data[j], data[j - 1]);
				swap_flag = true;
			}
		}
		/*std::cout << "第 " << i+1 << "次:";
		ShowAll();*/
		if (!swap_flag)
			return;
	}
}

void ArrayList::QuickSort(int(*compare)(int, int))
{
	QuickSortRecursion(compare, 0, length - 1);
}

void ArrayList::SelectSort(int(*compare)(int, int))
{
	int i, j, selected;
	for (i = 0; i < length - 1; i++)
	{
		selected = i;
		for (j = i + 1; j < length; j++)
		{
			if (compare(data[j], data[selected]))
				selected = j;
		}
		std::swap(data[selected], data[i]);
		/*std::cout << "第 " << i + 1 << "次:";
		ShowAll();*/
	}
}

void ArrayList::HeapSort()
{
	Heap *heap = new Heap;
	heap->CreateFromArrayList(this);
	/*for (int i = length - 1; i >= 0; i--)
	{
		heap->Insert(data[i]);
	}
	*/
	for (int i = length - 1; i>=0;i--)
	{
		//heap->ShowAll();
		data[i] = heap->GetAndDeleteRoot();
	}
	delete heap;
}

void ArrayList::MergeSort(int(*compare)(int, int))
{
	MergeSortRecursion(compare,0, length - 1);
}

void ArrayList::RadixSort()
{
	CycleQueue queue[10];
	int max_digit_count=0,temp,digit,i,data_pointer;
	for (i = 0; i < length; i++)
	{
		temp = (int)log10(data[i]);
		if (temp > max_digit_count)
			max_digit_count = temp;
	}

	for (digit = 0; digit <= max_digit_count; digit++)
	{
		//分配
		for (i = 0; i < length; i++)
		{
			temp = GetDigit(data[i], digit);
			queue[temp].EnQueue(data[i]);
		}
		//收集
		data_pointer = 0;
		for (i = 0; i < 10; i++)
		{
			while (!queue[i].IsEmpty())
				queue[i].DeQueue(data[data_pointer++]);
		}
	}
}

void ArrayList::GoblinSort(int(*compare)(int, int))
{
	int *pointer = data;
	while (pointer != data + length)
	{
		if (pointer == data || !compare(*pointer, *(pointer - 1)))
			pointer++;
		else
		{
			swap(*pointer, *(pointer - 1));
			pointer--;
		}
	}
}

void ArrayList::DoubleBubbleSort(int(*compare)(int, int))
{
	int low = 0, high = length - 1,i;
	while (low < high)
	{
		for (i = low; i < high; i++)
		{
			if (compare(data[i + 1], data[i]))
				swap(data[i], data[i + 1]);
		}
		high--;
		for (i = high; i > low; i--)
		{
			if (compare(data[i], data[i-1]))
				swap(data[i], data[i - 1]);
		}
		low++;
		/*std::cout << "第 " << i + 1 << "次:";
		ShowAll();*/
	}
}

void ArrayList::CountSort(int(*compare)(int, int))
{
	int a[MAXSIZE];
	int i,j, count;
	for (i = 0; i < length; i++)
	{
		a[i] = data[i];
	}
	for (i = 0; i < length; i++)
	{
		count = 0;
		for (j = 0; j < length; j++)
		{
			if (compare(a[j], a[i]))
				count++;
		}
		data[count] = a[i];
	}
}

int ArrayList::SortQuickPartition(int(*compare)(int, int), int low, int high)
{
	int pivot = data[low];
	while (low < high)
	{
		while (low < high && !compare(data[high], pivot))//pivot<=data[high],注意要取等
			high--;
		data[low] = data[high];
		while (low < high && !compare(pivot, data[low]))//data[low]<=pivot
			low++;
		data[high] = data[low];
	}
	data[low] = pivot;
	return low;

}

void ArrayList::QuickSortRecursion(int(*compare)(int, int), int low, int high)
{
	if (low < high)
	{
		int mid = SortQuickPartition(compare,low, high);
		QuickSortRecursion(compare, low, mid - 1);
		QuickSortRecursion(compare, mid + 1, high);
	}
}

void ArrayList::MergeSortRecursion(int(*compare)(int, int),int low, int high)
{
	if (low < high)
	{
		int mid = low + (high - low) / 2;
		MergeSortRecursion(compare, low, mid);
		MergeSortRecursion(compare, mid + 1, high);
		Merge(compare, low, mid, high);
	}
}

void ArrayList::Merge(int(*compare)(int, int),int low, int mid, int high)
{
	int *a = new int[length];
	int a_pointer = low, low_pointer = low, mid_pointer = mid+1;

	while (a_pointer <= high)
	{
		a[a_pointer] = data[a_pointer];
		a_pointer++;
	}
	a_pointer = low;

	while (low_pointer <= mid && mid_pointer <= high)
	{
		if (compare(a[low_pointer], a[mid_pointer]))
			data[a_pointer++] = a[low_pointer++];
		else
			data[a_pointer++] = a[mid_pointer++];
	}

	while(low_pointer<=mid) 
		data[a_pointer++] = a[low_pointer++];
	while(mid_pointer<=high)
		data[a_pointer++] = a[mid_pointer++];
	delete a;
	/*cout << "从" << low << "到" << high << "归并的结果：";
	ShowAll();*/
}

int ArrayList::GetDigit(int number, int position)
{
	if (number == 0)
		return 0;
	int product = 1;
	for (int i = 1; i <= position; i++)
		product *= 10;
	return (number / product) % 10;
}






