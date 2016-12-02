#include "memory.h"

int kstart_addr = (int) &kernel_start;
int ktextend    = (int) &text_end;
int kdataend    = (int) &data_end;
int kbssend     = (int) &bss_end;
int kend_addr   = (int) &kernel_end;

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

struct multiboot_entry {
  unsigned long long address;
  unsigned long long length;
  unsigned char type;
} __attribute__((packed));


struct gdt_entry gdt[3];
struct gdt_ptr gp;

struct multiboot_entry multiboot_entry_stack[32];
unsigned int mbe_ptr = 0;

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
  gp.base = (unsigned int)&gdt;

  _add_gdt_entry(0, 0, 0, 0, 0);
  _add_gdt_entry(1, 0, 0xFFFFFFFF, 0x9A, 0xCF);
  _add_gdt_entry(2, 0, 0xFFFFFFFF, 0x92, 0xCF);

  gdt_flush();
}


void memory_detect(multiboot_info_t* mbd) {
  char text_buffer[20];



  multiboot_memory_map_t* mmap = (multiboot_memory_map_t*) mbd->mmap_addr;
  char kerninfo[10];

  kout("text: 0x");
  itoa(ktextend,kerninfo,16);
  kout(kerninfo);
  kout("\n");
  kout("data: 0x");
  itoa(kdataend,kerninfo,16);
  kout(kerninfo);
  kout("\n");
  kout("bss:  0x");
  itoa(kbssend,kerninfo,16);
  kout(kerninfo);
  kout("\n\n");

  itoa(mbd->mem_upper, text_buffer, 10);    // grab the value, convert it to text.

  kout("\nUpper memory (KiB): ");           // display the text part
  kout(text_buffer);                        // display the converted value from the buffer
  kout("\n");                               // go to a new line

  while (mmap < (multiboot_memory_map_t*)(mbd->mmap_addr + mbd->mmap_length) &&
         mmap->size == 20) {

    kout("address: ");
    lltoa(mmap->addr, text_buffer, 16);
    kout(text_buffer);

    kout("  length: ");
    lltoa(mmap->len, text_buffer, 16);
    kout(text_buffer);

    kout("  ending address:");
    lltoa(mmap->len + mmap->addr, text_buffer, 16);
    kout(text_buffer);

    kout("  type: ");
    if (mmap->type == 1) {
      kout("free");

      multiboot_entry_stack[mbe_ptr].address = mmap->addr;
      multiboot_entry_stack[mbe_ptr].length = mmap->len;
      multiboot_entry_stack[mbe_ptr].type = mmap->type;

      if (multiboot_entry_stack[mbe_ptr].address == 0x1000000) {
        multiboot_entry_stack[mbe_ptr].address = firstpf;

        if (!(multiboot_entry_stack[mbe_ptr].address + multiboot_entry_stack[mbe_ptr].length + 1 % 4096)) {
          multiboot_entry_stack[mbe_ptr].length--;
        }
      }
      kout("\n");
      itoa(multiboot_entry_stack[mbe_ptr].length,text_buffer,16);
      kout(text_buffer);

      mbe_ptr++;


    } else {
      kout("used");
    }

    kout("\n");
    mmap = (multiboot_memory_map_t*)((unsigned int)mmap + mmap->size +
                                     sizeof(mmap->size));
  }
}
