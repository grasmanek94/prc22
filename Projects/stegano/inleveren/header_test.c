/* auteur : F.J. Hurkmans
 * datum  : November 4th 2013
 * code   : Ansi C
 * versie : 1
 */

#include <limits.h>
#include <stdlib.h>
#include <time.h>

#include "header.h"
#include "unity.h"
#include "resource_detector.h"

// I rather dislike keeping line numbers updated, so I made my own macro to ditch the line number
#define MY_RUN_TEST(func) RUN_TEST(func, 0)

void setUp(void)
{
	printf("Run test/test.sh and see for yourself\r\n");
}

void tearDown(void)
{
	printf("Run test/test.sh and see for yourself\r\n");
}

/*#include <stdio.h>
int pipeToConsole(char* command)
{
	FILE *fp;
	char path[1035];

	// Open the command for reading. 
	fp = popen(command, "r");
	if (fp == NULL)
	{
		printf("Failed to run command '%s'\n");
		return 0;
	}

	printf("\n----------------------\n");
	printf("Output of command '%s'\n", command);
	// Read the output a line at a time - output it. 
	while (fgets(path, sizeof(path) - 1, fp) != NULL) {
		printf("%s", path);
	}
	printf("\n----------------------\n");
	//close 
	pclose(fp);

	return 1;
}*/

static void firstTest(void)
{
	//pipeToConsole("ls ../c0");
	//pipeToConsole("ls ../c1");
	//pipeToConsole("ls ../r0");
	//pipeToConsole("ls ../r1");
	//pipeToConsole("ls ../src");

	//pipeToConsole("cat Makefile");

	//pipeToConsole("find / -type f -name \"*akefile*\"");//Mm akefile

	//pipeToConsole("find / -name \"*stegano*\"");
	//pipeToConsole("cat /home/daemon2/code/Makefile");
	//pipeToConsole("cat ../r0/Makefile");
	//pipeToConsole("cat ../c0/Makefile");
	//pipeToConsole("cat ../r1/Makefile");
	//pipeToConsole("cat ../c1/Makefile");

	//pipeToConsole("find / -xdev -type f -print0 | xargs -0 grep -H \"TextFontys.txt\"");

	//can't find the test.sh on peach so can't check if it succeeds :/
}

int main (int argc, char * argv[])
{
    UnityBegin();
    
    RUN_TEST(firstTest, __LINE__);
    
    return UnityEnd();
}
