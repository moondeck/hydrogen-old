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

  mov edx, 0x5000     ;x bytes are gonna get zero'd
  mov ecx, 0x00600000   ;at address 0x00000000
  mov ebx, 0x00000000  ;value that's gonna get written
  add edx, ecx
  call zero_page

  mov eax, 0x00600000  ;0x600000 is where we will put our tables
  mov ebx, 0x00601003  ;flags, writable, readable, the start of paging structures
  mov ecx, eax        ;ecx will keep the address to the structures
  mov edx, 0x00000000  ;edx will keep the address to the current page table (4 of them)
  mov esi, 0x00000000

  call id_page_kernel ;

	call kmain          ;calls the main kernel function in kernel.c
	cli
	hlt                 ;halts the cpu

id_page_kernel:       ;i have no idea how this even works
  inc esi
  mov [eax], ebx
  add eax, 4
  add ebx, 0x1000
  cmp esi, 0x04
  jne id_page_kernel

  mov eax, 0x00601000
  mov ebx, 0x00000003
  mov esi, 0x00000000

  jmp id_page_kernel2

id_page_kernel2:
  inc esi
  mov [eax], ebx
  add eax, 4
  add ebx, 0x1000
  cmp ebx, 0x00fff003
  je cr3load
  jmp id_page_kernel2


cr3load:
  mov eax, 0x00600000
  mov cr3, eax

  mov eax, cr0
  or  eax, 0x80010001
  mov cr0, eax

  ret


gdt_flush:            ;enables GDT
    lgdt [gp+2]       ;pointer to structure + 2 because of padding (16 bit)
    mov eax,0x10			;pointer to the data segment
    mov ds,eax
    mov es,eax
    mov fs,eax
    mov gs,eax
    mov ss,eax
    jmp 0x08:flush2		;far jump to the code segment, changes CS pointer

flush2:
    ret

zero_page:
  mov [ecx], ebx
  inc ecx
  cmp ecx, edx
  jne zero_page
  ret

done:
  ret

section .bss
stack:
stack_end:
