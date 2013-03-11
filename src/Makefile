CC		= i586-elf-gcc
CFLAGS		= -Wall -Wextra -nostdlib -fno-builtin -nostartfiles -nodefaultlibs #-Werror
LD		= i586-elf-ld
EMU		= qemu-system-i386

TARGETS	= loader.o kernel.o kstd.o string.o gdt.o idt.o isr.o interrupt.o

all: kernel.bin

.S.o:
	nasm -f elf -o $@ $<

.c.o:
	$(CC) $(CFLAGS) -o $@ -c $<

kernel.bin: $(TARGETS)
	$(LD) -T linker.ld -o $@ $^

clean:
	$(RM) $(TARGETS) kernel.bin kernel.img

bochs:
	cat stage1 stage2 pad kernel.bin > floppy.img

start:
	$(EMU) -kernel kernel.bin
