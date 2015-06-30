/*
	Main assignment2a source file
*/

//Default includes
#include <stdio.h>
#include <stdlib.h>

//Custom includes
#include "main.h"
#include "assignment2a.h"

double GetAverageStudentCredits(STUDENT *arr, unsigned long len)
{
	if (len == 0)
	{ 
		return 0;
	}
	int sum = 0;

	for (int to = (int)(long)arr + len * sizeof(int); (int)(long)arr < to; ++arr)
	{
		sum += (*arr).StudyCredits;
	}
	return (double)sum / (double)len;
}

char * GetConsoleLine(void) 
{
	char * line = (char*)malloc(255), *linep = line;
	size_t lenmax = 255, len = lenmax;
	int c;

	if (line == NULL)
	{
		return NULL;
	}

	while (1)
	{
		c = fgetc(stdin);
		if (c == EOF)
		{
			break;
		}

		if (--len == 0) 
		{
			len = lenmax;
			char * linen = (char*)realloc(linep, lenmax *= 2);

			if (linen == NULL) 
			{
				free(linep);
				return NULL;
			}

			line = linen + (line - linep);
			linep = linen;
		}

		if ((*line++ = c) == '\n')
		{
			break;
		}
	}
	*line = '\0';

	return linep;
}