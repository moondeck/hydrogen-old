#include <stdint.h>
#include <libc/kprintf.h>

enum {
  CPUID_FPU     = (1 << 0),
  CPUID_VME     = (1 << 1),
  CPUID_DE      = (1 << 2),
  CPUID_PSE     = (1 << 3),
  CPUID_TSC     = (1 << 4),
  CPUID_MSR     = (1 << 5),
  CPUID_PAE     = (1 << 6),
  CPUID_MCE     = (1 << 7),
  CPUID_CX8     = (1 << 8),
  CPUID_APIC    = (1 << 9),
  CPUID_RES1    = (1 << 10),
  CPUID_SEP     = (1 << 11),
  CPUID_MTRR    = (1 << 12),
  CPUID_PGE     = (1 << 13),
  CPUID_MCA     = (1 << 14),
  CPUID_CMOV    = (1 << 15),
  CPUID_PAT     = (1 << 16),
  CPUID_PSE36   = (1 << 17),
  CPUID_PSN     = (1 << 18),
  CPUID_CLFSH   = (1 << 19),
  CPUID_RES2    = (1 << 20),
  CPUID_DS      = (1 << 21),
  CPUID_ACPI    = (1 << 22),
  CPUID_MMX     = (1 << 23),
  CPUID_FXSR    = (1 << 24),
  CPUID_SSE     = (1 << 25),
  CPUID_SSE2    = (1 << 26),
  CPUID_SS      = (1 << 27),
  CPUID_HTT     = (1 << 28),
  CPUID_TM      = (1 << 29),
  CPUID_IA64    = (1 << 30),
  CPUID_PBE     = (1 << 31)
};


uint32_t cpuid(char *cpuid_ptr);
uint32_t identify_cpu(uint32_t pointer);