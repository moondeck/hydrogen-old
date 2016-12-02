#ifdef __i386__
  #define COM1 0x3F8

  #include "arch/i386/kernelio.h"
  #include "arch/i386/memory.h"
  #include "arch/i386/pfa.h"
  #include "arch/i386/idt.h"
  #include "arch/i386/irq.h"
  #include "arch/i386/serial.h"
  #include "kernel/libc/libc.h"
  #include "arch/i386/multiboot.h"

#endif
