#include "serial.h"


void init_serial() {
  outb(serial_port + 1, 0x00);
  outb(serial_port + 2, 0xC7);

  outb(serial_port + 3, inb(serial_port + 3) | 0b10000000); //disable DLAB

  outb(serial_port + 0, 0x01);
  outb(serial_port + 1, 0x00); //set the baud rate to 115200 (no division)

  outb(serial_port + 3, inb(serial_port + 3) & ~0b10000000); //set DLAB


  outb(serial_port + 3, 0x03);
  outb(serial_port + 4, 0x01);
}

void com_1_interrupt(void) { kout_char(inb(COM1)); }
