#include <arch/i386/vmm/vmm.h>
#include <arch/i386/memory/memory.h>
#include <libc/kprintf.h>

struct pt {
    uint32_t page_tab_entry[1024];
};

struct pd {
    uint32_t page_dir_entry[1024];
};



#define PDIR 0x600000

uint32_t map_pv(uint32_t virt, uint32_t phys) {
    uint32_t pd_index = (virt >> 22);
    uint32_t pt_index = (virt >> 12);

    struct pd *page_dir = (struct pd*) PDIR;
    struct pt *page_tab = 0;


    if(page_dir->page_dir_entry[pd_index]) {    //is the entry there?
        kprintf("page tab is there\n");
        page_tab = (struct pt*) (page_dir->page_dir_entry[pd_index] & 0xFFFFF000);  //if yes, just map it
    } else {                                    //if its not, do:
        kprintf("page tab not there, allocating\n");
        page_dir->page_dir_entry[pd_index] = alloc_pframe();
        page_dir->page_dir_entry[pd_index] |= 3;
        invlpg(page_dir->page_dir_entry[pd_index] & 0xFFFFF000);
        page_tab = (struct pt*) (page_dir->page_dir_entry[pd_index] & 0xFFFFF000);
    }
    memset(page_dir->page_dir_entry[pd_index], 0x00 )
    page_tab->page_tab_entry[pt_index] = phys | 3;
    load_cr3((uint32_t) PDIR);
    return 0;
}

void init_paging(void) {
    kprintf("current dir:%x\n",(uint32_t) PDIR);
    load_cr3((uint32_t) PDIR);
}

inline void invlpg(uint32_t addr) {
   asm volatile("invlpg (%0)" ::"r" (addr) : "memory");
}