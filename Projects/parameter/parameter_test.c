/*
	Main parameter test file
*/

//Default includes
#include <stdio.h>

//Unit testin includes
#include <unity.h>

//Custom includes
#include "parameter.h"

void setUp(void)
{

}

void tearDown(void)
{

}

static void test_SwapValues(void)
{
	int i = -10;
	int j = 11;
	int k = 2000000000;
	int l = 1000000000;
	int m = 2000000000;

	SwapValues(&i, &j);
	SwapValues(&k, &l);
	SwapValues(&m, &l);

	TEST_ASSERT(i == 11);
	TEST_ASSERT(j == -10);
	TEST_ASSERT(k == 1000000000);
	TEST_ASSERT(l == 2000000000);
	TEST_ASSERT(m == 2000000000);

	SwapValues(0, &i);
	SwapValues(0, &j);
	SwapValues(0, &k);
	SwapValues(0, &l);
	SwapValues(0, &m);

	SwapValues(&i, 0);
	SwapValues(&j, 0);
	SwapValues(&k, 0);
	SwapValues(&l, 0);
	SwapValues(&m, 0);

	SwapValues(0, 0);

	TEST_ASSERT(i == 11);
	TEST_ASSERT(j == -10);
	TEST_ASSERT(k == 1000000000);
	TEST_ASSERT(l == 2000000000);
	TEST_ASSERT(m == 2000000000);
}

static void test_GetSumReturn(void)
{
	int a[] = { 10, 20, 30, 40 };

	int result = GetSumReturn(a, 4);
	int result2 = GetSumReturn(0, 4);
	int result3 = GetSumReturn(a, 0);
	int result4 = GetSumReturn(a, -100);

	TEST_ASSERT(a[0] == 10);
	TEST_ASSERT(a[1] == 20);
	TEST_ASSERT(a[2] == 30);
	TEST_ASSERT(a[3] == 40);

	TEST_ASSERT(result == 100);
	TEST_ASSERT(result2 == 0);
	TEST_ASSERT(result3 == 0);
	TEST_ASSERT(result4 == 0);
}

static void test_GetSumParameter(void)
{
	int a[] = { 10, 20, 30, 40 };
	int result = 0;

	GetSumParameter(a, 3, &result);

	TEST_ASSERT(a[0] == 10);
	TEST_ASSERT(a[1] == 20);
	TEST_ASSERT(a[2] == 30);
	TEST_ASSERT(a[3] == 40);

	TEST_ASSERT(result == 60);

	GetSumParameter(a, 0, 0);

	TEST_ASSERT(a[0] == 10);
	TEST_ASSERT(a[1] == 20);
	TEST_ASSERT(a[2] == 30);
	TEST_ASSERT(a[3] == 40);

	int u = 564564564;
	int w = u;
	GetSumParameter(a, 0, &u);//unchanged

	TEST_ASSERT(u == w);

	int x = 564564564;
	int y = x;

	GetSumParameter(0, 100, &x);

	TEST_ASSERT(x == y);//unchanged
}

static void test_ArrayAdd(void)
{
	int a1[] = { 10, 20, 30, 40 };
	int a2[] = { 1, 2, 3, 4 };
	int result[4] = { 0, 0, 0, 0 };

	ArrayAdd(0, 0, 4, result);
	ArrayAdd(0, 0, -100, result);
	ArrayAdd(a1, a2, -100, result);
	ArrayAdd(0, a1, -100, result);
	ArrayAdd(a2, a1, -100, result);
	ArrayAdd(a2, 0, 100, result);

	TEST_ASSERT(a1[0] == 10);
	TEST_ASSERT(a1[1] == 20);
	TEST_ASSERT(a1[2] == 30);
	TEST_ASSERT(a1[3] == 40);
	TEST_ASSERT(a2[0] == 1);
	TEST_ASSERT(a2[1] == 2);
	TEST_ASSERT(a2[2] == 3);
	TEST_ASSERT(a2[3] == 4);
	TEST_ASSERT(result[0] == 0);
	TEST_ASSERT(result[1] == 0);
	TEST_ASSERT(result[2] == 0);
	TEST_ASSERT(result[3] == 0);

	ArrayAdd(a1, a2, 4, result);

	TEST_ASSERT(a1[0] == 10);
	TEST_ASSERT(a1[1] == 20);
	TEST_ASSERT(a1[2] == 30);
	TEST_ASSERT(a1[3] == 40);
	TEST_ASSERT(a2[0] == 1);
	TEST_ASSERT(a2[1] == 2);
	TEST_ASSERT(a2[2] == 3);
	TEST_ASSERT(a2[3] == 4);
	TEST_ASSERT(result[0] == 11);
	TEST_ASSERT(result[1] == 22);
	TEST_ASSERT(result[2] == 33);
	TEST_ASSERT(result[3] == 44);
}

int main(void)
{
	UnityBegin();

	RUN_TEST(test_ArrayAdd, __LINE__);
	RUN_TEST(test_GetSumParameter, __LINE__);
	RUN_TEST(test_GetSumReturn, __LINE__);
	RUN_TEST(test_SwapValues, __LINE__);

	return UnityEnd();
}
