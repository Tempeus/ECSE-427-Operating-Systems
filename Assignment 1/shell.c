#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "shell.h"

/***************************** COMMANDS ****************************
           help                 Displays all the commands
           quit                 Exits / terminates the shell with “Bye!”
           set     VAR STRING   Assigns a value to shell memory
           print   VAR          Displays the STRING assigned to VAR
           run     SCRIPT.TXT   Executes the file SCRIPT.TXT
********************************************************************/

int main() {
    printf("Welcome to the Kevin shell!\n");
    printf("Version 1.0 Created January 2020\n");
    char prompt[100] = {'$', '\0'};
    char userInput[INPUT_SIZE] = {0};
    int errorCode = 0;

    while(1){
        printf("%s", &prompt);
        fgets(userInput, 999, stdin);
        if(checkSizeOfInput(userInput, INPUT_SIZE) == ERR_EXCEED_LIMIT){
            printf("ERROR: inputted command exceeded the character limit of 999, please try again\n");
            continue;
        }
        errorCode = parse(userInput);
        ERR_DISPLAY(errorCode)
    }

}

int parse(char ui[]){

    int a,b;
    char *words[100] = {0};
    int w = 0;

    //skipping the white spaces
    for (a = 0; ui[a] == ' ' && a < 1000; a++);

    while(ui[a] != '\0' && a < 1000){
        char tmp[200] = {0};
        for(b = 0; ui[a] != '\0' && ui[a] != ' ' && ui[a] != '\n' && a < 1000; a++, b++)
                tmp[b] = tolower(ui[a]);

        tmp[b] = '\0';

        words[w] = strdup(tmp);

        a++;
        w++;
    }
    return interpreter(words);
}

int checkSizeOfInput(char* input, int limit){
    if(strlen(input) < limit){
        return SUCCESS;
    }
    else{
        return ERR_EXCEED_LIMIT;
    }
}