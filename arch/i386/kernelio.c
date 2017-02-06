#include "kernelio.h"

/*
 * kernel I/O library
 */

 const char *version = "230117";

void bootmsg(multiboot_info_t* mbd) {  // boot message and some info

  if (mbd->cmdline != 0) {
    kprintf("\nbooting command line: %s\n", (char*)mbd->cmdline);
  }

  kprintf("welcome to hydrogen\n\n");
  kprintf("(C) Copyright 2015-2017 Moondeck\n");
  kprintf("Licensed under the Apache License, Version 2.0\n\n");
  kprintf("version %s pre-alpha\n", version);
  kprintf("loaded by: %s\n", (char*)mbd->boot_loader_name);
}

void brk(void) {
  asm("hlt");  // halts the cpu until an interrupt is received
}

void haltcpu(void) {
  asm("cli");  // halts the cpu until reset, as interrupts are disabled before
               // the hlt instruction
  asm("hlt");
}

void panic(char* err) {  // critical error, stops the system, until its restarted

  unsigned int eax, ebx, ecx, edx
              ,esi, edi;

  kprintf("\n|==== kernel panic ====|\n");
  kprintf(" cause: %s\n", err);
  asm("cli");  // disable interrupts so we dont get INTERRUPTED! (duh)

  asm("nop" : "=a"(eax));
  asm("nop" : "=b"(ebx));
  asm("nop" : "=c"(ecx));
  asm("nop" : "=d"(edx));
  asm("nop" : "=S"(esi));
  asm("nop" : "=D"(edi));
  kprintf(" eax:0x%x\n ebx:0x%x\n ecx:0x%x\n edx:0x%x\n esi:0x%x\n edi:0x%x\n", eax, ebx, ecx, edx, esi, edi);
  kprintf("\n|======================|");
  asm("hlt");
}
