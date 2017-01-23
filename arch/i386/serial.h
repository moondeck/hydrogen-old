#include "io.h"

#define COM1 0x3F8
#define serial_port COM1

void com_1_interrupt(void);
void init_serial();
char serial_io_wait();

void kout(char *koutstring);
void kout_char(char koutchar);