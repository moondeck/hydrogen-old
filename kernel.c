#include "kernel.h"

/*
 * this is the main kernel loop, not much happening here.
 * its a mess
 */

void kmain(multiboot_info_t *mbd_ptr) {

  init_serial();
  gdt_install();

  remap_PIC(0x20, 0x28); //to be fixed
  idt_install();
  PIC1_mask_irq(0);


  // TODO: Proper keyboard init
  bootmsg(mbd_ptr);
  memory_detect(mbd_ptr);
  initkbd();

  //detect_cpu();
  //pfa_init();

  while (1) {
    asm("hlt");
  }

}
