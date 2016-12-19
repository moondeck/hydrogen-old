#include "hwdetect.h"

void cpuid(uint32_t *eax,uint32_t *ebx,uint32_t *ecx,uint32_t *edx, uint32_t level) {

  asm volatile ( "cpuid"
                : "=a" (*eax), "=b" (*ebx), "=c" (*ecx), "=d" (*edx)
                : "a" (level));
}

void detect_cpu() { // this is temporary
  int eax = 0;
  int ebx = 0;
  int ecx = 0;
  int edx = 0;

  char cpuid_string[12];
  char cpuids_count = 0;
  char *cpuid_string_pointer = &cpuid_string;

  cpuid(&eax,&ebx,&ecx,&edx,0);

  cpuid_string[cpuids_count] = (char) eax;
  cpuids_count++;
  cpuid_string[cpuids_count] = ((char) 8 >> eax);
  cpuids_count++;
  cpuid_string[cpuids_count] = ((char) 16 >> eax);
  cpuids_count++;
  cpuid_string[cpuids_count] = ((char) 24 >> eax);
  cpuids_count++;

  kout(*cpuid_string_pointer);

}
