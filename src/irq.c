/*
 * irq.c
 *
 *  Created on: Mar 11, 2013
 *      Author: xandaros
 */

#include "system.h"
#include "kstdio.h"

#define PIC1_COMMAND	0x20
#define PIC1_DATA		0x21
#define PIC2_COMMAND	0xA0
#define PIC2_DATA		0xA1

#define ICW1_ICW4		0x01		/* ICW4 needed */
#define ICW1_SINGLE		0x02		/* Single (cascade) mode */
#define ICW1_INTERVAL4	0x04		/* Call address interval 4 (8) */
#define ICW1_LEVEL		0x08		/* Level triggered (edge) mode */
#define ICW1_INIT		0x10		/* Initialization - required! */

#define ICW4_8086		0x01		/* 8086/88 (MCS-80/85) mode */
#define ICW4_AUTO		0x02		/* Auto (normal) EOI */
#define ICW4_BUF_SLAVE	0x08		/* Buffered mode/slave */
#define ICW4_BUF_MASTER	0x0C		/* Buffered mode/master */
#define ICW4_SFNM		0x10		/* Special fully nested (not) */

void setupPIC()
{
	outb(PIC1_COMMAND, ICW1_INIT | ICW1_ICW4);
	outb(PIC2_COMMAND, ICW1_INIT | ICW1_ICW4);
	outb(PIC1_DATA, 0x20);
	outb(PIC2_DATA, 0x28);
	outb(PIC1_DATA, 4);
	outb(PIC2_DATA, 2);
	outb(PIC1_DATA, ICW4_8086);
	outb(PIC2_DATA, ICW4_8086);
}

void irq_handler(registers_t registers, uint32_t id, uint32_t error)
{
	//Spurious?
	if (id == 7)
	{
		outb(PIC1_COMMAND, 0x0B);
		if (inb(PIC1_COMMAND) == 0)
			return; //Spurious Interrupt
	}
	else if (id == 15)
	{
		outb(PIC2_COMMAND, 0x0B);
		if (inb(PIC2_COMMAND) == 0)
		{
			outb(PIC1_COMMAND, 0x20); //EOI to master
			return;
		}
	}

	//The actual handler

	if (id == 0) return;

	char buffer[4];
	print("Unhandled IRQ: ");
	println(itoa(id, buffer, 10));



	//Send EOI
	if (id >= 8)
		outb(PIC2_COMMAND, 0x20);
	outb(PIC1_COMMAND, 0x20);
}
