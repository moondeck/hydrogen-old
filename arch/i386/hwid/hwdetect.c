#include <arch/i386/hwid/hwdetect.h>

uint32_t cpuid(char *cpuid_ptr) {
    uint32_t return_val = identify_cpu((uint32_t) cpuid_ptr);
    kprintf("cpuid: %s\n", cpuid_ptr);
    return return_val;
}
