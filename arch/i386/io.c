#include "io.h"

void outb(unsigned short port, unsigned char value) {  // 8bit port output
  asm("outb %1, %0" : : "dN"(port), "a"(value));
}

void outw(unsigned short port, unsigned short value) {  // 16bit port output
  asm("outw %1, %0" : : "dN"(port), "a"(value));
}

void outl(unsigned short port, unsigned int value) {  // 32bit port output
  asm("outl %1, %0" : : "dN"(port), "a"(value));
}

unsigned char inb(unsigned short port) {  // 8bit port input
  unsigned char ret;
  asm("inb %1, %0" : "=a"(ret) : "Nd"(port));
  return ret;
}

unsigned short inw(unsigned short port) {  // 16bit port input
  unsigned short ret;
  asm("inw %1, %0" : "=a"(ret) : "Nd"(port));
  return ret;
}

unsigned int inl(unsigned short port) {  // 32bit port input
  unsigned int ret;
  asm("inl %1, %0" : "=a"(ret) : "Nd"(port));
  return ret;
}