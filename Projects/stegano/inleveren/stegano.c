/*
 * stegano.c
 *
 *  Created on: Jun 8, 2015
 *		Authors: Yop Spanjers & Rafal Grasman
 *
 *	Welcome to the kingdom of high performant & stable code ;)
 *
 */

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>

#include "resource_detector.h"
#include "bit.h"
#include "header.h"
#include "stegano.h"

#define MAX_FILENAME 255

#define max(a,b)    (((a) > (b)) ? (a) : (b))

#ifdef _WIN32
#pragma pack (1)
#endif

typedef struct
{
	BMP_MAGIC_t magic;
	BMP_FILE_t file;
	BMP_INFO_t info;
}
#ifndef _WIN32
__attribute__((packed))
#endif
BMP_ALL;

#define _BITS_PP (24)
#define _BITS_PB (8)
#define _BYTES_PP (_BITS_PP / _BITS_PB)

//I don't like defines
const int32_t bitspp  = _BITS_PP;
const int32_t bitspb  = _BITS_PB;
const int32_t bytespp = _BYTES_PP;

size_t customfsize(FILE* fp)
{
	if (!fp)
	{
		return 0;
	}

	size_t curr = ftell(fp);
	if (fseek(fp, 0L, SEEK_END))
	{
		return 0;
	}

	size_t size = ftell(fp);
	if (fseek(fp, curr, SEEK_SET))
	{
		return 0;
	}

	return size;
}

void multiplex (const char* File0, const char* File1)
{
	FILE* FilePtr[2]			=	{ NULL, NULL};

	//prepare input files
	FilePtr[0]					=	fopen(File0, "rb"); //waarin je wilt verbergen

	if (!FilePtr[0])
	{
		return;
	}

	FilePtr[1]					=	fopen(File1, "rb"); //wat wil je verbergen

	if (!FilePtr[1])
	{
		fclose(FilePtr[0]);
		return;
	}

	BMP_ALL bmp[2];

	//prepare headers and load file 1 and 2 into memory in one big swing, nice performance gain (we assume enough free memory)
	for (int i = 0; i < 2; ++i)
	{
		readHdr(FilePtr[i], &bmp[i].magic, &bmp[i].file, &bmp[i].info);
		if (fseek(FilePtr[i], bmp[i].file.bmp_offset, SEEK_SET))
		{	//welp, error
			fclose(FilePtr[0]);
			fclose(FilePtr[1]);
			return;
		}
	}

	if (bmp[0].info.width < bmp[1].info.width || bmp[0].info.height < bmp[1].info.height)
	{	//'hidden' image too big (good luck hiding that big ass!)
		fclose(FilePtr[0]);
		fclose(FilePtr[1]);
		return;
	}

	//prepare memory
	size_t BitmapSizes[2];
	uint8_t *FileBytes[3];


	for (int i = 0; i < 2; ++i)
	{
		BitmapSizes[i] = bytespp * bmp[i].info.width * bmp[i].info.height;
		FileBytes[i] = malloc(BitmapSizes[i]);
		if(fread(FileBytes[i], BitmapSizes[i], 1, FilePtr[i]) != 1)
		{	//error so.. cleanup:
			for (int j = 0; j < i; ++j)
			{
				fclose(FilePtr[j]);
				free(FileBytes[j]);
			}
			return;
		}
		fclose(FilePtr[i]);//file not needed anymore so close it (because it's now in our memory)
	}

	FileBytes[2] = malloc(BitmapSizes[0]);

	bmp[0].file.creator1 = bmp[1].info.width;
	bmp[0].file.creator2 = bmp[1].info.height;

	char  buf[MAX_FILENAME];

    for (int NrBits = 0; NrBits < 9; NrBits++)
    {
        // NrBits: nbr of bits for the hidden image

		//prepare output file
        snprintf (buf, MAX_FILENAME, "mux_%s_%s_%d.bmp", File0, File1, NrBits);
        FilePtr[0] = fopen (buf,   "wb");

		if (!FilePtr[0])
		{	//more errors, let's just continue to next file
			continue;
		}

		//write the header
		bmp[0].info.nimpcolors = NrBits;

		writeHdr(FilePtr[0], &bmp[0].magic, &bmp[0].file, &bmp[0].info);
		
		memset(FileBytes[2], 0, BitmapSizes[0]);

		for (int32_t x = 0; x < bmp[0].info.width; ++x)//width
		{
			for (int32_t y = 0; y < bmp[0].info.height; ++y)//height
			{			
				for (int32_t b = 0; b < bytespp; ++b)//byte
				{
					uint8_t src[2] =
					{	//bonus 6:
						(x < bmp[0].info.width) ? ((y < bmp[0].info.height) ? (FileBytes[0][y * bmp[0].info.width * bytespp + x * bytespp + b]) : (0)) : (0),
						(x < bmp[1].info.width) ? ((y < bmp[1].info.height) ? (FileBytes[1][y * bmp[1].info.width * bytespp + x * bytespp + b]) : (0)) : (0)
					};

					FileBytes[2][y * bmp[0].info.width * bytespp + x * bytespp + b] =
						getSubstring(src[0], NrBits, bitspb - NrBits, NrBits) | getSubstring(src[1], bitspb - NrBits, NrBits, 0);
				}
			}
		}

		//write our new bmp image:
		if(fwrite(FileBytes[2], BitmapSizes[0], 1, FilePtr[0]) != 1) 
		{ 
			/* we don't care if there's an error or not, we are going to close the file anyway now: */ 
		}

		//close output file
		fclose(FilePtr[0]);
    }

	//cleanup memory
	for (int i = 0; i < 3; ++i)
	{
		free(FileBytes[i]);
	}
}

