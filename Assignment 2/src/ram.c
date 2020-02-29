#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ram.h"

char* ram[MEMORY_SPACE];
int ram_index = 0;
int ram_start;
int ram_end;

/**
 * This method is used to initalize the RAM by setting each cell to null
 */
void initialize_ram(){
    for(int i =0; i < MEMORY_SPACE; i++)
        ram[i] = NULL;
}

/**
 * This method is used to delete a specified range of cells in RAM
 * @param start_index   The starting index of where RAM will be deleted
 * @param end_index     The ending index of where RAM will be deleted
 */
void delete_ram(int start_index, int end_index){
    for(start_index = ram_start; start_index <= end_index; start_index++)
        ram[start_index] = NULL;
}

/**
 * This method will insert the script into the ram
 * @param file      the script file
 * @return          Exit code
 */
int insert_ram(FILE *file){
    char* line = NULL;

    size_t lc = 0;
    ram_start = ram_index;
    while (!feof(file)){
        getline(&line, &lc, file);

        //make sure the index is smaller than the maximum memory space
        if(ram_index < MEMORY_SPACE)
            ram[ram_index] = strdup(line);

        else
            return -1;

        //increment the ram index
        ram_index ++;
    }

    ram_end = ram_index - 1;
    return ram_end;
}