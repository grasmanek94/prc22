/*
	Main parameter source file
*/

//Default includes
#include <stdio.h>

//Custom includes
#include "parameter.h"

int main(void)
{
	int i = 10;
	int j = 11;
	SwapValues(&i, &j);
	printf("i = %i == 11; j = %i == 10\n", i, j);

	int a[] = { 10, 20, 30, 40 };
	int result = GetSumReturn(a, 4);

	printf("result = %i == 100;\n", result);

	int b[] = { 10, 20, 30, 40 };
	int result2 = 0;
	GetSumParameter(b, 3, &result2);

	printf("result2 = %i == 60;\n", result2);

	int a1[] = { 10, 20, 30, 40 };
	int a2[] = { 1, 2, 3, 4 };
	int result3[4];
	ArrayAdd(a1, a2, 4, result3);

	printf(
		"result3[0] = %i == 11;\n\
result3[1] = %i == 22;\n\
result3[2] = %i == 33;\n\
result3[3] = %i == 44;\n",
		   result3[0], 
		   result3[1], 
		   result3[2], 
		   result3[3]
	);
	return 0;
}
