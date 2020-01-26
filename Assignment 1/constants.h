#ifndef ECSE427_ASSIGNMENT1_CONSTANTS_H
#define ECSE427_ASSIGNMENT1_CONSTANTS_H

/* ERROR CODES OR EXIT CODE */
#define EXIT -1
enum{
    SUCCESS,
    ERR_EXCEED_LIMIT,
    ERR_FEW_ARGS,
    ERR_MANY_ARGS,
    ERR_NO_CMD,
    ERR_NO_VAR,
    ERR_MAX_MEM,
    ERR_NO_MEM,
    ERR_FILE,
    ERR_MAJOR
};

/* ERROR CODE DISPLAY */
#define ERR_DISPLAY(x)                                                          \
switch(x){                                                                      \
    case SUCCESS:                                                               \
        break;                                                                  \
                                                                                \
    case EXIT:                                                                  \
        printf("Bye!");                                                         \
        exit(99);                                                               \
                                                                                \
    case ERR_FEW_ARGS:                                                          \
        printf("ERROR: Too few arguments for this command\n");                  \
        break;                                                                  \
                                                                                \
    case ERR_MANY_ARGS:                                                         \
        printf("ERROR: Too many arguments for this command\n");                 \
        break;                                                                  \
                                                                                \
    case ERR_NO_CMD:                                                            \
        printf("ERROR: Command does not exist\n");                              \
        break;                                                                  \
                                                                                \
    case ERR_NO_VAR:                                                            \
        printf("ERROR: Variable cannot be found\n");                            \
        break;                                                                  \
                                                                                \
    case ERR_MAX_MEM:                                                           \
        printf("ERROR: Memory is at maximum capacity\n");                       \
        break;                                                    \
                                                                                \
    case ERR_NO_MEM:                                                            \
        printf("ERROR: There are no variables stored in memory\n");             \
        break;                                                                  \
                                                                                \
    case ERR_FILE:                                                              \
        printf("ERROR: failed to open file\n");                                 \
        break;                                                                  \
                                                                                \
    case ERR_MAJOR:                                                             \
        printf("ERROR: Something went wrong, please restart the shell\n");      \
        break;                                                                  \
                                                                                \
    default:                                                                    \
        break;                                                                  \
}                                                                               \

/* HELP DISPLAY */
#define CMD_HELP "        help               Displays all the commands\n\
        quit               Exits / terminates the shell with “Bye!”\n\
        set VAR STRING     Assigns a value to shell memory\n\
        print VAR          Displays the STRING assigned to VAR\n\
        run SCRIPT.TXT     Executes the file SCRIPT.TXT\n"

/* SIZES */
#define INPUT_SIZE 1000
#define MEMORY_SIZE 1000

/* MEMORY STRUCTURE */
typedef struct MEM{
    char *var;
    char *value;
} shell_memory;

#endif //ECSE427_ASSIGNMENT1_CONSTANTS_H
