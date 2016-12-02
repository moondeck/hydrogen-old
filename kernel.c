#include "kernel.h"

/*
 * this is the main kernel loop, not much happening here.
 * its a mess
 */

void kmain(multiboot_info_t *mbd_ptr) {

  gdt_install();
  //  memory_init();
  //  setup_paging();
  idt_install();
  remap_PIC(0x20, 0x28);

  // TODO: Proper keyboard init
  init_serial(COM1);
  bootmsg(mbd_ptr);
  memory_detect(mbd_ptr);
  pfa_init();


  asm("hlt");
}
