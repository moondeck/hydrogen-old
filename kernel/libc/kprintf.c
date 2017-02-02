#include "kprintf.h"

int kprintf(const char *format, ... ) {
    va_list parameters;
    va_start(parameters, format);

    char *text_str;
    char text_conversion[32];
    int number;

    while(*format != 0) {

        if(*format == '%') {
            format++;

            switch (*format) {
                case 's':   //string
                    text_str = va_arg(parameters, char *);
                    kout(text_str);
                    break;

                case 'd':   //integer
                    number = va_arg(parameters, uint32_t);
                    itoa(number, text_conversion, 10);
                    kout(text_conversion);
                    break;

                case 'x':   //hex integer
                    number = va_arg(parameters, uint32_t);
                    itoa(number, text_conversion, 16);
                    kout(text_conversion);
                    break;

                case 'l':   //64 bit integer
                    number = va_arg(parameters, uint64_t);
                    ltoa(number, text_conversion, 10);
                    kout(text_conversion);
                    break;

                 case 'X':   //hex 64 int integer
                    number = va_arg(parameters, uint64_t);
                    ltoa(number, text_conversion, 16);
                    kout(text_conversion);
                    break;
                         
            }

            format++;

        } else {

            if(*format == '\n') {
                kout_char('\r');
                kout_char('\n');
                format++;

            } else {
                kout_char(*format);
                format++;
                
            }
        }
    }
    return 0;
}