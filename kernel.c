#include "kernel.h"

/*
 * this is the main kernel loop, not much happening here.
 * its a mess
 */

void kmain(multiboot_info_t *mbd_ptr) {

  init_serial();
  gdt_install();
  remap_PIC(0x20, 0x28);
  idt_install();
  PIC1_mask_irq(1);

  initkbd();

  bootmsg(mbd_ptr);

  memory_init(mbd_ptr);

  pfa_init();
  cpuid(0x110000, 0x110020);
  alloc_pframe();

  init_paging();
  while (1) {
    brk();
  }

}
