extern kmain

global loader
global magic
global mbd

MAGIC equ 0x1BADB002
MODULEALIGN equ 1<<0				; align loaded modules on page boundaries
MEMINFO equ 1<<1					; provide memory map
FLAGS equ MODULEALIGN | MEMINFO
CHECKSUM equ -(MAGIC + FLAGS)

section .text

align 4
	dd MAGIC
	dd FLAGS
	dd CHECKSUM

STACKSIZE equ 0x4000	;16k

loader:
	mov esp, stack + STACKSIZE		; Setup stack
	mov [magic], eax
	mov [mbd], ebx					; Copy multiboot info

	call kmain						; Call main function

.hang:
	hlt
	jmp .hang						; Kernel exited, loop eternally... for now

section .bss
align 4
	stack: resb STACKSIZE
	magic: resd 1
	mbd: resd 1