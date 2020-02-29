#include <stdlib.h>
#include <stdio.h>

#include "shell.h"
#include "pcb.h"
#include "ram.h"
#include "cpu.h"
#include "kernel.h"

pcb *current_pcb;

/**
 * Main function
 * @param argc
 * @param argv
 * @return
 */
int main(int argc, const char *argv[]){
    //initialize the ram
    initialize_ram();
    //initialize the cpu
    initialize_cpu();

    int response = shell_ui();
    return response;
}

/**
 * The scheduler for the kernel
 */
void scheduler(){
    initialize_cpu();

    //If the head exists
    while(getHead()){
        print_pcb();  //testing purposes
        current_pcb = getReady();
        //if current pcb is not null
        if(current_pcb){
            set_cpu(current_pcb->PC);

            if(run_cpu(2) == 2)
                terminate(current_pcb);

            else
                addReady(current_pcb);
        }
    }
}

/**
 * This function is responsible of deleting the pcb from the ram
 * as well as freeing the memory
 * @param p    the pcb that you want to stop
 */
void terminate(pcb *p){
    delete_ram(p->start, p->end);
    free(p);
}

/**
 * this function is responsible in initializing the kernel by making
 * pcbs, putting them in the ready queue and putting files into RAM
 * @param file      the file you want to put into memory
 * @return          0 for success
 *                  1 for error
 */
int initialize_kernel(FILE *file){
    pcb *p;
    if(insert_ram(file) >= 0){
        p = make_pcb(ram_start, ram_end);

        //if pcb is not null, then add it to the ready queue
        if(p){
            addReady(p);
            return 0;
        }
    }
    return 1;
}