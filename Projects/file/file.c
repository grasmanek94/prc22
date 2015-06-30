/*
	Main file source file
*/

//Default includes
#include <stdio.h>
#include <string.h>
#include <math.h>

//Custom includes
#include "file.h"

extern long customfsize(FILE* fp);

int computeAverageStudyResults(char* FileName, double* Average)
/* pre    :
* post   : Calculates the average of all study results in a file
* returns: -1 if an error occurs, 0 if a valid average is computed
*/
{
	FILE* fptr = fopen(FileName, "rb");
	if (fptr == NULL || Average == NULL || FileName == NULL)
	{
		return -1;
	}

	int sum = 0;
	int index = 0;
	STUDENT student;

	while (readElement(fptr, index++, &student))
	{
		sum += student.StudyCredits;
	}

	if (index == 1)
	{
		return -1;
	}

	*Average = (double)sum / (double)--index;

	fclose(fptr);

	return 0;
}

int findElementLinear(FILE* fptr, int Number, STUDENT* StudentPtr)
{
	int index = 0;
	STUDENT student;
	while (readElement(fptr, index++, &student))
	{
		if (student.StudentNumber == Number)
		{
			if (StudentPtr != NULL)
			{
				memcpy(StudentPtr, &student, sizeof(STUDENT));
			}
			return 0;
		}
	}
	return -1;
}

int linearSearchStudentsFile(char* FileName, int Number, STUDENT* StudentPtr)
/* pre    :
* post   : Returns student information of student with student number Number
* returns: -1 if Number is not available or in case of an error, 0 if Number is available
*/
{
	FILE* fptr = fopen(FileName, "rb");
	if (fptr == NULL || FileName == NULL || StudentPtr == NULL)
	{
		return -1;
	}

	int ret = findElementLinear(fptr, Number, StudentPtr);

	fclose(fptr);
	return ret;
}

int binarySearchStudentsFile(char* FileName, int Number, STUDENT* StudentPtr)
/* pre    :
* post   : Returns student information of student with student number Number
* returns: -1 if Number is not available or in case of an error, 0 if Number is available
*/
{
	FILE* fptr = fopen(FileName, "rb");
	if (fptr == NULL || FileName == NULL || StudentPtr == NULL)
	{
		return -1;
	}

	STUDENT student;

	int first, last, middle, n, search;

	n = customfsize(fptr) / sizeof(STUDENT);
	first = 0;
	last = n - 1;
	middle = (first + last) / 2;
	search = Number;

	while (first <= last) 
	{
		if (readElement(fptr, middle, &student))
		{
			if (student.StudentNumber < search)
			{
				first = middle + 1;
			}
			else if (student.StudentNumber == search) 
			{
				//printf("%d found at location %d.\n", search, middle + 1);	
				memcpy(StudentPtr, &student, sizeof(student));
				break;
			}
			else
			{
				last = middle - 1;
			}
			middle = (first + last) / 2;
		}
		else
		{
			break;
		}
	}

	fclose(fptr);
	if (first > last)
	{
		//printf("Not found! %d is not present in the list.\n", search);
		return -1;
	}
	return 0;
}

int addStudentSortedToFile(char* FileName, STUDENT* StudentPtr)
/* pre    :
* post   : Adds information from StudentPtr to FileName in a sorted way,
*          if FileName does not exist, a new file is created.
* returns: -1 in case of an error
*          0  if a student with the given student number already exists
*          1  if the student is added to the file
*/
{
	if (FileName == NULL || StudentPtr == NULL)
	{
		return -1;
	}

	FILE* fptr = fopen(FileName, "rb");
	if (fptr == NULL)
	{
		return -1;
	}

	if (findElementLinear(fptr, StudentPtr->StudentNumber, NULL) == 0)
	{
		fclose(fptr);
		return 0;
	}

	FILE* tmp = tmpfile();
	if (tmp == NULL)
	{
		fclose(fptr);
		return -1;
	}

	#define writeElemFast(a) \
		if (writeElement(tmp, written++, a) != 0) \
		{ \
			fclose(fptr); \
			fclose(tmp); \
			return -1; \
		} \

	int written = 0;
	bool didwrite = false;
	int index = 0;
	STUDENT student;

	while (readElement(fptr, index++, &student))
	{
		if (!didwrite && student.StudentNumber > StudentPtr->StudentNumber)
		{
			didwrite = true;
			writeElemFast(StudentPtr);
		}
		writeElemFast(&student);
	}
	if (!didwrite)
	{
		writeElemFast(StudentPtr);
	}

	fclose(fptr);
	remove(FileName);
	fptr = fopen(FileName, "wb");
	if (fptr == NULL)
	{
		fclose(tmp);
		return -1;
	}
	fseek(tmp, 0, SEEK_SET);
	
	//copy contents of tmp to FileName
	int a;
	bool comp;
	do 
	{
		a = fgetc(tmp);
		comp = a != EOF;
		if (comp)
		{
			fputc(a, fptr);
		}
	} 
	while (comp);
	
	fclose(fptr);
	fclose(tmp);

	#undef writeElemFast
	return 1;
}

int removeStudentFromFile(char* FileName, int StudentNumber)
/* pre    :
* post   : Removes student with StudentNumber from file
* returns: 0 if StudentNumber was removed from file
*          -1 if StudentNumber was not found or an error occurs
*/
{
	FILE* tmp = tmpfile();
	if (tmp == NULL || FileName == NULL)
	{
		return -1;
	}

	FILE* fptr = fopen(FileName, "rb");
	if (fptr == NULL)
	{
		fclose(tmp);
		return -1;
	}

	int index = 0;
	int written = 0;
	STUDENT student;
	bool found = false;

	while (readElement(fptr, index++, &student))
	{
		if (student.StudentNumber != StudentNumber)
		{
			if (writeElement(tmp, written++, &student) != 0)
			{
				fclose(fptr);
				fclose(tmp);
				found = false;
				return -1;
			}
		}
		else
		{
			found = true;
		}
	}

	if (found)
	{
		fclose(fptr);
		remove(FileName);
		fptr = fopen(FileName, "wb");
		if (fptr == NULL)
		{
			fclose(tmp);
			return -1;
		}
		fseek(tmp, 0, SEEK_SET);

		//copy contents of tmp to FileName
		int a;
		bool comp;
		do {
			a = fgetc(tmp);
			comp = a != EOF;
			if (comp)
			{
				fputc(a, fptr);
			}
		} while (comp);

		fclose(fptr);
		fclose(tmp);

		return 0;
	}

	return -1;
}
