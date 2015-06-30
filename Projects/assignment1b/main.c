/*
	Main assignment1b source file
*/

//Default includes
#include <stdio.h>

//Custom includes
#include "main.h"
#include "assignment1b.h"

int main(void)
{
	//define integer named 'i'
	int i;//uninitialised value so it will contain data that is currently at the memory location

	//define pointers 'p1' and 'p2' both pointing to integer 'i'
	int
		*p1 = &i;

	//Change value of 'i' using 'p1'
	*p1 = 69;

	//Print value of 'i' using 'p2', also add a carriage return at the end of the string
	//printf("%i\r\n", *p2);

	timesTwo(&i);  // of: timesTwo(p);
	printf("\nterug in main:\n");
	printf("waarde van i: %d\n", i);

	//I expect the value of 'i' to become 69*2 (138) and be printed like that to the console too
	//What happens? What I expect happens

	return 0;
}
