#ifndef ECSE427_ASSIGNMENT2_KERNEL_H
#define ECSE427_ASSIGNMENT2_KERNEL_H
#include <stdio.h>
#include "pcb.h"

void scheduler();
int initialize_kernel(FILE *file);
void terminate(pcb *p);

extern pcb *current_pcb;
#endif //ECSE427_ASSIGNMENT2_KERNEL_H
