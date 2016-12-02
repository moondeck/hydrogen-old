#include "kernelio.h"
#include "multiboot.h"
#include "../../kernel/libc/libc.h"

extern char kernel_start;
extern char kernel_end;
extern char text_end;
extern char data_end;
extern char bss_end;

extern unsigned int firstpf;

void gdt_install();
void gdt_set_gate(int num, unsigned long base, unsigned long limit,
                  unsigned char access, unsigned char gran);
extern void gdt_flush();
void memory_detect(multiboot_info_t *mbd);
void pfa_init();
