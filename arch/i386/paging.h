#include "kernelio.h"

//clean me up

extern long pagedir;
extern void paging_en();
int set_page_dir_entry(int pagenr, char configbits, long address );
int set_page_tab_entry(int pagenr, char configbits, long address );
void setup_paging();
