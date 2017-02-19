#include <arch/i386/vmm/vmm.h>
#include <arch/i386/memory/memory.h>
#include <libc/kprintf.h>

struct pt {
    uint32_t page_tab_entry[1024];
};

struct pd {
    uint32_t page_dir_entry[1024];
};


uint32_t *current_dir = (uint32_t*) 0x600000;



uintptr_t get_pdir(void) {
    return (uint32_t) current_dir;
}

uint32_t map_pv(uintptr_t virt, uintptr_t phys) {
    uint32_t pd_index = (virt >> 22);
    uint32_t pt_index = (virt >> 12);

    struct pd *page_dir = (struct pd*) get_pdir();
    struct pt *page_tab = 0;

    
    if(page_dir->page_dir_entry[pd_index]) {
        page_tab = (struct pt*) (page_dir->page_dir_entry[pd_index] & 0xFFFFF000);
    } else {
        page_dir->page_dir_entry[pd_index] = alloc_pframe();
        page_dir->page_dir_entry[pd_index] |= 3;
        page_tab = (struct pt*) (page_dir->page_dir_entry[pd_index] & 0xFFFFF000);
    }
    page_tab->page_tab_entry[pt_index] = phys | 3;
    return 0;
}

void init_paging(void) {
    uint32_t addr = 0;
    //panic("its time to stop");
    for(addr = 0;addr < 1024; addr++)
        dealloc_pframe(0x600000 + (addr * 0x1000)); //a hack to get some space for the first page dirs. It will "free" some guaranteed-free space inside the 16M border
                                                    //the PFA ends at 0x520000
    kprintf("current dir:%x\n",(uint32_t) current_dir);

    for(addr = 0;addr < 0xFFF000; addr += 4096) {
        //kprintf("addr = %x\n",addr);
        map_pv(addr,addr);
    }
    kprintf("addr = %x\n",addr);

    load_cr3((uint32_t) current_dir);

}