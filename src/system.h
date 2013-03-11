/*
 * system.h
 *
 *  Created on: Mar 10, 2013
 *      Author: xandaros
 */

#ifndef SYSTEM_H_
#define SYSTEM_H_

#include "stdint.h"

#define BochsBreak() __asm__ __volatile__("xchgw %%bx, %%bx" :);

typedef struct
{
		uint32_t ds;
		uint32_t edi, esi, ebp, esp, ebx, edx, ecx, eax;
} registers_t;

extern void protectedMode();
void setupGDT();
void setupIDT();
void setupPIC();

#endif /* SYSTEM_H_ */
