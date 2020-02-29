#ifndef ECSE427_ASSIGNMENT2_PCB_H
#define ECSE427_ASSIGNMENT2_PCB_H
typedef struct PCB{
    int PC;
    int start;
    int end;
    struct PCB *next;
}pcb;

pcb *getHead();
pcb *getReady();
pcb *make_pcb(int start, int end);
void addReady(pcb *p);
void print_pcb();
#endif //ECSE427_ASSIGNMENT2_PCB_H
