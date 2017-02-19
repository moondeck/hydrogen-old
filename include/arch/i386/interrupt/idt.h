#include <stdint.h>

void idt_isr_gate(uint8_t interrupt, uint8_t flags, uint8_t selector, uint32_t address);
extern void idt_install();
extern void idt_load();

extern void exception_0x00();
extern void exception_0x0E();

extern void interrupt_0x20();
extern void interrupt_0x21();
extern void interrupt_0x24();

