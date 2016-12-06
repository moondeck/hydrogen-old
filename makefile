
AS = nasm
CC = i686-elf-gcc
LD = i686-elf-ld

CFLAGS = -ffreestanding -Wall -Wextra

RED = \033[0;31m
GREEN = \033[0;32m
YELLOW = \033[1;33m
CLEAR = \033[0m

kernel_x86:
	clear

	@echo "[ ASM ]" $@
	@$(AS) -f elf32 kernelld.asm -o kloaderasm.o
	@$(AS) -f elf32 arch/i386/irq.asm -o irqasm.o

	@echo "[ GCC ]" $@
	@$(CC)	$(CFLAGS) -c arch/i386/serial.c -o serial.o
	@$(CC)	$(CFLAGS) -c arch/i386/kernelio.c -o kernelio.o
	@$(CC)	$(CFLAGS) -c arch/i386/idt.c -o idt.o
	@$(CC)	$(CFLAGS) -c arch/i386/memory.c -o memory.o
	@$(CC)	$(CFLAGS) -c arch/i386/pfa.c -o pfa.o
	@$(CC)	$(CFLAGS) -c arch/i386/irq.c -o irq.o
	@$(CC)	$(CFLAGS) -c arch/i386/kbd.c -o kbd.o

	@$(CC)	$(CFLAGS) -c kernel/libc/libc.c -o libc.o
	@$(CC)	$(CFLAGS) -c kernel.c -o kernel.o

	@echo "[ LINK ]" $@
	@$(CC) -nostdlib -T kernel.ld -o kernel.mkern kloaderasm.o kernel.o kbd.o memory.o pfa.o irqasm.o idt.o serial.o irq.o kernelio.o libc.o -lgcc

clean:
	rm -f kernel.mkern

install:
	echo "You wish you could install it like that"

loc:
	git ls-files | xargs cloc
