#include <arch/i386/vmm/vmm.h>
#include <arch/i386/memory/memory.h>
#include <libc/kprintf.h>

#define PDIR_PHYS 0x600000
#define PDIR_VIRT 0xFFFFF000

#define PSTRUCTURE_VIRT 0xFFC00000
static uint32_t *page_dir = (uint32_t *) PDIR_PHYS;
static uint32_t * const page_tab = (uint32_t*)0xFFC00000;

uint32_t get_virt_mapoffset(uint32_t PDIR_index) {
    return PSTRUCTURE_VIRT + (PDIR_index * 0x1000);
}

uint32_t map_pv(uint32_t virt, uint32_t phys) {
    uint32_t pd_index = (virt >> 22);
    uint32_t pt_index = (virt >> 12 );
    


    if(page_dir[pd_index]) {    //is the entry there?
        kprintf("page tab is there\n");
        *page_tab = get_virt_mapoffset(pd_index);  //if yes, just map it
    } else {                                    //if its not, do:
        kprintf("page tab not there, allocating\n");
        page_dir[pd_index] = alloc_pframe();
        page_dir[pd_index] |= 3;
        *page_tab = get_virt_mapoffset(pd_index);
        memset((uint8_t *) get_virt_mapoffset(pd_index), 0, PAGE_SIZE);
    }
    kprintf("page tab address: %x\n", get_virt_mapoffset(pd_index));
    kprintf("mapping physical address %x to virtual %x , thats gonna be offset %x\n", phys, virt, pt_index);

    page_tab[pt_index] = (phys & 0xFFFFF000) | 3;

    load_cr3((uint32_t) PDIR_PHYS);
    return 0;
}

void init_paging(void) {
    kprintf("current dir physical:%x virtual:%x\n", (uint32_t) PDIR_PHYS, (uint32_t) PDIR_VIRT);
    page_dir[1023] = PDIR_PHYS | 3;
    load_cr3((uint32_t) PDIR_PHYS);
    page_dir = (uint32_t *) PDIR_VIRT;
}

inline void invlpg(uint32_t addr) {
   asm volatile("invlpg (%0)" ::"r" (addr) : "memory");
}