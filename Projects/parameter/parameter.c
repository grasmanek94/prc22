/*
	Main parameter source file
*/

//Default includes
#include <stdio.h>

//Custom includes
#include "parameter.h"

void SwapValues(int *a, int *b)
{
	if (a && b)
	{
		*a = *a + *b;
		*b = *a - *b;
		*a = *a - *b;
	}
}

int GetSumReturn(int arr[], int len)
{
	int sum = 0;
	if (len > 0 && arr)
	{
		for (int i = 0; i < len; ++i)
		{
			sum += arr[i];
		}
	}
	return  sum;
}

void GetSumParameter(int *arr, int len, int *sum)
{	
	if (arr && sum && len > 0)
	{
		*sum = 0;
		for (int to = (int)(long)arr + len * sizeof(int); (int)(long)arr < to; ++arr)
		{
			*sum += *arr;
		}
	}
}

void ArrayAdd(int *arr_in_1, int *arr_in_2, int len, int *arr_out)
{
	if (arr_in_1 && arr_in_2 && arr_out && len > 0)
	{
		for (int i = 0; i < len; ++i)
		{
			arr_out[i] = arr_in_1[i] + arr_in_2[i];
		}
	}
}