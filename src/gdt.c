/*
 * gdt.c
 *
 *  Created on: Mar 9, 2013
 *      Author: xandaros
 */

#include "system.h"
#include "stdint.h"

#define ACCESS_ACCESSED 1
#define ACCESS_RW 2
#define ACCESS_DC 4
#define ACCESS_EXECUTABLE 8
#define ACCESS_RING0 0
#define ACCESS_RING1 16
#define ACCESS_RING2 32
#define ACCESS_RING3 48
#define ACCESS_PRESENT 128

#define FLAG_32BIT 64
#define FLAG_PAGEGRAN 128

#define GDT_ENTRIES 3

typedef struct GDT_Entry
{
		uint16_t limit_lo;
		uint16_t base_lo;
		uint8_t base_mid;
		uint8_t access;
		uint8_t flags;
		uint8_t base_hi;
} __attribute__((packed)) GDT_Entry;

typedef struct
{
		uint16_t limit;
		void *ptr;
} __attribute__((packed)) GDT_Descriptor;

static GDT_Entry GDT[GDT_ENTRIES];

extern void flushGDT();

void registerEntry(uint8_t i, uint32_t limit, uint32_t base, uint8_t access, uint8_t flags)
{
	GDT_Entry *entry = GDT + i;
	entry->limit_lo = limit & 0xFFFF;
	entry->base_lo = base & 0xFFFF;
	entry->base_mid = (base >> 16) & 0xFF;
	entry->base_hi = (base >> 24) & 0xFF;
	entry->access = access | 0x10;

	entry->flags = (limit >> 16) & 0x0F;
	entry->flags |= flags & 0xF0;
}

void setupGDT()
{
	registerEntry(0, 0, 0, 0, 0);
	registerEntry(1, (uint32_t)0xFFFFF, 0, ACCESS_PRESENT | ACCESS_RING0 | ACCESS_EXECUTABLE | ACCESS_RW, FLAG_32BIT | FLAG_PAGEGRAN);
	registerEntry(2, (uint32_t)0xFFFFF, 0, ACCESS_PRESENT | ACCESS_RING0 | ACCESS_RW, FLAG_32BIT | FLAG_PAGEGRAN);

	GDT_Descriptor desc = {.limit = GDT_ENTRIES*8-1, .ptr = GDT};
	__asm__ __volatile__("lgdt %0" : : "m"(desc));
	flushGDT();
}
