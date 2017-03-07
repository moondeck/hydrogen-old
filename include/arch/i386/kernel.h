#ifdef __i386__
  #define COM1 0x3F8

  #include <cpuid.h>

  #include <arch/i386/kbd/kbd.h>
  #include <arch/i386/io/kernelio.h>
  #include <arch/i386/memory/memory.h>
  #include <arch/i386/interrupt/idt.h>
  #include <arch/i386/interrupt/irq.h>
  #include <arch/i386/console/serial.h>
  #include <arch/i386/memory/multiboot.h>
  #include <arch/i386/vmm/vmm.h>

#endif

#include <libc/libc.h>
#include <libc/kprintf.h>