CC		= i586-elf-gcc
CFLAGS		= -Wall -Wextra -nostdlib -fno-builtin -nostartfiles -nodefaultlibs #-Werror
LD		= i586-elf-ld
EMU		= qemu-system-i386

TARGETS	= loader.o kernel.o kstd.o gdt.o

all: kernel.bin

.S.o:
	nasm -f elf -o $@ $<
	
.c.o:
	$(CC) $(CFLAGS) -o $@ -c $<
	
kernel.bin: $(TARGETS)
	$(LD) -T linker.ld -o $@ $^
	
clean:
	$(RM) $(TARGETS) kernel.bin kernel.img
	
start:
	$(EMU) -kernel kernel.bin
