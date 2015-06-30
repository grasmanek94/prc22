#include <stdio.h>

int array[6] = {1,2,3,4,5,6};

int main(void)
{
	int* p = &array[5];
	int i = *p;
	for (i >= 0; i--;)
	{
    	printf("waarde: %d\n", array[i]);
	}
    return 0;
}