#include "memory.h"
#include "kernelio.h"
#include "../../kernel/libc/libc.h"

struct gdt_entry {
  unsigned short limit;
  unsigned short base_low;
  unsigned char base_middle;
  unsigned char access;
  unsigned char granularity;
  unsigned char base_high;
} __attribute__((packed));

struct gdt_ptr {
  unsigned short limit;
  unsigned int base;
} __attribute__((packed));

struct gdt_entry gdt[16];
struct gdt_ptr gp;

extern void gdt_flush();

void _add_gdt_entry(int num, unsigned long base, unsigned long limit,
                  unsigned char access, unsigned char gran) {
  gdt[num].base_low = base;
  gdt[num].base_middle = (base >> 16);
  gdt[num].base_high = (base >> 24);
  gdt[num].limit = limit;
  gdt[num].granularity = gran;
  gdt[num].access = access;
}

void gdt_install() {

  gp.limit = (sizeof(struct gdt_entry) * 3) - 1;
  gp.base = (unsigned int)  &gdt;
  _add_gdt_entry(0, 0, 0, 0, 0);
  _add_gdt_entry(1, 0, 0xFFFFFFFF, 0x9A, 0xCF);
  _add_gdt_entry(2, 0, 0xFFFFFFFF, 0x92, 0xCF);
  gdt_flush();
}

void memory_detect(multiboot_info_t *mbd) {
  char foobar[15];
  multiboot_memory_map_t* mmap = (multiboot_memory_map_t*) mbd->mmap_addr;
  //itoa(mbd->mmap_addr,foobar,16);
  //kout("multiboot structures at:\n");
  while(mmap < (multiboot_memory_map_t*) mbd->mmap_addr + mbd->mmap_length && mmap->size != 0) {
    kout("type: ");
    if(mmap->type == 1){
      kout("free");
    } else{
      kout("used");
    }
    kout("  address: ");
    ltoa((unsigned) mmap->addr,foobar,16);
    kout(foobar);
    kout("  length: ");
    ltoa((unsigned) mmap->len,foobar,16);
    kout(foobar);
    kout("  ending address:");
    ltoa((unsigned) (mmap->len + mmap->addr),foobar,16);
    kout(foobar);
    kout("\n");
		mmap = (multiboot_memory_map_t*) ( (unsigned int)mmap + mmap->size + sizeof(unsigned int) );
	}
  itoa((unsigned) mmap->size,foobar,10);
  kout(foobar);
}
