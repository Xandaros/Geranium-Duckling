/*
 * interrupt.c
 *
 *  Created on: Mar 10, 2013
 *      Author: xandaros
 */

#include "stdint.h"
#include "kstdio.h"
#include "system.h"

extern void irq_handler(registers_t registers, uint32_t id, uint32_t error);

void isr_handler(registers_t registers, uint32_t id, uint32_t error)
{
	if (id == 13) return;
	if (id >= 0x20 && id <=0x2F)
	{
		irq_handler(registers, id-0x20, error);
		return;
	}
	char buffer[4];
	print("Unhandled interrupt: ");
	println(itoa(id, buffer, 10));
}