void multiplexText (const char* File0, const char* File1)
{
	FILE* FilePtr[2]			=	{ NULL, NULL };

	//prepare input files
	FilePtr[0]					=	fopen(File0, "rb");

	if (!FilePtr[0])
	{
		return;
	}

	FilePtr[1]					=	fopen(File1, "rb");

	if (!FilePtr[1])
	{
		fclose(FilePtr[0]);
		return;
	}

	//prepare headers and load file 1 and 2 into memory in one big swing, nice performance gain (we assume enough free memory)
	//also do some housekeeping
	BMP_ALL bmp;
	readHdr(FilePtr[0], &bmp.magic, &bmp.file, &bmp.info);

	if (fseek(FilePtr[0], bmp.file.bmp_offset, SEEK_SET))
	{	//welp, fseek error!
		fclose(FilePtr[0]);
		fclose(FilePtr[1]);
		return;
	}

	//prepare memory
	size_t FileSizes[2] = 
	{ 
		bytespp * bmp.info.width * bmp.info.height,  
		customfsize(FilePtr[1])
	};

	size_t neededBytesForText = FileSizes[1] * 8;//each character -> one bit on each byte so *8 = neededbBytes
	if (neededBytesForText > FileSizes[0] || !neededBytesForText)
	{	//welp not enough room or no text to hide!
		fclose(FilePtr[0]);
		fclose(FilePtr[1]);
		return;
	}

	uint8_t *FileBytes[2];

	//read files into memory & close
	for (int i = 0; i < 2; ++i)
	{
		FileBytes[i] = malloc(FileSizes[i]);
		if (fread(FileBytes[i], FileSizes[i], 1, FilePtr[i]) != 1)
		{	//read error! cleanup:
			for (int j = 0; j < i; ++j)
			{
				free(FileBytes[j]);
				fclose(FilePtr[j]);
			}
			return;
		}
		fclose(FilePtr[i]);//file loaded in memory so not needed anymore
	}

	//prepare out file
	char  buf[MAX_FILENAME];
    snprintf (buf, MAX_FILENAME, "mux_%s_%s.bmp", File0, File1);
    FilePtr[0] = fopen (buf,   "wb");

	//write the header
	bmp.file.creator1 = (uint16_t)FileSizes[1];

	writeHdr(FilePtr[0], &bmp.magic, &bmp.file, &bmp.info);

	size_t i = 1;
	size_t j;
	size_t bindex;

	do
	{
		j = i - 1;
		bindex = j / bitspb;

		uint8_t bit = (uint8_t)(j % (size_t)bitspb);
		uint8_t character = FileBytes[1][bindex];
		uint8_t charbit = (character & (1 << bit)) >> bit;

		FileBytes[0][i] = (FileBytes[0][i] & ~1) | charbit;

	} while (++i, bindex < FileSizes[1]);//we already know there is enough room so we only need to keep checking the bit-index

	//write our new bmp image:
	if(fwrite(FileBytes[0], FileSizes[0], 1, FilePtr[0]) != 1) 
	{
		/* we don't care if there's an error or not, we are going to close the file anyway now: */
	}
	
	//close handles & cleanup
	fclose(FilePtr[0]);
	for (int i = 0; i < 2; ++i)
	{
		free(FileBytes[i]);
	}
}

