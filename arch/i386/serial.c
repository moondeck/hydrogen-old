#include "kernelio.h"
#include "serial.h"

#define COM1 0x3F8

void init_serial(int serial_port) {
  outb(serial_port + 1,0x00);
  outb(serial_port + 2,0xC7);
  outb(serial_port + 4,0x01);
}

void com_1_interrupt(void) {
  kout_char(inb(COM1));
}
