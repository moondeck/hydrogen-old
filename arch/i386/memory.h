#include "kernelio.h"
#include "multiboot.h"
#include "kernelio.h"
#include "../../kernel/libc/libc.h"

void gdt_install();
void gdt_set_gate(int num, unsigned long base, unsigned long limit,
                  unsigned char access, unsigned char gran);
extern void gdt_flush();
void memory_detect(multiboot_info_t *mbd);

// struct gdt_entry gdt[3];
// struct gdt_ptr gp;
