#include "pfa.h"

unsigned int pfa_stack[PFA_STACK_LENGTH];
unsigned int stack_ptr = 0;
unsigned int firstpf = &kernel_end;

void pfa_stack_push(unsigned int value) {
  pfa_stack[stack_ptr] = value;
  stack_ptr++;

}

unsigned int pfa_stack_pop() {
  unsigned int pop_value = pfa_stack[stack_ptr];

  pfa_stack[stack_ptr] = 0;
  stack_ptr--;
  return pop_value;

}

void pfa_init() {

  while (firstpf % 4096 != 0) {
    firstpf++;
  }

  char test[10];
  pfa_stack_push(firstpf);



}
