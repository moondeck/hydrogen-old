#include <stdint.h>
#include <stdarg.h>

#ifdef __i386__
    #include "../../arch/i386/kernelio.h"
#endif

int kprintf(const char *format, ... );