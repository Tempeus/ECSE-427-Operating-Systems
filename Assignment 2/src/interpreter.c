#include "shellmemory.h"
#include "kernel.h"
#include "interpreter.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

int flag_quit = 1;

char **tokenize(char *str)
{
    size_t num_tokens = 1;
    int flag = 0;
    for (size_t i = 0; i < strlen(str); i++)
    {
        if (flag == 0 && str[i] == ' ')
        {
            num_tokens = num_tokens + 1;
            flag = 1;
        }
        if (str[i] != ' ')
        {
            flag = 0;
        }
    }
    char **ret_arr =
        (char **)malloc(sizeof(char *) * (num_tokens + 1));

    if (ret_arr == NULL)
    {
        perror("malloc");
        return NULL;
    }
    flag = 0;
    int ignore_flag = 0;
    char *modified_str = (char *)str;
    size_t counter = 0;
    const size_t length_str = strlen(str);
    for (size_t i = 0; i < length_str; i++)
    {
        if (modified_str[i] == '\n' || modified_str[i] == '\r')
            modified_str[i] = ' ';
        if (modified_str[i] == '"')
        {
            ignore_flag = ignore_flag ^ 0x1;
        }
        if (flag == 0 && modified_str[i] != ' ')
        {
            ret_arr[counter] = &(modified_str[i]);
            counter = counter + 1;
            flag = 1;
        }
        if (modified_str[i] == '\\' && modified_str[i + 1] == ' ')
        {
            i++;
            continue;
        }
        if (flag == 1 && modified_str[i] == ' ' && ignore_flag == 0)
        {
            modified_str[i] = '\0';
            flag = 0;
            continue;
        }
    }
    ret_arr[counter] = NULL;

    for (size_t i = 0; i < counter; ++i)
    {
        if (ret_arr[i][0] == '\"' &&
            ret_arr[i][strlen(ret_arr[i] - 1)] == '\"')
        {
            ret_arr[i][strlen(ret_arr[i]) - 1] = '\0';
            ret_arr[i] = ret_arr[i] + 1;
        }
    }

    return ret_arr;
}

int in_file_flag = 0;
int interpret(char *raw_input);

int help()
{
    printf(""
           "COMMAND         DESCRIPTION\n"
           "help            Displays all the commands\n"
           "quit            Exits / terminates the shell with \"Bye!\"\n"
           "set VAR STRING  Assigns a value to shell memory\n"
           "print VAR       Displays the STRING assigned to VAR\n"
           "run SCRIPT.TXT  Executes the file SCRIPT.TXT\n");
    return 0;
}

int quit()
{
    printf("Bye!\n");
    if (in_file_flag == 0 && flag_quit)
    {
        shell_memory_destory();
        exit(0);
    }
    else
        flag_quit = 1;
    return 0;
}

int run(const char *path)
{
    flag_quit = 1;
    FILE *file = fopen(path, "r");
    if (file == NULL)
    {
        printf("Script not found.\n");
        return 1;
    }
    int enter_flag_status = in_file_flag;
    in_file_flag = 1;
    while (!feof(file))
    {
        char *line = NULL;
        size_t linecap = 0;
        getline(&line, &linecap, file);

        int status = interpret(line);
        free(line);
        if (status != 0)
        {
            break;
            return status;
        }
    }
    fclose(file);
    in_file_flag = enter_flag_status;
    return 0;
}

int set(const char *key, const char *value)
{
    int status = shell_memory_set(key, value);
    if (status != 0)
        printf("set: Unable to set shell memory.\n");
    return status;
}

int print(const char *key)
{
    const char *value = shell_memory_get(key);
    if (value == NULL)
    {
        printf("print: Undefiend value.\n");
        return 1;
    }
    printf("%s\n", value);
    return 0;
}

/**
 * Function is used to check if the two files are the same
 * @param s1    first file
 * @param s2    second file
 * @return      boolean
 */
int checkSameFile(FILE *s1, FILE *s2){
    if(strcmp(s1, s2) == 0)
        return TRUE;
    else
        return FALSE;
}

/**
 * FUnction is used to check if the three files are the same
 * @param s1    first file
 * @param s2    second file
 * @param s3    third file
 * @return      boolean
 */
