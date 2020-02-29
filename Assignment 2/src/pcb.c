#include <stdio.h>
#include <stdlib.h>
#include "pcb.h"

//initializing linked list
pcb *head = NULL;
pcb *tail = NULL;

/**
 * Initializing the pcb
 * @param p
 * @param start
 * @param end
 */
void initializing_pcb(pcb *p, int start, int end){
    p->start = start;
    p->end = end;
    p->PC = start;
    p->next = NULL;
}

/**
 * This function is to make a pcb
 * @param start
 * @param end
 * @return pcb
 */
pcb *make_pcb(int start, int end){
    pcb *p;

    p = (pcb*)malloc(sizeof(pcb));

    if(!p)
        return NULL;

    initializing_pcb(p, start, end);
    return p;
}
/**
 * Get the head of the pcb list
 * @return  the head of the pcb list
 */
pcb *getHead(){
    return head;
}

/**
 * Get the pcb that is next to be taken out of the ready queue
 * @return  the head of the ready queue (pcb)
 */
pcb *getReady(){
    pcb *retsts;

    if(!head)
        return NULL;

    retsts = head;
    head = head->next;
    retsts->next = NULL;

    if(!head)
        tail = NULL;
    return retsts;
}

/**
 * This function is used to put the pcb into a ready list
 * @param p     the pcb that will be in the ready queue
 */
void addReady(pcb *p){
    if(!head){
        head = p;
        tail = p;
    }

    else{
        tail->next = p;
        tail = p;
    }
}

/**
 * Printing the pcb address: Used for debugging purposes
 */
void print_pcb(){
    pcb *target = head;
    while(target != NULL){
        printf("address: %d\n", target->start);
        target = target->next;
    }
}