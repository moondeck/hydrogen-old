#include "kernelio.h"
#include "../../kernel/libc/libc.h"

void idt_set_gate(unsigned char num, unsigned long base, unsigned short sel,
                  unsigned char flags);
extern void idt_install();
extern void idt_load();
// lol
