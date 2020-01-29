#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "constants.h"
#include "shell.h"

//Creating the shell memory
static shell_memory shellMemory[MEMORY_SIZE] = {0};
static int memory_size = 0;

int set(char *var, char *value){
    //Get the size of the shellMemory that isn't NULL
//    while(shellMemory[memory_size].value && shellMemory[memory_size].var){
//        memory_size ++;
//    }

    if(memory_size >= MEMORY_SIZE) {
        return ERR_MAX_MEM;
    }

    for(int i = 0; i < (memory_size); i++){
        if(strcmp(shellMemory[i].var, var) == 0){
            shellMemory[i].value = value;
            return SUCCESS;
        }
    }

    if(memory_size < MEMORY_SIZE){
        shell_memory new_data = {new_data.var = var, new_data.value = value};
        shellMemory[memory_size] = new_data;
        memory_size++;
        return SUCCESS;
    }

    else {
        return ERR_MAJOR;
    }

}

int print(char *var){
    //Get the size of the shellMemory that isn't NULL
//    while(shellMemory[memory_size].value && shellMemory[memory_size].var){
//        memory_size ++;
//    }

    if(memory_size == 0){
        return ERR_NO_MEM;
    }

    if(memory_size > MEMORY_SIZE) {
        return ERR_MAX_MEM;
    }

    for(int i = 0; i < (memory_size); i++){ //possible unreachable code at i++
        if(strcmp(shellMemory[i].var, var) == 0){
            printf("%s = %s\n", shellMemory[i].var, shellMemory[i].value);
            memory_size++;
            return SUCCESS;
        }
    }
    return ERR_NO_VAR;
}

int run(char *file){
    FILE *script;
    script = fopen(file,"r");
    if (script == NULL){
        return ERR_FILE;
    }

    char text_input[INPUT_SIZE] = {0};
    int errCode = 0;

    while(fgets(text_input, sizeof(text_input), script)){
        printf("Auto command: %s", &text_input);
        errCode = parse(text_input);
            if(errCode != 0){
                ERR_DISPLAY(errCode)
                break;
            }
    }

    fclose(script);
}
