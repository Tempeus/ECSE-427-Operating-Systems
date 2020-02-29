#ifndef ECSE427_ASSIGNMENT2_CPU_H
#define ECSE427_ASSIGNMENT2_CPU_H

#define instruction_size 1000

typedef struct {
    int IP;
    char IR[instruction_size];
    int quanta;
} CPU;

void initialize_cpu();
void set_cpu(int pc);
int run_cpu(int quanta);
#endif //ECSE427_ASSIGNMENT2_CPU_H
