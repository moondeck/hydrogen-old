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

void kout_char(char koutchar) {  // outputs a character to serial
  outb(COM1, koutchar);
}

char serial_io_wait() {
  while (!(inb(serial_port + 5) & 0x20));
  return 1;
}

void kout(char *koutstring) {  // outputs a string (char array) to serial

  while (*koutstring != 0) {

    serial_io_wait();

      if (*koutstring == '\n') {
        kout_char('\n');
        kout_char('\r');
        koutstring++;

      } else {
        kout_char(*koutstring);
        koutstring++;
      }
  }
}