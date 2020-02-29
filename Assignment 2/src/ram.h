#ifndef ECSE427_ASSIGNMENT2_RAM_H
#define ECSE427_ASSIGNMENT2_RAM_H

#define MEMORY_SPACE 1000

void initialize_ram();
int insert_ram(FILE *file);
void delete_ram(int start_index, int end_index);

extern char* ram[MEMORY_SPACE];
extern int ram_start;
extern int ram_end;
#endif //ECSE427_ASSIGNMENT2_RAM_H
