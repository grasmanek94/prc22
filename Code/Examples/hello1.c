#include <stdio.h>

int i;
int * p1 = &i;
int * p2 = &i;



int main(void)
{
	*p1 = 42;
	printf("hello world\n");
	printf("%d\n",i);
	return 0;
}