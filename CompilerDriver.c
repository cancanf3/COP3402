/* Author: Jose Pena
 * UCFID: 4142431
 * Tittle: Compiler Driver
 * Class: COP3402
 */
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

#include "./Lexical Analyzer/LexicalAnalyzer.h"
#include "./Parser/Parser.h"
#include "./Code Generator/CodeGenerator.h" 
#include "./Virtual Machine/VirtualMachine.h"
int main (int argc, char* argv[]) {

	// Auxiliary Structures
	queue* tokens;
	instruction code;
	stack* regis = createStack();
	code.codeSize = 0;
	for ( int i = 0 ; i < MAX_CODE_LENGTH ; i ++) {
		code.mem[i].op = 0;
		code.mem[i].r = 0;
		code.mem[i].l = 0;
		code.mem[i].m = 0;
	}

	// Flags to output
	int lFlag = 0;
	int aFlag = 0;
	int vFlag = 0;
	int opt;

	// Parsing the the flags
	while (( opt = getopt(argc, argv, "lav")) != -1) {
		switch (opt) {
			case 'l':
				lFlag = 1;
				break;
			case 'a':
				aFlag = 1;
				break;
			case 'v':
				vFlag = 1;
				break;
			default: 
				printf("Usage: %s [-l Tokens] [-a Assembly Code] [-v stack & cpu trace] \n", argv[0]);
				exit(EXIT_FAILURE);

		}
	}

	// Lexer
	tokens = LexicalAnalyzer(lFlag);
	if (tokens == NULL) {
		printf("Error in the Lexer\n");
		return 1;
	}


	// Parser and Generating Code (with Error Recovery)
	program(tokens, regis, &code);
	if(aFlag) {
		printf("\n\n\nAssembly Code Generated: \n");
		for (int i = 0; i < code.codeSize ; i++)
			printf(" %d: OP: %d R:%d L:%d M:%d \n",i,code.mem[i].op,code.mem[i].r,code.mem[i].l,code.mem[i].m);
	}
	//Virtual Machine
	VirtualMachine(vFlag, &code);


	// Freeing the Queue
	free(tokens);

	// Freeing the Stack
	while (regis->head != NULL)
		popStack(regis);
	free(regis);


}