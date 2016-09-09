#include "memory.h"
#include "kernelio.h"
//#include "multiboot.h"

extern void paging_en();

unsigned long page_dir_base;

unsigned long pagedirs[1023];

void setup_paging(){
	page_dir_base = (unsigned long) &pagedirs[0];
	paging_en();
}