void demultiplex(const char* File0, const char* File1, const char* File2)
{
	FILE* FilePtr[2] = { NULL, NULL };

	//prepare input file
	FilePtr[0] = fopen(File0, "rb");

	if (!FilePtr[0])
	{
		return;
	}

	//prepare header and load file 1 into memory in one big swing, nice performance gain (we assume enough free memory)
	//also do some housekeeping
	BMP_ALL bmp;
	readHdr(FilePtr[0], &bmp.magic, &bmp.file, &bmp.info);

	if (fseek(FilePtr[0], bmp.file.bmp_offset, SEEK_SET))
	{	//oioi, seek err! clenaup! *pun intended*
		fclose(FilePtr[0]);
		return;
	}

	int NrBits = bmp.info.nimpcolors;

	//use hidden image width & height (creator1 & creator2) to make correct image size
	size_t hidden_width = bmp.file.creator1;
	size_t hidden_height = bmp.file.creator2;
	size_t visible_width = bmp.info.width;
	size_t visible_height = bmp.info.height;
	size_t hidden_width_bytes = hidden_width * bytespp;
	size_t visible_width_bytes = visible_width * bytespp;

	size_t FileSizes[2] =
	{
		visible_width_bytes * bmp.info.height,
		hidden_width_bytes * hidden_height
	};

	uint8_t *FileBytes[2] =
	{
		malloc(FileSizes[0]),
		malloc(FileSizes[1])
	};

	if (fread(FileBytes[0], FileSizes[0], 1, FilePtr[0]) != 1)
	{	//read error! cleanup:
		for (int i = 0; i < 2; ++i)
		{
			free(FileBytes[i]);
		}
		fclose(FilePtr[0]);
		return;
	}

	fclose(FilePtr[0]);//it's loaded now into memory, so not needed anymore

	//...and output files
	FilePtr[0] = fopen(File1, "wb");

	if (!FilePtr[0])
	{
		for (int i = 0; i < 2; ++i)
		{
			free(FileBytes[i]);
		}
		return;
	}

	FilePtr[1] = fopen(File2, "wb");

	if (!FilePtr[1])
	{
		fclose(FilePtr[0]);
		for (int i = 0; i < 2; ++i)
		{
			free(FileBytes[i]);
		}
		return;
	}

	//write headers
	bmp.file.creator1 = 0;
	bmp.file.creator2 = 0;
	bmp.info.nimpcolors = 0;

	writeHdr(FilePtr[0], &bmp.magic, &bmp.file, &bmp.info);

	bmp.info.width = hidden_width;
	bmp.info.height = hidden_height;
	writeHdr(FilePtr[1], &bmp.magic, &bmp.file, &bmp.info);

	for (size_t x = 0; x < visible_width_bytes; ++x)
	{
		for (size_t y = 0; y < visible_height; ++y)
		{
			size_t v_i = y * visible_width_bytes + x;
			uint8_t source = FileBytes[0][v_i];

			FileBytes[0][v_i] = getSubstring(source, NrBits, bitspb - NrBits, NrBits);

			//bonus 7:
			if (x < hidden_width_bytes && y < hidden_height)
			{
				size_t h_i = y * hidden_width_bytes + x;
				FileBytes[1][h_i] = getSubstring(source, 0, NrBits, bitspb - NrBits);
			}
		}
	}

	//write & cleanup:
	for (int i = 0; i < 2; ++i)
	{
		if (fwrite(FileBytes[i], FileSizes[i], 1, FilePtr[i]) != 1)
		{
			/* we don't care if there's an error or not, we are going to close the file anyway now: */
		}
		fclose(FilePtr[i]);
		free(FileBytes[i]);
	}
}

