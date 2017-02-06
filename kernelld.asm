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


begin:
  push ebx

  cli
  mov eax, 0x000000   ;the beginning of memory, thats also where we will put our tables
  mov ebx, 0x000000
  mov ecx, 0x000000
  mov edx, 0x000000
  inc ecx

  call id_page_kernel ;
	call kmain          ;calls the main kernel function in kernel.c
	cli
	hlt                 ;halts the cpu

id_page_kernel:
  or ebx, 1

  mov [eax*4], ebx
  add ebx, 4096
  inc eax
  cmp eax, 2048
  je id_page_kernel2
  jmp id_page_kernel

id_page_kernel2:
  mov ebx, 0x00000000
  mov esi, 0x00000000
  or esi, 1

  mov [eax*4], esi
  inc eax

  add esi, 0x1000
  mov [eax*4], esi
  dec eax
  
  mov edx, 4
  mul edx
  
  mov cr3, eax
  

  mov eax, cr0
  or eax, 0x80000000
  mov cr0, eax
  ret

  

id_page_base dd 0x000000
id_page_blocks db 0x02 ;we only need 2 blocks, as 2x1024x4096 = 8 megs

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
    ret	
section .bss
stack:
stack_end: