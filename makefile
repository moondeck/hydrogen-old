
AS = nasm
CC = i686-elf-gcc
LD = i686-elf-ld

CFLAGS = -ffreestanding -Wall -Wextra -g

kernel_x86:
	clear

	@echo "[ ASM ]" $@
	@$(AS) -f elf32 kernelld.asm 											-o kloaderasm.o
	@$(AS) -f elf32 arch/i386/interrupt/irq.asm 							-o irqasm.o
	@$(AS) -f elf32 arch/i386/hwid/hwdetect.asm 							-o hwdetectasm.o
	@$(AS) -f elf32 arch/i386/vmm/vmm.asm 									-o vmmasm.o

	@echo "[ GCC ]" $@
	@$(CC)	$(CFLAGS) -c arch/i386/console/serial.c 	-I include			-o serial.o
	@$(CC)	$(CFLAGS) -c arch/i386/io/kernelio.c 		-I include			-o kernelio.o
	@$(CC)	$(CFLAGS) -c arch/i386/interrupt/idt.c 		-I include			-o idt.o
	@$(CC)	$(CFLAGS) -c arch/i386/memory/memory.c 		-I include			-o memory.o
	@$(CC)	$(CFLAGS) -c arch/i386/interrupt/irq.c 		-I include			-o irq.o
	@$(CC)	$(CFLAGS) -c arch/i386/kbd/kbd.c 			-I include			-o kbd.o
	@$(CC)	$(CFLAGS) -c arch/i386/io/io.c 				-I include 			-o io.o
	@$(CC)	$(CFLAGS) -c arch/i386/vmm/vmm.c 			-I include 			-o vmm.o
	@$(CC)	$(CFLAGS) -c arch/i386/hwid/hwdetect.c 		-I include 			-o hwdetect.o

	@$(CC)	$(CFLAGS) -c kernel/libc/kprintf.c			-I include			-o kprintf.o
	@$(CC)	$(CFLAGS) -c kernel/libc/libc.c 			-I include			-o libc.o
	@$(CC)	$(CFLAGS) -c kernel.c 						-I include			-o kernel.o

	@echo "[ LINK ]" $@
	@$(CC) -g -nostdlib -T kernel.ld -o kernel.elf kloaderasm.o kernel.o irqasm.o idt.o \
	kbd.o memory.o serial.o irq.o kernelio.o io.o vmm.o vmmasm.o hwdetect.o hwdetectasm.o libc.o kprintf.o -lgcc

clean:
	rm -f kernel.elf *.o

install:
	echo "You wish you could install it like that"

loc:
	git ls-files | xargs cloc
