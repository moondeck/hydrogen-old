#include "vmm.h"

struct pt {
    uint32_t page_tab_entry[1024];
};

struct pd {
    
    uint32_t page_dir_entry[1024];
};


uint32_t *current_dir = 0x2000;

uintptr_t alloc_pd(void) {
    current_dir = alloc_pframe();
    kprintf("new page dir at %x\n", current_dir);
    return current_dir;
}

uintptr_t get_pdir(void) {
    return current_dir;
}

uint32_t map_pv(uintptr_t virt, uintptr_t phys) {
    uint32_t pd_index = (virt >> 22);
    uint32_t pt_index = (virt >> 12);

    struct pd *page_dir = get_pdir();
    struct pt *page_tab = 0;

    if(page_dir->page_dir_entry[pd_index]) {
        page_tab = page_dir->page_dir_entry[pd_index] & 0xFFFFF000;

    } else {
        page_dir->page_dir_entry[pd_index] = alloc_pframe() | 3;
        page_tab = page_dir->page_dir_entry[pd_index] & 0xFFFFF000;
    }
    page_tab->page_tab_entry[pt_index] = phys | 3;
    return 0;
}

void init_paging(void) {
    alloc_pd();
    map_pv(0xFFF0000,0x1100FFF);

    load_cr3(current_dir);

}