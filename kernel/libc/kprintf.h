#include <stdint.h>
#include <stdarg.h>

#ifdef __i386__
    #include "../../arch/i386/serial.h"
#endif

#include "libc.h"

int kprintf(const char *format, ... );