/*
 * bit.c
 *
 *      Authors: Yop Spanjers & Rafal Grasman
 */

#include <stdlib.h>
#include <stdint.h>

#include "resource_detector.h"
#include "bit.h"

uint8_t getSubstring (uint8_t Src, uint8_t SrcPos, uint8_t NrOfBits, uint8_t DestPos)
{
	uint8_t full_bitmask = (uint8_t)(-1);
	uint8_t case_bitmask = full_bitmask >> (8 * sizeof(uint8_t) - NrOfBits);
	uint8_t source_bitmask = case_bitmask << SrcPos;
	uint8_t extracted_src = Src & source_bitmask;
	int8_t finalshift = DestPos - SrcPos;
	uint8_t output = finalshift >= 0 ? 
		extracted_src << finalshift : 
		extracted_src >> -finalshift;
	return output;
}
