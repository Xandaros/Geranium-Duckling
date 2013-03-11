/*
 * system.h
 *
 *  Created on: Mar 10, 2013
 *      Author: xandaros
 */

#ifndef SYSTEM_H_
#define SYSTEM_H_

#define BochsBreak() __asm__ __volatile__("xchgw %%bx, %%bx" :);

extern void protectedMode();
void setupGDT();
void setupIDT();

#endif /* SYSTEM_H_ */
