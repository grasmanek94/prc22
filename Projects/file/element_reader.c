/*
	Main file source file
*/

//Default includes
#include <stdio.h>

//Custom includes
#include "element_reader.h"

extern long customfsize(FILE* fp);

int readElement(FILE* FilePtr, int ElementNr, STUDENT* StudentPtr)
/* pre    :
* post   : If file contains enough elements, element 'ElementNr' is read into StudentPtr
* returns: On succes: 1 (1 element was read)
*          If element does not exist: 0
*          In case of an error (file could not be read, input pointers are NULL): -1
*/
{
	long bytes = ElementNr * sizeof(STUDENT);

	if (FilePtr == NULL || StudentPtr == NULL)
	{
		return -1;
	}

	if (customfsize(FilePtr) < (bytes + sizeof(STUDENT)) || fseek(FilePtr, bytes, SEEK_SET) != 0)
	{
		return 0;
	}

	if (fread(StudentPtr, sizeof(STUDENT), 1, FilePtr) != 1)
	{
		return -1;
	}

	return 1;
}

int writeElement(FILE* FilePtr, int ElementNr, const STUDENT* StudentPtr)
/* pre    :
* post   : Element 'ElementNr' is written into file with data from StudentPtr
* returns: On succes: 0
*          In case of an error (file could not be written, input pointers are NULL): -1
*/
{
	long bytes = ElementNr * sizeof(STUDENT);

	if (FilePtr == NULL || fseek(FilePtr, bytes, SEEK_SET) != 0 || StudentPtr == NULL)
	{
		return -1;
	}
	
	if (fwrite(StudentPtr, sizeof(STUDENT), 1, FilePtr) != 1)
	{
		return -1;
	}

	return 0;
}

long customfsize(FILE* fp)
{
	if (fp == NULL)
	{
		return 0;
	}
	long curr = ftell(fp);
	fseek(fp, 0L, SEEK_END);
	long size = ftell(fp);
	fseek(fp, curr, SEEK_SET);

	return size;
}