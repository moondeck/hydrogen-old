#include <arch/i386/kernel.h>

/*
 * this is the main kernel loop, not much happening here.
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
  cpuid(0x110000, 0x110010);
  //brk();

  init_paging();
  brk();
  uint32_t *page_fault_should_not_happen = 0xFFFFFC;
  *page_fault_should_not_happen = 0xdeadbeef;
  kprintf("%x\n",(int) *page_fault_should_not_happen );
  while (1) {
    brk();
  }

}
