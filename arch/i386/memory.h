#include "kernelio.h"
#include "multiboot.h"
#include "../../kernel/libc/libc.h"
#include "../../kernel/libc/kprintf.h"

#define KERNEL_LOAD_POINT 0x100000
#define PFA_STACK_POINTER 0x110000

extern int kernel_start;
extern int kernel_end;
extern int text_end;
extern int data_end;
extern int bss_end;

extern uint32_t firstpf;

void gdt_install();
void gdt_set_gate(int num, unsigned long base, unsigned long limit,
                  unsigned char access, unsigned char gran);
extern void gdt_flush();
void memory_init(multiboot_info_t *mbd);
uint32_t pfa_init();
