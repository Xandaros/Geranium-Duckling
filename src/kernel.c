/*
 * kernel.c
 *
 *  Created on: Mar 9, 2013
 *      Author: xandaros
 */

#include "stdint.h"
#include "kstd.h"
#include "gdt.h"

void init()
{
	setupGDT();
}

void kmain()
{
	extern uint32_t magic;
	//extern void *mbd;

	if (magic != 0x2BADB002)
	{
		//Something went wrong during boot. Stop booting.
		return;
	}

	init();

	clear();
	char b[20];
	volatile int a = 0;
	__asm__ __volatile__("mov %%cs,%0;" : "=r"(a));
	println(itoa(a, b, 16));
}
