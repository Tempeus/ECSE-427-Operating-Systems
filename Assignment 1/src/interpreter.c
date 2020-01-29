#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "interpreter.h"

int interpreter(char *words[]){
    int errCode = 0;

    if (strcmp(words[0], "help") == 0){
        printf(CMD_HELP);
    }

    else if(strcmp(words[0], "quit") == 0)
        return EXIT;

    else if(strcmp(words[0], "set") == 0){
        //Check if there are two arguments in the input
        if(!words[1] || !words[2])
            return ERR_FEW_ARGS;

        if(words[3])
            return ERR_MANY_ARGS;

        int w = 3;
        while(words[w]){
            words[2] = strcat(words[2], " ");
            words[2] = strcat(words[2], words[w]);
            w++;
        }

        errCode = set(words[1], words[2]);
    }

    else if(strcmp(words[0], "print") == 0){
        //check if there is an argument in the input
        if(!words[1])
            return ERR_FEW_ARGS;

        //check if there are too many arguments in the input
        else if(words[2])
            return ERR_MANY_ARGS;

        else
            errCode = print(words[1]);
    }

    else if(strcmp(words[0], "run") == 0){
        //Check to see if there are too few arguments
        if(!words[1])
            return ERR_FEW_ARGS;

        //Check to see if there are too many arguments
        else if(words[2])
            return ERR_MANY_ARGS;

        else
            errCode = run(words[1]);
    }

    //if strcmp doesnt work, that means it doesn't exist
    else errCode = ERR_NO_CMD;

    return errCode;
}

