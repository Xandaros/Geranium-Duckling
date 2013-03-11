/*
 * string.c
 *
 *  Created on: Mar 10, 2013
 *      Author: xandaros
 */

#include "string.h"

void *memset(void *_ptr, int value, size_t num)
{
	unsigned char *ptr = (unsigned char *)_ptr;
	while (num-- > 0)
	{
		*ptr++ = value;
	}
	return ptr;
}
