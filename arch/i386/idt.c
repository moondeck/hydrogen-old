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

void idt_isr_gate(uint8_t interrupt, uint8_t flags, uint8_t selector, uint32_t address){
  idt[interrupt].base_low = address;
  idt[interrupt].base_high = (address >> 16);

  idt[interrupt].sel = selector;

  idt[interrupt].flags = (flags << 4) | 0b00001110;

}

void idt_install(){

  idtp.base = (uint32_t) &idt;
  idtp.size = sizeof(idt);

  idt_isr_gate(0x20,0b1000,0x08,(uint32_t) &interrupt_0x20);
  idt_isr_gate(0x21,0b1000,0x08,(uint32_t) &interrupt_0x21);
  idt_isr_gate(0x24,0b1000,0x08,(uint32_t) &interrupt_0x24);

  idt_load();

}
