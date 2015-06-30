/*
	Main file source file
*/

//Default includes
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Unit testin includes
#include "unity.h"

//Custom includes
#include "element_reader.h"

STUDENT students[5];
int amountStudents = 0;

const char* test_file = "element_reader_test.data";

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

	CreateStudent("Grasman", amountStudents, 9);
	CreateStudent("Spajners", amountStudents, 10);
	CreateStudent("Boerkool", amountStudents, 5);
	CreateStudent("Koolboer", amountStudents, 40);
	CreateStudent("Nersspaj", amountStudents, 11);

	WriteTestStudentData();
}

void tearDown(void)
{
	remove(test_file);
	amountStudents = 0;
}

static void test_element_reader_readElement_FilePtr_NULL()
{
	FILE* fileptr = fopen(test_file, "rb");
	STUDENT element;

	element.StudentNumber = 12;
	element.StudyCredits = 34;
	element.Surname[0] = 56;

	TEST_ASSERT(fileptr != NULL);

	TEST_ASSERT(readElement(NULL, 0, &element) == -1);
	TEST_ASSERT(readElement(fileptr, 0, NULL) == -1);
	TEST_ASSERT(readElement(NULL, 100, &element) == -1);
	TEST_ASSERT(readElement(fileptr, 100, NULL) == -1);

	TEST_ASSERT_EQUAL(12, element.StudentNumber);
	TEST_ASSERT_EQUAL(34, element.StudyCredits);
	TEST_ASSERT_EQUAL(56, element.Surname[0]);

	fclose(fileptr);
}

static void test_element_reader_readElement_ElementNrTooBig()
{
	FILE* fileptr = fopen(test_file, "rb");
	STUDENT element;

	element.StudentNumber = 12;
	element.StudyCredits = 34;
	element.Surname[0] = 56;

	TEST_ASSERT(fileptr != NULL);

	TEST_ASSERT(readElement(fileptr, 16, &element) == 0);

	TEST_ASSERT_EQUAL(12, element.StudentNumber);
	TEST_ASSERT_EQUAL(34, element.StudyCredits);
	TEST_ASSERT_EQUAL(56, element.Surname[0]);

	fclose(fileptr);
}

static void test_element_reader_readElement_success()
{
	FILE* fileptr = fopen(test_file, "rb");
	STUDENT element;

	element.StudentNumber = 12;
	element.StudyCredits = 34;
	element.Surname[0] = 56;

	TEST_ASSERT(fileptr != NULL);

	TEST_ASSERT(readElement(fileptr, 1, &element) == 1);

	TEST_ASSERT_EQUAL(1, element.StudentNumber);
	TEST_ASSERT_EQUAL(10, element.StudyCredits);
	TEST_ASSERT_EQUAL_STRING("Spajners", element.Surname);

	fclose(fileptr);
}

static void test_element_reader_writeElement_FilePtr_NULL()
{
	remove(test_file);
	for (int i = 0; i < amountStudents; ++i)
	{
		TEST_ASSERT(writeElement(NULL, i, &students[i]) == -1);
	}
}

static void test_element_reader_writeElement_success()
{
	char compareBytes[sizeof(students)];
	memcpy(compareBytes, students, sizeof(students));

	char readBytes[sizeof(compareBytes)];
	memset(readBytes, 0, sizeof(readBytes));

	remove(test_file);
	FILE* fileptr = fopen(test_file, "wb");
	for (int i = 0; i < amountStudents; ++i)
	{
		TEST_ASSERT(writeElement(fileptr, i, &students[i]) == 0);
	}
	fclose(fileptr);

	fileptr = fopen(test_file, "rb");	
	if(fread(readBytes, sizeof(readBytes), 1, fileptr));
	fclose(fileptr);

	TEST_ASSERT_EQUAL_INT8_ARRAY(compareBytes, readBytes, sizeof(compareBytes));

}

int xmain(void)
{
	UnityBegin();

	RUN_TEST(test_element_reader_readElement_FilePtr_NULL, __LINE__);
	RUN_TEST(test_element_reader_readElement_ElementNrTooBig, __LINE__);
	RUN_TEST(test_element_reader_readElement_success, __LINE__);

	RUN_TEST(test_element_reader_writeElement_FilePtr_NULL, __LINE__);
	RUN_TEST(test_element_reader_writeElement_success, __LINE__);

	return UnityEnd();
}
