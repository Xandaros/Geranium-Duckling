/*
 * idt.c
 *
 *  Created on: Mar 10, 2013
 *      Author: xandaros
 */

#include "stdint.h"
#include "string.h"
#include "system.h"

//extern void loadIDT();

struct idt_entry
{
		uint16_t base_lo;
		uint16_t sel;
		uint8_t zero;
		uint8_t flags;
		uint16_t base_hi;
} __attribute__((packed));

struct idt_ptr
{
		uint16_t limit;
		void *base;
}__attribute__((packed));

struct idt_entry idt[256];
struct idt_ptr idt_ptr;

extern void isr0();
extern void isr1();
extern void isr2();
extern void isr3();
extern void isr4();
extern void isr5();
extern void isr6();
extern void isr7();
extern void isr8();
extern void isr9();
extern void isr10();
extern void isr11();
extern void isr12();
extern void isr13();
extern void isr14();
extern void isr15();
extern void isr16();
extern void isr17();
extern void isr18();
extern void isr19();
extern void isr20();
extern void isr21();
extern void isr22();
extern void isr23();
extern void isr24();
extern void isr25();
extern void isr26();
extern void isr27();
extern void isr28();
extern void isr29();
extern void isr30();
extern void isr31();
extern void isr32();
extern void isr33();
extern void isr34();
extern void isr35();
extern void isr36();
extern void isr37();
extern void isr38();
extern void isr39();
extern void isr40();
extern void isr41();
extern void isr42();
extern void isr43();
extern void isr44();
extern void isr45();
extern void isr46();

void setGate(uint8_t i, uint32_t base, uint16_t sel, uint8_t flags)
{
	struct idt_entry *ptr = idt+i;
	ptr->base_lo = base & 0xFFFF;
	ptr->base_hi = (base >> 16) & 0xFFFF;

	ptr->sel = sel & 0xFFFF;
	ptr->zero = 0;
	ptr->flags = flags;
}

void setupIDT()
{
	idt_ptr.limit = 2047; // (256 * 8) - 1
	idt_ptr.base = idt;

	memset(idt, 0, 2048);

	setGate(0, (uint32_t)isr0, 0x8, 0x8E);
	setGate(1, (uint32_t)isr1, 0x8, 0x8E);
	setGate(2, (uint32_t)isr2, 0x8, 0x8E);
	setGate(3, (uint32_t)isr3, 0x8, 0x8E);
	setGate(4, (uint32_t)isr4, 0x8, 0x8E);
	setGate(5, (uint32_t)isr5, 0x8, 0x8E);
	setGate(6, (uint32_t)isr6, 0x8, 0x8E);
	setGate(7, (uint32_t)isr7, 0x8, 0x8E);
	setGate(8, (uint32_t)isr8, 0x8, 0x8E);
	setGate(9, (uint32_t)isr9, 0x8, 0x8E);
	setGate(10, (uint32_t)isr10, 0x8, 0x8E);
	setGate(11, (uint32_t)isr11, 0x8, 0x8E);
	setGate(12, (uint32_t)isr12, 0x8, 0x8E);
	setGate(13, (uint32_t)isr13, 0x8, 0x8E);
	setGate(14, (uint32_t)isr14, 0x8, 0x8E);
	setGate(15, (uint32_t)isr15, 0x8, 0x8E);
	setGate(16, (uint32_t)isr16, 0x8, 0x8E);
	setGate(17, (uint32_t)isr17, 0x8, 0x8E);
	setGate(18, (uint32_t)isr18, 0x8, 0x8E);
	setGate(19, (uint32_t)isr19, 0x8, 0x8E);
	setGate(20, (uint32_t)isr20, 0x8, 0x8E);
	setGate(21, (uint32_t)isr21, 0x8, 0x8E);
	setGate(22, (uint32_t)isr22, 0x8, 0x8E);
	setGate(23, (uint32_t)isr23, 0x8, 0x8E);
	setGate(24, (uint32_t)isr24, 0x8, 0x8E);
	setGate(25, (uint32_t)isr25, 0x8, 0x8E);
	setGate(26, (uint32_t)isr26, 0x8, 0x8E);
	setGate(27, (uint32_t)isr27, 0x8, 0x8E);
	setGate(28, (uint32_t)isr28, 0x8, 0x8E);
	setGate(29, (uint32_t)isr29, 0x8, 0x8E);
	setGate(30, (uint32_t)isr30, 0x8, 0x8E);
	setGate(31, (uint32_t)isr31, 0x8, 0x8E);
	setGate(32, (uint32_t)isr32, 0x8, 0x8E);
	setGate(33, (uint32_t)isr33, 0x8, 0x8E);
	setGate(34, (uint32_t)isr34, 0x8, 0x8E);
	setGate(35, (uint32_t)isr35, 0x8, 0x8E);
	setGate(36, (uint32_t)isr36, 0x8, 0x8E);
	setGate(37, (uint32_t)isr37, 0x8, 0x8E);
	setGate(38, (uint32_t)isr38, 0x8, 0x8E);
	setGate(39, (uint32_t)isr39, 0x8, 0x8E);
	setGate(40, (uint32_t)isr40, 0x8, 0x8E);
	setGate(41, (uint32_t)isr41, 0x8, 0x8E);
	setGate(42, (uint32_t)isr42, 0x8, 0x8E);
	setGate(43, (uint32_t)isr43, 0x8, 0x8E);
	setGate(44, (uint32_t)isr44, 0x8, 0x8E);
	setGate(45, (uint32_t)isr45, 0x8, 0x8E);
	setGate(46, (uint32_t)isr46, 0x8, 0x8E);

	__asm__ __volatile__ ("lidt %0" : : "m"(idt_ptr));
}
