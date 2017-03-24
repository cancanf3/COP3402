#ifndef VIRTUALM
#define VIRTUALM

#include <stdio.h>

#define MAX_STACK_HEIGHT 2000
#define MAX_CODE_LENGTH 500
#define MAX_LEXI_LEVELS 2000

#include "../Code Generator/CodeGenerator.h"

void VirtualMachine ( int flag, instruction *code);
int load_Instruction ( memory *code );
int fetch_Cycle (memory *code, memory *ir, int *pc);
int execute_Cycle (memory ir, int *stack, int *rf, int *bp, int *sp, int *pc, int *halt, int *call, int flag);
void output_Instruction ( memory *code, int memory );

#endif