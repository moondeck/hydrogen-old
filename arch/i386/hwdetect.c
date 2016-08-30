/*
 *  all hardware detection stuff goes here
 *  CPUID and stuff like that
 *
*/

int CPUID(int level) {
  asm ("cpuid
  : ")
}
