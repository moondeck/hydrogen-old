#include <stdint.h>
#include <arch/i386/memory/multiboot.h>

#define PAGE_SIZE 4096
#define KERNEL_LOAD_POINT 0x100000
#define PFA_STACK_POINTER 0x120000
#define MEM_REGLIST (PFA_STACK_POINTER + 0x400000)

typedef uint32_t pfptr_t;

extern void kernel_start;
extern void kernel_end;
extern void text_end;
extern void data_end;
extern void bss_end;

extern uint32_t firstpf;

void gdt_install();
void gdt_set_gate(int num, unsigned long base, unsigned long limit,
                  unsigned char access, unsigned char gran);
extern void gdt_flush();
void memory_init(multiboot_info_t *mbd);
uint32_t pfa_init();
uint32_t pfa_pop();
uint32_t pfa_push(uint32_t pushvalue);
pfptr_t alloc_pframe();
pfptr_t dealloc_pframe(pfptr_t pframe_address);
