#include "kprintf.h"

int kprintf(const char *format, ... ) {
    va_list parameters;
    va_start(parameters, format);

    char *text;
    int number;

    while(*format != 0) {
        if(*format == '%') {
            *format++;
            switch (*format) {
                case 's':   //string
                    text = va_arg(parameters, char *);
                    kout(text);
                    break;

                case 'i':   //integer
                    number = va_arg(parameters, int);
                    itoa(number, text, 10);
                    kout(text);
                    break;

                case 'l':   //long
                    number = va_arg(parameters, long);
                    ltoa(number, text, 10);
                    kout(text);
                    break;

                case 'h':   //hex integer
                    number = va_arg(parameters, int);
                    ltoa(number, text, 16);
                    kout(text);
                    break;
                    
                case 'b':   //binary integer
                    number = va_arg(parameters, int);
                    ltoa(number, text, 16);
                    kout(text);
                    break;
            }

            

        } else{
            kout_char(*format);
        }
        *format++;
    }

}