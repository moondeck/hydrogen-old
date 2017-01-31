bits 32							;telling NASM we are using 32 bits

section .text       ;multiboot header, needed for GRUB and other multiboot bootloaders
      dd 0x1BADB002
      dd 0x00
      dd - (0x1BADB002 + 0x00)


global begin
extern kmain

extern setgdt
global gdt_flush
extern gp

extern setup_paging
extern page_dirs

global idt_load
extern idtp
global interrupt

global kbd_wait
global kbd_wait2

section .data

  jmp begin

begin:
  cli
  push ebx
	call kmain          ;calls the main kernel function in kernel.c
	cli
	hlt                 ;halts the cpu


gdt_flush:            ;enables GDT
    lgdt [gp+2]
    mov eax,0x10			;pointer to the data segment
    mov ds,eax
    mov es,eax
    mov fs,eax
    mov gs,eax
    mov ss,eax
    jmp 0x08:flush2		;far jump to the code segment, changes CS pointer

flush2:
    ret						   	;returns

section .bss
stack:
stack_end: