#include <stdint.h>

void load_cr3(uint32_t pointer);
void init_paging(void);
uint32_t map_pv(uint32_t virt, uint32_t phys);