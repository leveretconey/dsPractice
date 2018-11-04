#pragma once
#include "Arraylist.h"

int BinarySearch(ArrayList *al, int element);
int PatternMatching(char *text, char *pattern);
int KMPPatternMatching(char *text, char *pattern);
static int *KMPGetNext(char *pattern);