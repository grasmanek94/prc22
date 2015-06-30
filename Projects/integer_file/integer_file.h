#ifndef integer_file_H
#define integer_file_H
#include <stdio.h>

int create_file(char* filename, int high, int low);

int delete_file(char* filename);

int read_value(FILE* fileptr, int pos);


#endif
