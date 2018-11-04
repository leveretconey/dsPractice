#include "SearchAndMatch.h"
#include <iostream>

int BinarySearch(ArrayList *al, int element)
{
	int low = 0, high = al->GetLength() - 1;
	int mid;
	while (low <= high)
	{
		mid = (low + high) / 2;
		if (al->GetElement(mid) == element)
			return mid;
		if (al->GetElement(mid) < element)
			low = mid + 1;
		else
			high = mid - 1;
	}
	return -1;
}

int PatternMatching(char * text, char * pattern)
{
	int i=0, j=0;
	int text_length = strlen(text), pattern_length = strlen(pattern);
	while (i != text_length && j != pattern_length)
	{
		if (text[i] == pattern[j])
		{
			i++;
			j++;
		}
		else
		{
			i = i - j + 1;
			j = 0;
		}
	}
	if (j == pattern_length)
		return i - j;
	else
		return -1;
}

int KMPPatternMatching(char * text, char * pattern)
{
	int *next = KMPGetNext(pattern);
	int i , j = -1;
	int text_length = strlen(text), pattern_length = strlen(pattern);
	for (i = 0; i < text_length; i++)
	{
		while (!(j == -1 || text[i] == pattern[j + 1]))
			j = next[j];
		if(text[i] == pattern[j + 1])
		{
		    j++;
        }
		if (j == pattern_length-1)//注意这个减一
		{
			delete next;
			return i-j;
		}
	}
	delete next;
	return -1;
}

int * KMPGetNext(char *pattern)
{//这里我以算法笔记中的next数组算法为准，即next[0]=-1，如果找不到匹配的前缀则next也为-1
//next[i]表示从头到本字符(算上自己)的最大的前缀等于后缀的长度减1,(有的版本是不算自己的最大长度)
//例如对于"ababa"则next数组为 -1 -1 0 1 2

	int pattern_length = strlen(pattern);
	int *next = new int[pattern_length];
	int i,j=-1;
	next[0] = -1;
	for (i = 1; i < pattern_length; i++)
	{
		while (!(j == -1 || pattern[i] == pattern[j + 1]))
			j = next[j];
		if(pattern[i] == pattern[j + 1])
		{
			j++;
        }
		next[i] = j;
	}
	return next;
}
