#include "kernelio.h"
#include "../../kernel/libc/libc.h"

typedef unsigned int u32int;
typedef int s32int;
typedef unsigned short u16int;
typedef short s16int;
typedef unsigned char u8int;
typedef char s8int;

#define KBD_DAT 0x60
#define KBD_STACMD 0x64

unsigned int charcount = 0;

#define COM1 0x3F8

/*
 * kernel I/O library
 */

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

 int com_rdy(int comport) {
   return inb(comport + 5) & 0x20;
 }

void kout_char(char koutchar) {
  while (com_rdy(COM1) == 0);
  outb(COM1,koutchar);
}

void kout(char *koutstring) {
  while (*koutstring != 0) {
    kout_char(*koutstring);
    koutstring++;
  }
}

void initkbd() {  // initialises the keyboard
  // TODO
}

void bootmsg() {
  kout("welcome to hydrogen\n\n");
  kout("(C) Copyright 2015-2016 Moondeck\n");
  kout("Licensed under the Apache License, Version 2.0\n\n");
  kout("version 0.0.5 pre-alpha\n");
}

void brk(void) {
  asm("hlt");  // halts the cpu until an interrupt is received
}

void haltcpu(void) {
  asm("cli");  // halts the cpu until reset, as interrupts are disabled before
               // the hlt instruction
  asm("hlt");
}

void halt_system_err(char *err) {
  kout("\n\n\n[!!!     CRITICAL ERROR    !!!] \n\n");
  kout("cause: ");
  kout(err);
  asm("cli");
  unsigned int eax,ebx,ecx,edx;
  char eax_str[16],ebx_str[16],ecx_str[16],edx_str[16];
  asm("nop"
  :"=b"(eax));
  kout("\nEAX: 0x");
  kout(itoa(eax,eax_str,16));
  kout("\n");
  asm("nop"
  :"=b"(ebx));
  kout("EBX: 0x");
  kout(itoa(ebx,ebx_str,16));
  kout_char('\n');
  asm("nop"
  :"=b"(ecx));
  kout("ECX: 0x");
  kout(itoa(ecx,ecx_str,16));
  kout_char('\n');
  asm("nop"
  :"=b"(edx));
  kout("EDX: 0x");
  kout(itoa(edx,edx_str,16));
  kout("\nsystem halted\n");
  asm("hlt");  // halts the CPU
}
