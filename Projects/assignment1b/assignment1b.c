/*
	Main assignment1b source file
*/

//Default includes
#include <stdio.h>

//Custom includes
#include "main.h"
#include "assignment1b.h"

void timesTwo(int* p)
{
	printf("\nin functie: %s\n", __FUNCTION__);
	printf("Address of ptr 'p': %08X\n", (unsigned int)((long)&p));
	printf("Value of ptr 'p': %08X\n", (unsigned int)((long)p));
	printf("Dereferenced Value of ptr 'p' before *2: %i\n", *p);
	*p *= 2; // datgene waar p naar wijst
	printf("Dereferenced Value of ptr 'p' after *2: %i\n", *p);
}

void timesTwoWrong(int p)
{
	/*
		The problem with this function is that you pass a integer variable p
		as a copy of the original input variable, so you cannot modify
		the original variable, this means that the multiplication
		will not emerge outside the scope of this function

		If you run:

			int main(void)
			{
				int i = 10;
				timesTwoWrong(i);
				printf("%i", i);
				return 0;
			}

		It will print '10'.

		~Rafal Grasman
	*/
	printf("\nin functie: %s\n", __FUNCTION__);
	printf("Value of 'p': %i\n", p);
	p *= 2;
	printf("Value of 'p' after *2: %i\n", p);
}
