#include "../../kernel/libc/libc.h"
#include "../../kernel/libc/kprintf.h"

#ifdef __i386__
    #include "multiboot.h"
#endif

#include <stdint.h>

typedef unsigned int u32int;
typedef int s32int;
typedef unsigned short u16int;
typedef short s16int;
typedef unsigned char u8int;
typedef char s8int;

#define KBD_DAT 0x60
#define KBD_STACMD 0x64

void kout(char *kouttext);
void kout_char(char koutchar);
void kout_color(char kout_color);
void clearscreen();
void initkbd();
void kin(char *kintext);
void outb(u16int port, u8int value);
void outw(u16int port, u16int value);
void panic(char* err);
void bootmsg(multiboot_info_t *mbd);
unsigned char inb(unsigned short port);
unsigned short inw(unsigned short port);
unsigned int inl(unsigned short port);
void haltcpu(void);
void brk(void);
void kout_mem(char *membase, char *sepchar, char *memlenght, char type);

