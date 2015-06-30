/*
 * header.c
 *
 *      Authors: Yop Spanjers & Rafal Grasman
 */

#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include "resource_detector.h"
#include "header.h"

void readHdr (FILE* FilePtr, BMP_MAGIC_t* Magic, BMP_FILE_t* File, BMP_INFO_t* Info)
{
	if (FilePtr && Magic && File && Info)
	{
		if (
			fread(Magic, sizeof(BMP_MAGIC_t), 1, FilePtr) +
			fread(File, sizeof(BMP_FILE_t), 1, FilePtr) + 
			fread(Info, sizeof(BMP_INFO_t), 1, FilePtr) 
		== 3) {}
	}
}


void writeHdr (FILE* FilePtr, BMP_MAGIC_t* Magic, BMP_FILE_t* File, BMP_INFO_t* Info)
{
	if (FilePtr && Magic && File && Info)
	{
		if (
			fwrite(Magic, sizeof(BMP_MAGIC_t), 1, FilePtr) +
			fwrite(File,  sizeof(BMP_FILE_t),  1, FilePtr) +
			fwrite(Info,  sizeof(BMP_INFO_t),  1, FilePtr)
		== 3) {}
	}
}
