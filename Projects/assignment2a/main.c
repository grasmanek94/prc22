/*
	Main assignment2a source file
*/

//Default includes
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

//Custom includes
#include "main.h"
#include "assignment2a.h"

STUDENT students[5] =
{
	{ 1, 10 },
	{ 2, 20 },
	{ 3, 30 },
	{ 4, 20 },
	{ 5, 10 }
};

int main(void)
{
	int entries = sizeof(students) / sizeof(STUDENT);

	int currentStudentIndex = 0;

	do
	{
		printf("StudyCredits for student %d: ", students[currentStudentIndex].StudentNumber);

		char * line = GetConsoleLine();
		char * end;

		int inputCredit = strtol(line, &end, 10);

		//Use free ONLY after this comparision
		bool check_success = *end == '\n' && line != end;

		free(line);

		if (check_success)
		{
			//success
			students[currentStudentIndex].StudyCredits = inputCredit;	
		}
		else
		{
			//error
			printf("Invalid input, proceeding with default values...\n");
			break;
		}
	} while (++currentStudentIndex < entries);

	printf("Average Study Credits for all (%d) students: %.2f", entries, GetAverageStudentCredits(students, entries));
	return 0;
}
