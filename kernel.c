#include "kernel.h"

/*
 * this is the main kernel loop, not much happening here.
 * its a mess
 */

void kmain(multiboot_info_t *mbd_ptr) {

  char test[10];
  init_serial();
  gdt_install();
  //memory_init();
  //setup_paging();
  remap_PIC(0x20, 0x28);
  //idt_install();
  PIC1_mask_irq(0b00000001);


  // TODO: Proper keyboard init
  bootmsg(mbd_ptr);
  memory_detect(mbd_ptr);

  detect_cpu();
  //pfa_init();

  while (1) {
    asm("hlt");
  }

}
