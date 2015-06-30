/*
	Main file test file
*/

//Default includes
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

//Unit testin includes
#include "unity.h"

//Custom includes
#include "file.h"

STUDENT students[7];
int amountStudents = 0;

char* test_file = "file_test.data";

void CreateStudent(char* studentName, int studentNumber, int studyCredits)
{
	if (amountStudents < (sizeof(students) / sizeof(STUDENT)))
	{
		students[amountStudents].StudentNumber = studentNumber;
		students[amountStudents].StudyCredits = studyCredits;

		int varSize = sizeof(students[amountStudents].Surname) * sizeof(char);
		int nameSize = strlen(studentName);

		memset(students[amountStudents].Surname, 0, varSize);
		memcpy(students[amountStudents].Surname, studentName, nameSize < varSize ? nameSize : varSize);

		++amountStudents;
	}
}

void WriteTestStudentData()
{
	FILE* fileptr = fopen(test_file, "wb");
	for (int i = 0; i < amountStudents; ++i)
	{
		writeElement(fileptr, i, &students[i]);
	}
	fclose(fileptr);
}

void setUp(void)
{
	remove(test_file);

	amountStudents = 0;
	CreateStudent("Grasman", 0, 9);
	CreateStudent("Spajners", 2, 10);
	CreateStudent("Boerkool", 5, 12);
	CreateStudent("Koolboer", 14, 40);
	CreateStudent("Nersspaj", 30, 11);

	WriteTestStudentData();
}

void tearDown(void)
{
	remove(test_file);
	amountStudents = 0;
}

static void computeAverageStudyResults_test_NULLParam(void)
{
	double average;

	TEST_ASSERT(computeAverageStudyResults(NULL, &average) == -1);
	TEST_ASSERT(computeAverageStudyResults(test_file, NULL) == -1);
	TEST_ASSERT(computeAverageStudyResults(NULL, NULL) == -1);
}

float custom_nextafterf(float x, float y)
{
	union
	{
		float f;
		unsigned int i;
	} u;
	if (isnan (y) || isnan (x))
		return x + y;
	if (x == y )
		return y;
	u.f = x; 
	if (x == 0.0F)
	{
		u.i = 1;
		return y > 0.0F ? u.f : -u.f;
	}
	if (((x > 0.0F) ^ (y > x)) == 0)
		u.i++;
	else
		u.i--;
	return u.f;
}

static void computeAverageStudyResults_test(void)
{
	double average;
	double expected = 16.4;
	double delta = ((double)custom_nextafterf(expected, expected + 1.0) - expected);

	TEST_ASSERT(computeAverageStudyResults(test_file, &average) == 0);
	TEST_ASSERT_FLOAT_WITHIN(delta, expected, average);
}

static void linearSearchStudentsFile_test_NULLParam(void)
{
	STUDENT student;
	student.StudentNumber = 0;
	student.StudyCredits = 0;
	memcpy(student.Surname, "None", strlen("None") + 1);

	TEST_ASSERT(linearSearchStudentsFile(NULL, 2, &student) == -1);
	TEST_ASSERT(linearSearchStudentsFile(test_file, 2, NULL) == -1);
	TEST_ASSERT(linearSearchStudentsFile(NULL, 2, NULL) == -1);

	TEST_ASSERT_EQUAL(0, student.StudentNumber);
	TEST_ASSERT_EQUAL(0, student.StudyCredits);
	TEST_ASSERT_EQUAL_STRING("None", student.Surname);
}

static void linearSearchStudentsFile_test_NotFound(void)
{
	STUDENT student;
	student.StudentNumber = 0;
	student.StudyCredits = 0;
	memcpy(student.Surname, "None", strlen("None") + 1);

	TEST_ASSERT(linearSearchStudentsFile(test_file, 333, &student) == -1);

	TEST_ASSERT_EQUAL(0, student.StudentNumber);
	TEST_ASSERT_EQUAL(0, student.StudyCredits);
	TEST_ASSERT_EQUAL_STRING("None", student.Surname);
}

