/*
	Main assignment2a header file
*/

//Include Guard
#ifndef assignment2a_HEADER
#define assignment2a_HEADER

typedef struct
{
	int     StudentNumber;
	int     StudyCredits;
} STUDENT;

double GetAverageStudentCredits(STUDENT *arr, unsigned long len);
char * GetConsoleLine(void);
#endif