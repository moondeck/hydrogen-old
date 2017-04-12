#include <stdint.h>

void load_cr3(uint32_t pointer);
void init_paging(void);
uint32_t map_pv(uint32_t virt, uint32_t phys, uint8_t flags);

#define PFLAG_GLOBAL (1 << 7)
#define PFLAG_CACHED (1 << 3)
#define PFLAG_WRITET (1 << 2)
#define PFLAG_USRSUP (1 << 1)
#define PFLAG_READWR (1 << 0)