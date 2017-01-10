#include "kprintf.h"

int kprintf(const char *format, ... ) {
    va_list parameters;
    va_start(parameters, format);

    while(*format != 0) {
        if(*format == '%') {
            *format++;
            

        } else{
            kout_char(*format);
        }
        *format++;
    }

}