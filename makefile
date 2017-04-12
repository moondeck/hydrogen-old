#TODO rework the retarded makefile please

AS = nasm
CC = i686-elf-gcc
LD = i686-elf-ld

CFLAGS = -ffreestanding -Wall -Wextra -g

kernel_x86 : kernelloader.o irqasm.o hwdetectasm.o vmmasm.o serial.o kernelio.o idt.o memory.o irq.o kbd.o io.o vmm.o hwdetect.o kprintf.o libc.o kernel.o ata.o
	@echo "[ LINK ]" $@
	@$(CC) -g -nostdlib -T arch/i386/kernel.ld -o hydrogen kernelloader.o kernel.o irqasm.o idt.o \
	kbd.o memory.o serial.o irq.o kernelio.o io.o vmm.o vmmasm.o hwdetect.o hwdetectasm.o ata.o \
	libc.o kprintf.o -lgcc

kernelloader.o :
	@$(AS) -f elf32 arch/i386/kernelld.asm 											-o kernelloader.o
irqasm.o :
	@$(AS) -f elf32 arch/i386/interrupt/irq.asm 								-o irqasm.o
hwdetectasm.o :
	@$(AS) -f elf32 arch/i386/hwid/hwdetect.asm 								-o hwdetectasm.o
vmmasm.o :
	@$(AS) -f elf32 arch/i386/vmm/vmm.asm 											-o vmmasm.o

serial.o :
	@$(CC)	$(CFLAGS) -c arch/i386/console/serial.c 						-I include			-o serial.o
kernelio.o :
	@$(CC)	$(CFLAGS) -c arch/i386/io/kernelio.c 								-I include			-o kernelio.o
idt.o :
	@$(CC)	$(CFLAGS) -c arch/i386/interrupt/idt.c 							-I include			-o idt.o
memory.o :
	@$(CC)	$(CFLAGS) -c arch/i386/memory/memory.c 							-I include			-o memory.o
irq.o :
	@$(CC)	$(CFLAGS) -c arch/i386/interrupt/irq.c 							-I include			-o irq.o
kbd.o :
	@$(CC)	$(CFLAGS) -c arch/i386/kbd/kbd.c 										-I include			-o kbd.o
io.o :
	@$(CC)	$(CFLAGS) -c arch/i386/io/io.c 											-I include 			-o io.o
vmm.o :
	@$(CC)	$(CFLAGS) -c arch/i386/vmm/vmm.c 										-I include 			-o vmm.o
hwdetect.o :
	@$(CC)	$(CFLAGS) -c arch/i386/hwid/hwdetect.c 							-I include 			-o hwdetect.o
ata.o :
	@$(CC)	$(CFLAGS) -c arch/i386/ata/ata.c 										-I include			-o ata.o

kprintf.o :
	@$(CC)	$(CFLAGS) -c kernel/libc/kprintf.c									-I include			-o kprintf.o
libc.o :
	@$(CC)	$(CFLAGS) -c kernel/libc/libc.c 										-I include			-o libc.o
kernel.o :
	@$(CC)	$(CFLAGS) -c arch/i386/kernel.c 										-I include			-o kernel.o

clean:
	rm -f hydrogen *.o

install:
	echo "You wish you could install it like that"

loc:
	git ls-files | xargs cloc
