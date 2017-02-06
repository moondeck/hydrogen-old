#include "vmm.h"

struct pt {
    uint32_t page_tab_entry[1024];
};

uint32_t *current_dir = 0;

uint32_t tld_ptr = 0;

uintptr_t alloc_pt() {
    struct pt *page_table_ptr = alloc_pframe();
    kprintf("page table at %x\n", page_table_ptr);
    return page_table_ptr;
}

uintptr_t init_paging(uint8_t level) {
    tld_ptr = alloc_pt();
    kprintf("page directory allocated at %x\n", current_dir);
    for(tld_ptr = 0;tld_ptr != 1023;tld_ptr++) {

        *current_dir = alloc_pt() | 1;

    }
    
}