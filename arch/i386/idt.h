#include "kernelio.h"
#include "../../kernel/libc/libc.h"

#include <stdint.h>

void idt_set_gate(unsigned char num, unsigned long base, unsigned short sel,
                  unsigned char flags);
extern void idt_install();
extern void idt_load();

extern void exception_0x00();
extern void interrupt_0x20();
extern void interrupt_0x21();
extern void interrupt_0x24();
// lol
