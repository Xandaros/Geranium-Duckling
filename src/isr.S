%macro ISR_NOERROR 1
	global isr%1
	isr%1:
		cli
		push byte 0
		push byte %1
		jmp isr_common
%endmacro

%macro ISR_ERROR 1
	global isr%1
	isr%1:
		cli
		push byte %1
		jmp isr_common
%endmacro

ISR_NOERROR 0
ISR_NOERROR 1
ISR_NOERROR 2
ISR_NOERROR 3
ISR_NOERROR 4
ISR_NOERROR 5
ISR_NOERROR 6
ISR_NOERROR 7
ISR_ERROR 8
ISR_NOERROR 9
ISR_ERROR 10
ISR_ERROR 11
ISR_ERROR 12
ISR_ERROR 13
ISR_ERROR 14
ISR_NOERROR 15
ISR_NOERROR 16
ISR_NOERROR 17
ISR_NOERROR 18
ISR_NOERROR 19
ISR_NOERROR 20
ISR_NOERROR 21
ISR_NOERROR 22
ISR_NOERROR 23
ISR_NOERROR 24
ISR_NOERROR 25
ISR_NOERROR 26
ISR_NOERROR 27
ISR_NOERROR 28
ISR_NOERROR 29
ISR_NOERROR 30
ISR_NOERROR 31

extern isr_handler

isr_common:
	pusha					; save all registers to have a clean environment for the interrupt
	mov ax,ds
	push eax				; save DS

	mov ax,0x10				; reinit segments to 0x10
	mov ds,ax
	mov es,ax
	mov fs,ax
	mov gs,ax

	call isr_handler		; call C-function

	pop eax					; restore segments
	mov ds,ax
	mov es,ax
	mov fs,ax
	mov gs,ax

	popa					; restore registers
	add esp,8				; pop 2 values (interrupt id and error code)
	sti						; re-enable interrupts
iret						; return to where we left off