void demultiplexText (const char* File0, const char* File1, const char* File2)
{
	FILE* FilePtr[2] = { NULL, NULL };

	//prepare files
	FilePtr[0] = fopen(File0, "rb");

	if (!FilePtr[0])
	{
		return;
	}

	//prepare headers and load file 1 into memory in one big swing, nice performance gain (we assume enough free memory)
	//also do some housekeeping
	BMP_ALL bmp;
	readHdr(FilePtr[0], &bmp.magic, &bmp.file, &bmp.info);

	if (!bmp.file.creator1 || // we have no text data? :(
		fseek(FilePtr[0], bmp.file.bmp_offset, SEEK_SET))
	{	//oh nooooseee! errah, cleanup:
		fclose(FilePtr[0]);
		return;
	}

	//prepare memory
	size_t FileSizes[2] =
	{
		bytespp * bmp.info.width * bmp.info.height,
		bmp.file.creator1
	};

	uint8_t *FileBytes[2] = 
	{
		malloc(FileSizes[0]),
		malloc(FileSizes[1])
	};

	memset(FileBytes[1], 0, FileSizes[1]);//HEY COMPILER! this line is very important, if you remove it (optimization?) this code won't work

	if (fread(FileBytes[0], FileSizes[0], 1, FilePtr[0]) != 1) 
	{	//so many errors... cleanup lady! c'mon:
		fclose(FilePtr[0]);
		for (int i = 0; i < 2; ++i)
		{
			free(FileBytes[i]);
		}
		return;
	}

	fclose(FilePtr[0]);//file loaded in memory so not needed anymore

	FilePtr[0] = fopen(File1, "wb");

	if (!FilePtr[0])
	{
		for (int i = 0; i < 2; ++i)
		{
			free(FileBytes[i]);
		}
		return;
	}

	FilePtr[1] = fopen(File2, "wb");

	if (!FilePtr[1])
	{
		fclose(FilePtr[0]);
		for (int i = 0; i < 2; ++i)
		{
			free(FileBytes[i]);
		}
		return;
	}

	//write the header
	bmp.file.creator1 = 0;
	writeHdr(FilePtr[0], &bmp.magic, &bmp.file, &bmp.info);

	size_t i = 1;
	size_t j;
	size_t bindex;

	do
	{
		j = i - 1;
		bindex = j / (bitspb * sizeof(uint8_t));
		uint8_t bit = (uint8_t)(j % (size_t)(bitspb * sizeof(uint8_t)));
		uint8_t charbit = (FileBytes[0][i] & 1) << bit;

		FileBytes[1][bindex] |= charbit;
		FileBytes[0][i] &= ~1;
	} while (++i < FileSizes[0] && bindex < FileSizes[1]); // the FileSizes[1] could be corrupt so just in case check FileSizes[0] too, it's at least 1 so it won't crash, completely safe

	//write, close handles & cleanup
	for (int i = 0; i < 2; ++i)
	{
		if (fwrite(FileBytes[i], FileSizes[i], 1, FilePtr[i]) != 1)
		{
			/* we don't care if there's an error or not, we are going to close the file anyway now: */
		}
		fclose(FilePtr[i]);
		free(FileBytes[i]);
	}
}

