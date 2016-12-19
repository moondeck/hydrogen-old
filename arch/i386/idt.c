#include "kernelio.h"

extern void idt_load();

extern void exception_0x00();
extern void interrupt_0x20();
extern void interrupt_0x21();
extern void interrupt_0x24();

struct idt_entry {
  unsigned short base_low;
  unsigned short sel;
  unsigned char null;
  unsigned char flags;
  unsigned short base_high;
} __attribute__((packed, aligned(8)));

struct idt_pointer {
  unsigned short limit;
  unsigned int base;
} __attribute__((packed, aligned(8)));

struct idt_entry idt[256];
struct idt_pointer idtp;

void idt_set_gate(unsigned char num, unsigned long base, unsigned short sel,
                  unsigned char flags) {
  idt[num].base_low = base;
  idt[num].base_high = base >> 16;
  idt[num].sel = sel;
  idt[num].null = 0x00;
  idt[num].flags = flags;
}

void idt_install() {
  idtp.limit = (sizeof(struct idt_entry) * 256) - 1;
  idtp.base = (unsigned)&idt;
  mset((unsigned char*)idt, 0, sizeof(struct idt_entry) * 256);
  idt_set_gate(0x00, (unsigned)exception_0x00, 0x08, 0x8E);
  idt_set_gate(0x20, (unsigned)interrupt_0x20, 0x08, 0x8E);
  idt_set_gate(0x21, (unsigned)interrupt_0x21, 0x08, 0x8E);
  //idt_set_gate(0x24, (unsigned)interrupt_0x24, 0x08, 0x8E);
  idt_load();
}
