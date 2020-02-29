#include <stdio.h>
#include <string.h>

#include "ram.h"
#include "kernel.h"
#include "interpreter.h"
#include "cpu.h"

//Instantiating the CPU
CPU cpu;

/**
 * Method is responsible in initializing the CPU
 */
void initialize_cpu(){
    cpu.IP = 0;
    cpu.IR[0] = '\0';
    cpu.quanta = 2;
}

/**
 * Function runs the CPU
 * @param quanta
 * @return Exit code
 */
int run_cpu(int quanta){
    int current_instr = current_pcb->PC;
    int end_instr = current_pcb->end;
    int retsts;
    cpu.IP++;
    cpu.quanta = quanta;

    while(cpu.quanta > 0){
        strcpy(cpu.IR, ram[current_instr]);
        flag_quit = 0;
        if(current_instr < end_instr + 1){
            retsts = interpret(cpu.IR);
            //makes sure it reaches the end of the file
            if(retsts != 0)
                return retsts;

            //makes sure it reaches the end of the file
            if(current_instr == end_instr)
                return 2;

            cpu.IP++;
            current_instr++;
            cpu.quanta--;
        }
    }

    current_pcb->PC = current_instr;
    return 0;
}

/**
 * Setter for the cpu
 * @param pc
 */
void set_cpu(int pc){
    cpu.IP = pc;
    cpu.IR[0] = '\0';
}
