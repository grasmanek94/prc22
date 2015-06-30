//Default includes
#include <stdio.h>

//Unit testin includes
#include <unity.h>

//Custom includes
#include "integer_file.h"
#include "integer_file_test.h"

static const int StartValue = 8320;
static const int EndValue = 7321;

void setUp(void)
{
    // This is run before EACH test
    create_file(TESTFILE, StartValue, EndValue);
}

void tearDown(void)
{
    // This is run after EACH test
    delete_file(TESTFILE);
}

void test_CreateFileNullCheck(void)
{
    TEST_ASSERT_EQUAL(-1, create_file(NULL, 12, 10));
}

void test_CreateFileInvaludHighAndLow(void)
{
    TEST_ASSERT_EQUAL(-1, create_file(TESTFILE, 10, 12));
}

void test_DeleteFileNullCheck(void)
{
    TEST_ASSERT_EQUAL(-1, delete_file(NULL));
}

void test_ReadValueNullCheck(void)
{
    TEST_ASSERT_EQUAL(-1, read_value(NULL, 12));
}

void test_ReadingFirstValueInFile(void)
{
    FILE* fileptr = fopen(TESTFILE, "rb");
    TEST_ASSERT_NOT_NULL(fileptr);

    TEST_ASSERT_EQUAL(StartValue, read_value(fileptr, 0));

    fclose(fileptr);
}

void test_ReadingValueInMiddleOfFile(void)
{
    FILE* fileptr = fopen(TESTFILE, "rb");
    TEST_ASSERT_NOT_NULL(fileptr);

    TEST_ASSERT_EQUAL(StartValue-250, read_value(fileptr, 250));

    fclose(fileptr);
}

void test_ReadingLastValueInFile(void)
{
    FILE* fileptr = fopen(TESTFILE, "rb");
    TEST_ASSERT_NOT_NULL(fileptr);

    TEST_ASSERT_EQUAL(EndValue, read_value(fileptr, 999));

    fclose(fileptr);
}

int main(void)
{
    UnityBegin();

    RUN_TEST(test_CreateFileNullCheck, __LINE__);
	RUN_TEST(test_CreateFileInvaludHighAndLow, __LINE__);
	RUN_TEST(test_DeleteFileNullCheck, __LINE__);
	RUN_TEST(test_ReadValueNullCheck, __LINE__);
	RUN_TEST(test_ReadingFirstValueInFile, __LINE__);
	RUN_TEST(test_ReadingValueInMiddleOfFile, __LINE__);
	RUN_TEST(test_ReadingLastValueInFile, __LINE__);

	//All tests passed

    return UnityEnd();
}
