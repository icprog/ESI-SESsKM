#include "stdafx.h"
#include "Util.h"
void Util::initialize(char *arr1, char *arr2, int startIdx, int endIdx, int j)
{
	for (int i = startIdx, k = j; i < endIdx; i++, k++) {
		arr1[k] = arr2[i];
	}
}
