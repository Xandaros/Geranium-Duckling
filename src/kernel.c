/*
 * kernel.c
 *
 *  Created on: Mar 9, 2013
 *      Author: xandaros
 */

#include "stdint.h"
#include "kstd.h"

void kmain()
{
	extern uint32_t magic;
	//extern void *mbd;

	if (magic != 0x2BADB002)
	{
		//Something went wrong during boot. Stop booting.
		return;
	}

	clear();
}
