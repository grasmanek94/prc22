/*
	Main assignment1c source file
*/

//Default includes
#include <stdio.h>

//Custom includes
#include "main.h"
#include "assignment1c.h"

int main(void)
{
	typedef int array_type;
	array_type array[6] =
	{ 
		1, 2, 3, 4, 5, 6
	};
	for (array_type *i = array + sizeof(array) / sizeof(array_type) - 1; i >= array; --i)
	{
		printf("waarde: %d\n", *i);
	}
	return 0;
}
