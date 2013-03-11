/*
 * kstd.c
 *
 *  Created on: Mar 9, 2013
 *      Author: xandaros
 */

#include "kstdio.h"

static unsigned char *videoram = (unsigned char *)0xB8000;
unsigned char cur_x, cur_y;

void putchar(unsigned char c)
{
	word *ptr = (word *)videoram + 80*cur_y + cur_x;
	*ptr = 0x0F<<8 | c;
}

void print(char *s)
{
	while (*s != 0)
	{
		putchar(*s++);
		cur_x++;
	}
}

void println(char *s)
{
	print(s);
	cur_y++;
	cur_x = 0;
}

void clear()
{
	word *ptr = (word *)videoram;
	int y;
	for (y = 0; y < 25; y++)
	{
		int x;
		for (x = 0; x < 80; x++)
		{
			*ptr++ = 0;
		}
	}
}

void outb(word port, byte value)
{
	__asm__ __volatile__("outb %0, %1" : : "a"(value), "Nd"(port));
}

byte inb(word port)
{
	byte ret;
	__asm__ __volatile__("inb %1, %0" : "=a"(ret) : "Nd"(port));
	return ret;
}

void outw(word port, word value)
{
	__asm__ __volatile__("outw %0, %1" : : "a"(value), "Nd"(port));
}

word inw(word port)
{
	word ret;
	__asm__ __volatile__("inw %1, %0" : "=a"(ret) : "Nd"(port));
	return ret;
}

void io_wait()
{
    __asm__ __volatile__("outb %%al, $0x80" : : "a"(0));
}

char *itoa(sint32_t i, char *buffer, int base)
{
	char *ptr = buffer, *ptr1 = buffer;
	int temp;
	//sanity check
	if (base < 2 || base > 36)
	{
		*buffer = '\0';
		return buffer;
	}

	//Generate the string... backwards to save time
	do
	{
		temp = i;
		i /= base;
		*ptr++ = "zxywvutsrqponmlkjihgfedcba9876543210123456789abcdefghijklmnopqrstuvwxyz"[35 + (temp - i * base)];
	} while (i);

	//Apply sign if applicable
	if (i < 0)
		*ptr++ = '-';
	//Strings end
	*ptr-- = '\0';

	//reverse result
	char tempc;
	while (ptr1 < ptr)
	{
		tempc = *ptr1;
		*ptr1++ = *ptr;
		*ptr-- = tempc;
	}

	return buffer;
}
