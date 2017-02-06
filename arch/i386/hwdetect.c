#include "hwdetect.h"

void cpuid(struct cpuid_string *cpuid_ptr, struct cpuid_brands *cpuid_brand_ptr) {
    identify_cpu((uint32_t) cpuid_ptr,(uint32_t) cpuid_brand_ptr);
    kprintf("cpuid: %s\n", (char*) cpuid_ptr);
    kprintf("brand: %s\n", (char*) cpuid_brand_ptr);

} 