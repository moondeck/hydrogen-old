#include "memory.h"

uint32_t kstart_addr = (uint32_t)&kernel_start;
uint32_t ktextend = (uint32_t)&text_end;
uint32_t kdataend = (uint32_t)&data_end;
uint32_t kbssend = (uint32_t)&bss_end;
uint32_t kend_addr = (uint32_t)&kernel_end;

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

struct memory_reg_mark {
  uint32_t MAGIC;
  uint32_t nextptr;
};

struct gdt_entry gdt[3];
struct gdt_ptr gp;

struct multiboot_entry free_mem_stack[32];
struct multiboot_entry used_mem_stack[32];
uint32_t fms_ptr = 0;
uint32_t ums_ptr = 0;

uint32_t firstpf = (uint32_t)&kernel_end;
uint32_t *map = 0;

uint32_t *kmalloc_ptr = 0;

void _add_gdt_entry(int num,
                    uint32_t base,
                    uint32_t limit,
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
  gp.base = (uint32_t)&gdt;

  _add_gdt_entry(0, 0, 0, 0, 0);
  _add_gdt_entry(1, 0, 0xFFFFFFFF, 0x9A, 0xCF);
  _add_gdt_entry(2, 0, 0xFFFFFFFF, 0x92, 0xCF);

  gdt_flush();
}

void memory_init(multiboot_info_t* mbd) {
  multiboot_memory_map_t* mmap = (multiboot_memory_map_t*)mbd->mmap_addr;

  kprintf("text: 0x%x\ndata: 0x%x\nbss : 0x%x\n", ktextend, kdataend,
          kbssend);  // See mom? No itoa()!
  kprintf("Upper memory (KiB): %d\n",
          mbd->mem_upper);  // display the total amount of memory

  while (mmap < (multiboot_memory_map_t*)(mbd->mmap_addr + mbd->mmap_length) &&
  mmap->size == 20) {
    if (mmap->type == 1 && mmap->addr > 0x100000 - 1) {
      free_mem_stack[fms_ptr].address = (uint32_t) mmap->addr;
      free_mem_stack[fms_ptr].length = (uint32_t) mmap->len;
      free_mem_stack[fms_ptr].type = (uint32_t) mmap->type;

      if (free_mem_stack[fms_ptr].address == KERNEL_LOAD_POINT) {
        free_mem_stack[fms_ptr].address = PFA_STACK_POINTER + 0x400000;
        free_mem_stack[fms_ptr].length =
            (free_mem_stack[fms_ptr].length -
             (free_mem_stack[fms_ptr].address - KERNEL_LOAD_POINT));
      }

      kprintf("FREE addr: %x leng: %x type: %d\n",
              free_mem_stack[fms_ptr].address, free_mem_stack[fms_ptr].length,
              free_mem_stack[fms_ptr].type);
      fms_ptr++;

    } else {
      used_mem_stack[ums_ptr].address = (uint32_t) mmap->addr;
      used_mem_stack[ums_ptr].length = (uint32_t) mmap->len;
      used_mem_stack[ums_ptr].type = 2;

      kprintf("USED addr: %x leng: %x type %d\n",
              used_mem_stack[ums_ptr].address, used_mem_stack[ums_ptr].length,
              used_mem_stack[ums_ptr].type);

      ums_ptr++;
    }
    mmap = (multiboot_memory_map_t*)((uint32_t)mmap + mmap->size +
                                     sizeof(mmap->size));
  }

  fms_ptr = 0;
  ums_ptr = 0;
}

uint32_t pfa_init() {
  map = PFA_STACK_POINTER;
  fms_ptr = 0;
  struct multiboot_entry temp;

  while(!(free_mem_stack[fms_ptr].length == 0)) {
    temp = free_mem_stack[fms_ptr];
    *map = temp.address;

    while(temp.address < (free_mem_stack[fms_ptr].address + free_mem_stack[fms_ptr].length)) {

      temp.address += PAGE_SIZE;
      //kprintf("address: %x to address: %x\n",temp.address,map);

      map++;
      *map = temp.address;

    }
    kprintf("addrwrite: %x addr: %x\n",temp.address,map);
    fms_ptr++;
  }
  return map;
}

uint32_t pfa_pop() {
  if(map < PFA_STACK_POINTER) panic("PFA stack empty!");
  uint32_t return_val = *map;
  memset(map, 0x00, PAGE_SIZE);
  *map = 0;
  map--;
  kprintf("popping page frame with addr: %x\n",return_val);
  return return_val;
}

uint32_t pfa_push(uint32_t pushvalue) {
  if(map == PFA_STACK_POINTER + 0x400000) panic("PFA stack overflow!"); //max 32 bit pfa stack size
  map++;
  *map = pushvalue;
  return map;
}

pfptr_t alloc_pframe() {
  return pfa_pop();
}

pfptr_t dealloc_pframe(pfptr_t pframe_address) {
  return pfa_push(pframe_address);
}
