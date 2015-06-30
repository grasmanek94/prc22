#include <stdio.h>

void timesTwo(int*);
void timesTwoWrong(int);

int main(void)
{
	int i = 10;
	int* p = &i;    
    *p += 1;

    printf("waarde van i: %d\n", i);
    printf("adres van i : %p\n\n", &i);

    printf("waarde van p: %p\n", p);
    printf("adres van p : %p\n", &p);
    printf("waar p naar wijst: %d\n", *p);

    timesTwo(&i);  // of: timesTwo(p);
    timesTwoWrong(i);
    printf("\nterug in main:\n");
    printf("waarde van i: %d\n", i);

    return 0;
}

void timesTwo(int* p)
{
	printf("\nTimesTwo\n");
	printf("waarde p: %p\n", p);
    printf("adress p: %p\n", &p);
    printf("waar p naar wijst: %d\n", *p);
    *p *= 2;
}

void timesTwoWrong(int p)
{
    printf("\nTimesTwoWrong\n");
	printf("waarde p: %p\n", p);
    printf("adress p: %p\n", &p);
    p *= 2;
}