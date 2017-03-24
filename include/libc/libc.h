#include <stdint.h>
uint32_t memset(uint32_t *dest, uint8_t val, uint32_t count) ;
uint32_t memcpy(uint32_t *src,uint32_t *dest,uint32_t length);
char *itoa(int32_t value, char *str, uint32_t base);
char *ltoa(int64_t value, char *str, uint32_t base);
