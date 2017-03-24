#ifndef CODEGEN
#define CODEGEN

#define MAX_CODE_LENGTH 500

#include "../Auxiliar Structures/Stack.h"


typedef struct memory {
	int op; // OP code
	int r;  // reg
	int l;  // L
	int m;  // M
}memory;

typedef struct {
	memory mem[MAX_CODE_LENGTH];
	int codeSize;
}instruction;

void gen(int opr, int l, int m, stack* s, instruction* code);


#endif 

