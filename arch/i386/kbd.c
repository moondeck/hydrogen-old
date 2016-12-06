#include "kbd.h"

void initkbd() {
  char KBD_DATA_var;

  outb(KBD_CMD,0xAD);
  inb(KBD_DATA);

  outb(KBD_CMD,0x20);
  KBD_DATA_var = inb(KBD_DATA);

  KBD_DATA_var = (0 << 1) | (0 << 6) | (1 << 0);

  outb(KBD_CMD,0x60);
  outb(KBD_DATA,KBD_DATA_var);

  outb(KBD_CMD,0xAA);
  if (inb(KBD_DATA) == 0x55) {
    kout("keyboard controller test passed\n");
  } else {
    halt_system_err("No keyboard controller detected, cannot continue");
  }

  while (inb(KBD_CMD) & (1 << 1)) ;

  outb(KBD_CMD,0xAE);
  outb(KBD_DATA,0xFF);

}
