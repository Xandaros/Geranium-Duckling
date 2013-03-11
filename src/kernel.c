/*
 * kernel.c
 *
 *  Created on: Mar 9, 2013
 *      Author: xandaros
 */

#include "stdint.h"
#include "kstdio.h"
#include "system.h"
#include "string.h"

void init()
{
	setupGDT();
	protectedMode();
	setupIDT();
	setupPIC();
	__asm__ __volatile__("sti");
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
	println("Before interrupts");
	asm volatile("int $0x3");
	println("Between interrupts");
	asm volatile("int $0x4");
	println("After interrupts");
}
