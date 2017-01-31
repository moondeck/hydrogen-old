#include <stdint.h>

void *mset(unsigned char *dest, unsigned char val, uint32_t count);
void memcpy(uint32_t *src,uint32_t *dest,uint32_t length);
char *itoa(uint32_t value, char *str, uint32_t base);
char *ltoa(long value, char *str, uint32_t base);
char *lltoa(long long value, char *str, uint32_t base);
