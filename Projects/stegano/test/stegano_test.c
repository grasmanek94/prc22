/* auteur : F.J. Hurkmans
 * datum  : November 4th 2013
 * code   : Ansi C
 * versie : 1
 */

#include <limits.h>
#include <stdlib.h>
#include <time.h>

#include "stegano.h"
#include "unity.h"
#include "resource_detector.h"

// I rather dislike keeping line numbers updated, so I made my own macro to ditch the line number

void setUp(void)
{
	printf("Run test/test.sh and see for yourself\r\n");
}

void tearDown(void)
{
	printf("Run test/test.sh and see for yourself\r\n");
}

static void firstTest(void)
{
	printf("Run test/test.sh and see for yourself\r\n");
}

int main (int argc, char * argv[])
{
    UnityBegin();
    
    RUN_TEST(firstTest, __LINE__);
    
    return UnityEnd();
}
