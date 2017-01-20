#include "memory.h"

int kstart_addr = (int) &kernel_start;
int ktextend    = (int) &text_end;
int kdataend    = (int) &data_end;
int kbssend     = (int) &bss_end;
int kend_addr   = (int) &kernel_end;

struct gdt_entry {
  uint16_t limit;
  uint16_t base_low;
  uint8_t base_middle;
  uint8_t access;
  uint8_t granularity;
  uint8_t base_high;
};

struct gdt_ptr {
  uint16_t pad;
  uint16_t limit;
  uint32_t base;
};

struct multiboot_entry {
  unsigned long long address;
  unsigned long long length;
  uint32_t type;
} __attribute__((packed));


struct gdt_entry gdt[3];
struct gdt_ptr gp;

struct multiboot_entry multiboot_entry_stack[32];
unsigned int mbe_ptr = 0;

void _add_gdt_entry(int num, unsigned long base, unsigned long limit,
                    uint32_t access, uint32_t gran) {
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

  itoa(mbd->mem_upper, kerninfo, 10);    // grab the value, convert it to text.

  kout("\nUpper memory (KiB): ");           // display the text part
  kout(kerninfo);                        // display the converted value from the buffer
  kout("\n");                               // go to a new line

  while (mmap < (multiboot_memory_map_t*)(mbd->mmap_addr + mbd->mmap_length) &&
         mmap->size == 20) {
    if (mmap->type == 1) {

      multiboot_entry_stack[mbe_ptr].address = mmap->addr;
      multiboot_entry_stack[mbe_ptr].length = mmap->len;
      multiboot_entry_stack[mbe_ptr].type = mmap->type;

      if (multiboot_entry_stack[mbe_ptr].address == 0x1000000) {
        multiboot_entry_stack[mbe_ptr].address = firstpf;

        if (!(multiboot_entry_stack[mbe_ptr].address + multiboot_entry_stack[mbe_ptr].length + 1 % 4096)) {
          multiboot_entry_stack[mbe_ptr].length--;
        }
      }
      mbe_ptr++;


    } else {
    }
    mmap = (multiboot_memory_map_t*)((unsigned int)mmap + mmap->size +
                                     sizeof(mmap->size));
  }
}
