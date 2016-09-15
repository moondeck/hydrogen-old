
AS = nasm
CC = i686-elf-gcc
LD = i686-elf-ld

RED = \033[0;31m
GREEN = \033[0;32m
YELLOW = \033[1;33m
CLEAR = \033[0m

kernel_x86:
	clear

	#assembly part
	@echo "[ $(RED)ASM$(CLEAR) ]" $@
	@$(AS) -f elf32 kernelld.asm -o kloaderasm.o
	@$(AS) -f elf32 arch/i386/irq.asm -o irqasm.o
	@$(AS) -f elf32 arch/i386/paging.asm -o pagingasm.o

	#compiling stuff
	@echo "[ $(GREEN)GCC$(CLEAR) ]" $@
	@$(CC)	-ffreestanding -c arch/i386/serial.c -o serial.o -std=gnu11 -O2 -W -Wall -Werror
	@$(CC)	-ffreestanding -c arch/i386/paging.c -o paging.o -std=gnu11 -O2 -W -Wall -Werror
	@$(CC)	-ffreestanding -c arch/i386/kernelio.c -o kernelio.o -std=gnu11 -O2 -W -Wall -Werror
	@$(CC)	-ffreestanding -c arch/i386/idt.c -o idt.o -std=gnu11 -O2 -W -Wall -Werror
	@$(CC)	-ffreestanding -c arch/i386/memory.c -o memory.o -std=gnu11 -O2 -W -Wall -Werror
	@$(CC)	-ffreestanding -c arch/i386/irq.c -o irq.o -std=gnu11 -O2 -W -Wall -Werror
	@$(CC)	-ffreestanding -c kernel/libc/libc.c -o libc.o -std=gnu11 -O2 -W -Wall -Werror
	@$(CC)	-ffreestanding -c kernel.c -o kernel.o -std=gnu11 -O2 -W -Wall -Werror

	#link dat shit
	@echo "[ $(YELLOW)LINK$(CLEAR) ]" $@
	@$(CC)	-T kernel.ld  -nostdlib  -o kernel.mkern kloaderasm.o memory.o irqasm.o idt.o serial.o irq.o kernelio.o paging.o kernel.o pagingasm.o libc.o

clean:
	rm -f kernel.mkern

install:
	echo "You wish you could install it like that"
