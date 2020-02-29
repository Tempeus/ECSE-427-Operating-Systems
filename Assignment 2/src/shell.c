#include "interpreter.h"
#include "shellmemory.h"

#include <stdio.h>
#include <stdlib.h>

int shell_ui(){
    printf("Welcome to the Kevin Kernel!\n"
           "Welcome to the Kevin's Shell!\n"
           "Version 2.0 Created January 2020\n");

    shell_memory_initialize();

    while (!feof(stdin))
    {
        printf("$ ");
        fflush(stdout);

        char *line = NULL;
        size_t linecap = 0;
        if (getline(&line, &linecap, stdin) == -1)
            break;

        (void)interpret(line);
        free(line);
    }

    shell_memory_destory();

    return 0;
}