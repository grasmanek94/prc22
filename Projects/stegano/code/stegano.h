/*
 * stegano.h
 *
 *  Created on: Jun 8, 2015
 *      Author: F. Hurkmans
 */

#ifndef STEGANO_H_
#define STEGANO_H_

void multiplex (const char* File0, const char* File1);
void multiplexText (const char* File0, const char* File1);
void demultiplex (const char* File0, const char* File1, const char* File2);
void demultiplexText (const char* File0, const char* File1, const char* File2);

#endif /* STEGANO_H_ */
