#include "serial.h"


void init_serial() {
  outb(COMPORT + 1, 0x00);
  outb(COMPORT + 2, 0xC7);
  outb(COMPORT + 3, inb(COMPORT + 3) & ~0b10000000); //set DLAB

  outb(COMPORT + 0, 0x01);
  outb(COMPORT + 1, 0x00); //set the baud rate to 115200 (no division)

  outb(COMPORT + 3, inb(COMPORT + 3) | 0b10000000); //disable DLAB

  outb(COMPORT + 2, 0x01);
  outb(COMPORT + 3, 0x03);
  outb(COMPORT + 4, 0x01);
}

void kout_char(char koutchar) {  // outputs a character to serial
  outb(COM1, koutchar);
}

char serial_io_wait() {
  while (!(inb(COMPORT + 5) & 0x20));
  return 1;
}

void kout(char *koutstring) {  // outputs a string (char array) to serial

  while (*koutstring != 0) {

    serial_io_wait();

      if (*koutstring == '\n') {
        kout_char('\r');
        kout_char('\n');
        koutstring++;

      } else {
        kout_char(*koutstring);
        koutstring++;
      }
  }
}