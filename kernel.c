#include "kernel.h"

#define KBD_DAT 0x60
#define KBD_STACMD 0x64
#define COM1 0x3F8

/*
 * this is the main kernel loop, not much happening here.
 * its a mess
 */

void kmain(multiboot_info_t *mbd_ptr) {
  gdt_install();
  idt_install();
  // setup_paging();
  remap_PIC(0x20, 0x28);

  // TODO: Proper keyboard init
  mask_irq(0);
  init_serial(COM1);
  bootmsg(mbd_ptr);
  memory_detect(mbd_ptr);
  while (1) {
    asm("hlt");
  }
}
