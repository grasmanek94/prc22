//Default includes
#include <stdlib.h>

//Custom includes
#include "integer_file.h"

int create_file(char* filename, int high, int low)
/* pre : -
 * post: If all parameters are valid, a new file is created with name filename. The file contains integers,
 *       starting from high and counting down to low. Result 0 is returned.
 *       If parameters are invalid (null or high is lower than low), -1 is returned.
 *       thus create_file("test.txt", 3999, 3000) will result in a text file that contains 1000 integers
 *       starting at 3999 and counting down to 3000
 */
{
	if (high < low || filename == NULL)
	{
		return -1;
	}

	FILE* file = fopen(filename, "wb");

	if (file == NULL)
	{
		return -1;
	}

	for (int i = high; i >= low; --i)
	{
		if (fwrite(&i, sizeof(int), 1, file) != 1)
		{
			return -1;
		}
	}

	fclose(file);

    return 0;
}

int delete_file(char* filename)
/* pre : -
 * post: If filename is valid, file is removed from disk and 0 is returned. Else -1 is returned.
 */
{
	if (filename == NULL || remove(filename) != 0)
	{
		return -1;
	}

    return 0;
}

int read_value(FILE* fileptr, int pos)
/* pre : -
 * post: the value on position pos is read from the correct location in the already opened file
 *       if fileptr is NULL, -1 is returned.
 */
{
	if (fileptr == NULL || fseek(fileptr, pos * sizeof(int), SEEK_SET) != 0)
	{
		return -1;
	}

	int val;

	if (fread(&val, sizeof(int), 1, fileptr) != 1)
	{
		return -1;
	}

    return val;
}
