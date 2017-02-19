#include <arch/i386/io/kernelio.h>
#include <arch/i386/console/serial.h>
#include <arch/i386/interrupt/irq.h>

#define PIC_A 0x20
#define PIC_B 0xA0
#define PIC_A_DATA 0x21
#define PIC_B_DATA 0xA1
#define PIC_ENDOFINT 0x20

void remap_PIC(char offset, char offset2) {
  unsigned char mask1;
  unsigned char mask2;

  mask1 = inb(PIC_A_DATA);
  mask2 = inb(PIC_B_DATA);

  outb(PIC_A, 0x11);          // init in cascade mode
  outb(PIC_B, 0x11);

  outb(PIC_A_DATA, offset);
  outb(PIC_A_DATA, offset2);  // set offset for the 2 PICs

  outb(PIC_A_DATA,
       4);                    // tells the master PIC there is a slave PIC at IRQ 2 (0000 0100)
  outb(PIC_B_DATA, 2);        // tells the slave PIC its on the second IRQ (0000 0010)

  outb(PIC_A_DATA, 0x01);
  outb(PIC_A_DATA, 0x01);

  outb(PIC_A_DATA, mask1);
  outb(PIC_A_DATA, mask2);
}

void PIC1_mask_irq(unsigned irq_mask) {
  outb(PIC_A_DATA,inb(PIC_A_DATA) | irq_mask);
}

void PIC2_mask_irq(unsigned irq_mask) {
  outb(PIC_B_DATA,inb(PIC_B_DATA) | irq_mask);
}


void div_by_0(void) { panic("division by 0"); }

void pit_isr(void) {
  //kout("PIT interrupt\n");
  outb(PIC_A, PIC_ENDOFINT);
}

void kbd_isr(void) {
  inb(0x60);
  kout("keyboard interrupt\n");
  outb(PIC_A, PIC_ENDOFINT);
}

void com1_isr(void) {
  kout_char(inb(COMPORT));
  outb(PIC_A, PIC_ENDOFINT);
}

void page_fault(void) {
  panic("Yep, that's a page fault!");
}