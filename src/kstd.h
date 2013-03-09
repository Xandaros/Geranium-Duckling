/*
 * kstd.h
 *
 *  Created on: Mar 9, 2013
 *      Author: xandaros
 */

#ifndef KSTD_H_
#define KSTD_H_

#include "stdint.h"

void putchar(unsigned char c);
void print(char *string);
void println(char *string);
void clear();

char *itoa(sint32_t i, char *buffer, int base);

#endif /* KSTD_H_ */
