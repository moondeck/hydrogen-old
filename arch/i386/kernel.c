#include <arch/i386/kernel.h>

/*
 * this is the main kernel loop, not much happening here.
 */

extern int get_hileaf();

void kmain(multiboot_info_t *mbd_ptr) {

  gdt_install();
  remap_PIC(0x20, 0x28);
  idt_install();
  PIC1_mask_irq(1);

  initkbd();
  init_serial();

  bootmsg(mbd_ptr);

  memory_init(mbd_ptr);

  pfa_init();

  init_paging();
  
  while (1) {
    brk();
  }

}