static void linearSearchStudentsFile_test(void)
{
	STUDENT student;
	student.StudentNumber = 0;
	student.StudyCredits = 0;
	memcpy(student.Surname, "None", strlen("None") + 1);

	TEST_ASSERT(linearSearchStudentsFile(test_file, 5, &student) == 0);

	TEST_ASSERT_EQUAL(5, student.StudentNumber);
	TEST_ASSERT_EQUAL(12, student.StudyCredits);
	TEST_ASSERT_EQUAL_STRING("Boerkool", student.Surname);
}

static void binarySearchStudentsFile_test_NULLParam(void)
{
	STUDENT student;
	student.StudentNumber = 0;
	student.StudyCredits = 0;
	memcpy(student.Surname, "None", strlen("None") + 1);

	TEST_ASSERT(binarySearchStudentsFile(NULL, 2, &student) == -1);
	TEST_ASSERT(binarySearchStudentsFile(test_file, 2, NULL) == -1);
	TEST_ASSERT(binarySearchStudentsFile(NULL, 2, NULL) == -1);

	TEST_ASSERT_EQUAL(0, student.StudentNumber);
	TEST_ASSERT_EQUAL(0, student.StudyCredits);
	TEST_ASSERT_EQUAL_STRING("None", student.Surname);
}

static void binarySearchStudentsFile_test_NotFound(void)
{
	STUDENT student;
	student.StudentNumber = 0;
	student.StudyCredits = 0;
	memcpy(student.Surname, "None", strlen("None") + 1);

	TEST_ASSERT(binarySearchStudentsFile(test_file, 333, &student) == -1);

	TEST_ASSERT_EQUAL(0, student.StudentNumber);
	TEST_ASSERT_EQUAL(0, student.StudyCredits);
	TEST_ASSERT_EQUAL_STRING("None", student.Surname);
}

static void binarySearchStudentsFile_test(void)
{
	STUDENT student;
	student.StudentNumber = 0;
	student.StudyCredits = 0;
	memcpy(student.Surname, "None", strlen("None") + 1);

	TEST_ASSERT(binarySearchStudentsFile(test_file, 5, &student) == 0);

	TEST_ASSERT_EQUAL(5, student.StudentNumber);
	TEST_ASSERT_EQUAL(12, student.StudyCredits);
	TEST_ASSERT_EQUAL_STRING("Boerkool", student.Surname);
}

static void addStudentSortedToFile_test_NULLParam(void)
{
	STUDENT student;

	student.StudentNumber = 1;
	student.StudyCredits = 30;
	memcpy(student.Surname, "Victorian", strlen("Victorian") + 1);

	//TEST_ASSERT_EQUAL(-1, addStudentSortedToFile(test_file, NULL));
	//TEST_ASSERT_EQUAL(-1, addStudentSortedToFile(NULL, &student));
	TEST_ASSERT_EQUAL(1, addStudentSortedToFile(test_file, &student));
	TEST_ASSERT_EQUAL(0, addStudentSortedToFile(test_file, &student));
}

