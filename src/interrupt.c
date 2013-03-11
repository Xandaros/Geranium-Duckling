/*
 * interrupt.c
 *
 *  Created on: Mar 10, 2013
 *      Author: xandaros
 */

#include "stdint.h"
#include "kstd.h"

typedef struct
{
		uint32_t ds;
		uint32_t edi, esi, ebp, esp, ebx, edx, ecx, eax;
} registers_t;

void isr_handler(registers_t registers, uint32_t id, uint32_t error)
{
	if (id == 13) return;
	char buffer[4];
	print("Unhandled interrupt: ");
	println(itoa(id, buffer, 10));
}
