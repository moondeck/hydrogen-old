#include "idt.h"

struct idt_entry {
  uint16_t base_low;
  uint16_t sel;
  uint8_t null;
  uint8_t flags;
  uint16_t base_high;
};

struct idt_ptr {
  uint16_t pad;
  uint16_t size;
  uint32_t base;
};

struct idt_entry idt[256];
struct idt_ptr idtp;

void idt_set_gate(unsigned char num, unsigned long base, unsigned short sel,
                  unsigned char flags) {
  idt[num].base_low = base;
  idt[num].base_high = (base >> 16);
  idt[num].sel = sel;
  idt[num].null = 0x00;
  idt[num].flags = flags;
}

void idt_install() {
  idtp.size = (sizeof(struct idt_entry) * 256) - 1;
  idtp.base = (uint16_t)&idt;


  mset((uint8_t *)idt, 0, sizeof(struct idt_entry) * 256);

  idt_set_gate(0x00, (unsigned long)exception_0x00, 0x08, 0x8E);
  idt_set_gate(0x20, (unsigned long)interrupt_0x20, 0x08, 0x8E);
  idt_set_gate(0x21, (unsigned long)interrupt_0x21, 0x08, 0x8E);

  idt_load();

}