int checkSame3File(FILE *s1, FILE *s2, FILE *s3){
    if(checkSameFile(s1, s3) == TRUE || checkSameFile(s2, s3) == TRUE || checkSameFile(s1,s2) == TRUE)
        return TRUE;
    else
        return FALSE;
}

int exec(char* f1, char* f2, char* f3){
    FILE *src1;
    FILE *src2;
    FILE *src3;

    //if there is potentially more than one file
    if(f2){
        //if f1 and f2 are the same
        if(checkSameFile(f1, f2) == TRUE){
            printf("Error: %s is already being loaded!", f2);
            return 1;
        }
        else{
            //if there is a third file
            if(f3){
                //if f3 is the same as one of the other files
                if(checkSame3File(f1, f2, f3) == TRUE){
                    printf("Error: %s is already being loaded!", f3);
                    return 1;
                }

                else{
                        src1 = fopen(f1, "rt");
                        src2 = fopen(f2, "rt");
                        src3 = fopen(f3, "rt");
                        if(!src1 || !src2 || !src3){
                            printf("Error: One or more of the files can't be found\n");
                            return 1;
                        }

                        //if nothing went wrong in initializing kernel for each file
                        if(initialize_kernel(src1) == 0 && initialize_kernel(src2) == 0 && initialize_kernel(src3) == 0){
                            scheduler();
                            printf("three files have been successfully loaded!\n");
                            return 0;
                        }
                        else
                            return 1;
                }
            }
            //if there is only two files
            else{
                src1 = fopen(f1, "rt");
                src2 = fopen(f2, "rt");
                if(!src1 || !src2){
                    printf("Error: One of the files can't be found!\n");
                    return 1;
                }

                //if nothing went wrong in initializing kernel of each file
                if(!initialize_kernel(src1) && !initialize_kernel(src2)){
                    scheduler();
                    printf("two files have successfully been loaded!\n");
                    return 0;
                }
                else
                    return 1;
            }
        }
    }

    //if there is only one file
    else{
        src1 = fopen(f1, "rt");
        //if the file can't be found
        if(!src1){
            printf("Error: %s cannot be found", f1);
            return 1;
        }

        //if error occured when initializing the kernel on the file
        if(initialize_kernel(src1) == 0)
            scheduler();
        else
            return 1;

        printf("one file is successfully loaded\n");
        return 0;
    }
}

int interpret(char *raw_input)
{
    char **tokens = tokenize(raw_input);

    if (tokens[0] == NULL)
        return 0; // empty command

    if (strcmp(tokens[0], "help") == 0)
    {
        if (tokens[1] != NULL)
        {
            printf("help: Malformed command\n");
            free(tokens);
            return 1;
        }
        free(tokens);
        return help();
    }

    if (strcmp(tokens[0], "quit") == 0)
    {
        if (tokens[1] != NULL)
        {
            printf("quit: Malformed command\n");
            free(tokens);
            return 1;
        }
        free(raw_input);
        free(tokens);
        return quit();
    };

    if (strcmp(tokens[0], "set") == 0)
    {
        if (!(tokens[1] != NULL && tokens[2] != NULL))
        {
            printf("set: Malformed command\n");
            free(tokens);
            return 1;
        }
        int status = set(tokens[1], tokens[2]);
        free(tokens);
        return status;
    }

    if (strcmp(tokens[0], "print") == 0)
    {
        if (!(tokens[1] != NULL && tokens[2] == NULL))
        {
            printf("print: Malformed command\n");
            free(tokens);
            return 1;
        }
        int status = print(tokens[1]);
        free(tokens);
        return status;
    }

    if (strcmp(tokens[0], "run") == 0)
    {
        if (!(tokens[1] != NULL && tokens[2] == NULL))
        {
            printf("run: Malformed command\n");
            free(tokens);
        }
        int result = run(tokens[1]);
        free(tokens);
        return result;
    }

    if(strcmp(tokens[0], "exec") == 0){
        if(!(tokens[1] != NULL)){
            printf("exec: Malformed command \n");
            free(tokens);
            return 1;
        }
        int retsts = exec(tokens[1], tokens[2], tokens[3]);
        free(tokens);
        return retsts;
    }

    printf("Unrecognized command \"%s\"\n", tokens[0]);
    free(tokens);
    return 1;
}