static void addStudentSortedToFile_test(void)
{
	//Create ad reset temporary memory
	STUDENT sortedStudent[2];
	STUDENT readAllStudents[7];

	memset(sortedStudent, 0, sizeof(sortedStudent));
	memset(readAllStudents, 0, sizeof(readAllStudents));

	/* Before:
		Index	Name		Number	Credits
		0		Grasman		0		9 
		1		Spajners	2		10
		2		Boerkool	5		12
		3		Koolboer	14		40
		4		Nersspaj	30		11
	*/

	//insert some students
	sortedStudent[0].StudentNumber = 1;
	sortedStudent[0].StudyCredits = 30;
	memcpy(sortedStudent[0].Surname, "Victorian", strlen("Victorian") + 1);

	sortedStudent[1].StudentNumber = 6;
	sortedStudent[1].StudyCredits = 40;
	memcpy(sortedStudent[1].Surname, "Otheguy", strlen("Otheguy") + 1);

	/* After:
		Index	Name		Number	Credits
		0		Grasman		0		9 
		1		Victorian	1		30
		2		Spajners	2		10
		3		Boerkool	5		12
		4		Otheguy		6		40
		5		Koolboer	14		40
		6		Nersspaj	30		11
	*/

	//Test and perform sorted insertions
	TEST_ASSERT_EQUAL(1, addStudentSortedToFile(test_file, &sortedStudent[1]));
	TEST_ASSERT_EQUAL(0, addStudentSortedToFile(test_file, &students[0]));
	TEST_ASSERT_EQUAL(0, addStudentSortedToFile(test_file, &students[1]));
	TEST_ASSERT_EQUAL(0, addStudentSortedToFile(test_file, &students[2]));
	TEST_ASSERT_EQUAL(0, addStudentSortedToFile(test_file, &students[3]));
	TEST_ASSERT_EQUAL(0, addStudentSortedToFile(test_file, &students[4]));
	TEST_ASSERT_EQUAL(1, addStudentSortedToFile(test_file, &sortedStudent[0]));
	TEST_ASSERT_EQUAL(0, addStudentSortedToFile(test_file, &sortedStudent[0]));
	TEST_ASSERT_EQUAL(0, addStudentSortedToFile(test_file, &sortedStudent[1]));

	//Now recreate our custom user table (at the top of this file)
	//to match out expected result
	amountStudents = 0;
	memset(students, 0, sizeof(students));

	CreateStudent("Grasman"  , 0 , 9 );
	CreateStudent("Victorian", 1 , 30);
	CreateStudent("Spajners" , 2 , 10);
	CreateStudent("Boerkool" , 5 , 12);
	CreateStudent("Otheguy"  , 6 , 40);
	CreateStudent("Koolboer" , 14, 40);
	CreateStudent("Nersspaj" , 30, 11);

	//Now read the whole file that we did write using addStudentSortedToFile,
	//to read we use readElement
	FILE* fileptr = fopen(test_file, "rb");

	for (int i = 0; i < amountStudents; ++i)
	{
		readElement(fileptr, i, &readAllStudents[i]);
	}

	fclose(fileptr);

	//Now test if all the bytes are the same 
	TEST_ASSERT_EQUAL_HEX8_ARRAY((char*)students, (char*)readAllStudents, amountStudents * sizeof(STUDENT));
}

static void removeStudentFromFile_test_NullParam(void)
{
	TEST_ASSERT(removeStudentFromFile(NULL, 0) == -1);
}

static void removeStudentFromFile_test_NotFound(void)
{
	TEST_ASSERT(removeStudentFromFile(test_file, 0) == 0);
	TEST_ASSERT(removeStudentFromFile(test_file, 1) == -1);
}

static void removeStudentFromFile_test(void)
{	
	int removeStudentIds[] =
	{
		0, 3
	};

	int expectedStudentIds[] = 
	{ 
		1, 2, 4
	};

	for (int i = 0; i < sizeof(removeStudentIds) / sizeof(int); ++i)
	{
		TEST_ASSERT(removeStudentFromFile(test_file, students[removeStudentIds[i]].StudentNumber) == 0);
	}

	int index = 0;
	STUDENT readStudent;

	FILE* fileptr = fopen(test_file, "rb");

	while (/*index < sizeof(expectedStudentIds) / sizeof(int) &&*/ readElement(fileptr, index, &readStudent) == 1)
	{
		TEST_ASSERT_EQUAL(students[expectedStudentIds[index++]].StudentNumber, readStudent.StudentNumber);
	}

	fclose(fileptr);
}

int xmain(void)
{
	UnityBegin();
	
	RUN_TEST(computeAverageStudyResults_test_NULLParam, __LINE__);
	RUN_TEST(computeAverageStudyResults_test, __LINE__);

	RUN_TEST(linearSearchStudentsFile_test_NULLParam, __LINE__);
	RUN_TEST(linearSearchStudentsFile_test_NotFound, __LINE__);
	RUN_TEST(linearSearchStudentsFile_test, __LINE__);

	RUN_TEST(binarySearchStudentsFile_test_NULLParam, __LINE__);
	RUN_TEST(binarySearchStudentsFile_test_NotFound, __LINE__);
	RUN_TEST(binarySearchStudentsFile_test, __LINE__);

	RUN_TEST(addStudentSortedToFile_test_NULLParam, __LINE__);
	RUN_TEST(addStudentSortedToFile_test, __LINE__);

	RUN_TEST(removeStudentFromFile_test_NullParam, __LINE__);
	RUN_TEST(removeStudentFromFile_test_NotFound, __LINE__);
	RUN_TEST(removeStudentFromFile_test, __LINE__);

	return UnityEnd();
}
