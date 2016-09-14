
AS = nasm
CC = i686-elf-gcc
LD = i686-elf-ld

kernel_x86:
	$(AS) -f elf32 kernelld.asm -o kloaderasm.o
	$(AS) -f elf32 arch/i386/irq.asm -o irqasm.o
	$(AS) -f elf32 arch/i386/paging.asm -o pagingasm.o
	$(CC)	-ffreestanding -c arch/i386/serial.c -o serial.o -std=gnu11 -O2 -W -Wall -Werror
	$(CC)	-ffreestanding -c arch/i386/paging.c -o paging.o -std=gnu11 -O2 -W -Wall -Werror
	$(CC)	-ffreestanding -c arch/i386/kernelio.c -o kernelio.o -std=gnu11 -O2 -W -Wall -Werror
	$(CC)	-ffreestanding -c arch/i386/idt.c -o idt.o -std=gnu11 -O2 -W -Wall -Werror
	$(CC)	-ffreestanding -c arch/i386/memory.c -o memory.o -std=gnu11 -O2 -W -Wall -Werror
	$(CC)	-ffreestanding -c arch/i386/irq.c -o irq.o -std=gnu11 -O2 -W -Wall -Werror
	$(CC)	-ffreestanding -c kernel/libc/libc.c -o libc.o -std=gnu11 -O2 -W -Wall -Werror
	$(CC)	-ffreestanding -c kernel.c -o kernel.o -std=gnu11 -O2 -W -Wall -Werror
	$(CC)	-T kernel.ld  -nostdlib  -o kernel.mkern kloaderasm.o memory.o irqasm.o idt.o serial.o irq.o kernelio.o paging.o kernel.o pagingasm.o libc.o
clean:
	rm -f kernel.mkern

install:
	echo "You wish you could install it like that"
