#include <stdint.h>
void memset(unsigned char *dest, unsigned char val, uint32_t count);
void memcpy(uint32_t *src,uint32_t *dest,uint32_t length);
char *itoa(int32_t value, char *str, uint32_t base);
char *ltoa(int64_t value, char *str, uint32_t base);
