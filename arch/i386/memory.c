#include "memory.h"

int kstart_addr = (int)&kernel_start;
int ktextend = (int)&text_end;
int kdataend = (int)&data_end;
int kbssend = (int)&bss_end;
int kend_addr = (int)&kernel_end;

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
  uint32_t address;
  uint32_t length;
  uint32_t type;
};

struct gdt_entry gdt[3];
struct gdt_ptr gp;

struct multiboot_entry free_mem_stack[32];
struct multiboot_entry used_mem_stack[32];
uint32_t fms_ptr = 0;
uint32_t ums_ptr = 0;

uint32_t firstpf = (uint32_t)&kernel_end;

void _add_gdt_entry(int num,
                    unsigned long base,
                    unsigned long limit,
                    uint32_t access,
                    uint32_t gran) {
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

void memory_init(multiboot_info_t* mbd) {
  while (firstpf % 4096)
    firstpf++;

  multiboot_memory_map_t* mmap = (multiboot_memory_map_t*)mbd->mmap_addr;

  kprintf("text: 0x%x\ndata: 0x%x\nbss : 0x%x\n", ktextend, kdataend,
          kbssend);  // See mom? No itoa()!
  kprintf("Upper memory (KiB): %d\n",
          mbd->mem_upper);  // display the total amount of memory

  while (mmap < (multiboot_memory_map_t*)(mbd->mmap_addr + mbd->mmap_length) &&
         mmap->size == 20) {
    if (mmap->type == 1) {
      free_mem_stack[fms_ptr].address = mmap->addr;

      free_mem_stack[fms_ptr].length = mmap->len;

      free_mem_stack[fms_ptr].type = mmap->type;

      if (free_mem_stack[fms_ptr].address == KERNEL_LOAD_POINT) {
        free_mem_stack[fms_ptr].address = firstpf;
        free_mem_stack[fms_ptr].length =
            (free_mem_stack[fms_ptr].length -
             (free_mem_stack[fms_ptr].address - KERNEL_LOAD_POINT));
      }
      fms_ptr++;

    } else {
      used_mem_stack[ums_ptr].address = mmap->addr;
      used_mem_stack[ums_ptr].length = mmap->len;
      used_mem_stack[ums_ptr].type = mmap->type;

      ums_ptr++;
    }
    mmap = (multiboot_memory_map_t*)((unsigned int)mmap + mmap->size +
                                     sizeof(mmap->size));
  }
}
