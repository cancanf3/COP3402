/* Author: Jose Pena
 * UCFID: 4142431
 * Tittle: Virtual Machine
 * Class: COP3402
 */

#include <stdio.h>

#define MAX_STACK_HEIGHT 2000
#define MAX_CODE_LENGTH 500
#define MAX_LEXI_LEVELS 2000

typedef struct {
	int op; // OP code
	int r;  // reg
	int l;  // L
	int m;  // M
} instruction; 

int load_Instruction ( instruction *code );
int fetch_Cycle (instruction *code, instruction *ir, int *pc);
int execute_Cycle (instruction ir, int *stack, int *rf, int *bp, int *sp, int *pc, int *halt, int *call);
void output_Instruction ( instruction *code, int instructions );
 

int main () {

	// Registers 
	int bp;
	int sp;
	int pc;
	int rf[16];
	instruction ir;

	// Memory Stack
	int stack[MAX_STACK_HEIGHT];
	// Memory Code
	instruction code[MAX_CODE_LENGTH];

	int mark[MAX_LEXI_LEVELS];


	// Initialization 
	bp = 1;
	sp = 0;
	pc = 0;
	ir.op = 0;
	ir.r = 0;
	ir.l = 0;
	ir.m = 0;

	for (int i = 0 ; i < 16 ; i++)
		rf[i] = 0;
	for (int i = 0 ; i < MAX_STACK_HEIGHT ; i++)
		stack[i] = 0;
	for (int i = 0 ; i < MAX_CODE_LENGTH ; i++) {
		code[i].op = 0;
		code[i].r = 0;
		code[i].l = 0;
		code[i].m = 0;
	}

	for ( int i = 0 ; i < MAX_LEXI_LEVELS ; i++)
		mark[i] = 0;

	int instructions = load_Instruction(code);
	output_Instruction(code, instructions);


	// Program Cycle

	int halt = 0;
	int call = 0;
	int marks = 0;

	printf("\n\n");
	printf("Initial Values\t\t\t\tpc\tbp\tsp\n");
	
	while (halt == 0 && pc < instructions) {
		// Fetch Cycle
		if (fetch_Cycle(code, &ir, &pc) != 0) {
			printf("Error in Fetch Cycle...Aborting! \n");
			return 1;
		}

		// Execute Cycle
		printf("%d\t", pc-1);
		if (execute_Cycle(ir, stack, rf, &bp, &sp, &pc, &halt, &call)) {
			printf("Error in Fetch Cycle...Aborting! \n");
			return 1;
		}

		// Mark between Activation Records
		if (call == 1)
			mark[marks++] = bp;
		else if (call == 2) {
			mark[marks--] = 0;
		}

		// Stack Trace
		printf("Stack:\t");
		int j = 0;
		for (int i = 0 ; i <= sp ; i++) {
			if (mark[j] == i && i) {
				j++;
				printf("| ");
			}
			printf("%d ", stack[i]);
		}
		printf("\n");

		// Returning from the main
		if (call == 2 && pc == 0)
			break;
		call = 0;

	}

	return 0;

}

int load_Instruction ( instruction *code ) {
	char name[100];
	printf("select the input file: ");
	scanf("%s", name);
	FILE *file = fopen(name, "r");
	int i = 0;
	while (4 == fscanf(file, "%d %d %d %d", &(code[i].op), &(code[i].r), &(code[i].l), &(code[i].m)))
		i++;

	fclose(file);
	return i;
}

int base ( int l, int base, int *stack ) {
	int b1; //find base L levels 
	down
	b1 = base;

	while (l > 0) {
		b1 = stack[b1 + 1];
		l--;
	}
	return b1;
}

int fetch_Cycle (instruction *code, instruction *ir, int *pc) {

	if (*pc >= 500 || *pc < 0)
		return 1;

	ir->op = code[*pc].op;
	ir->r = code[*pc].r;
	ir->l = code[*pc].l;
	ir->m = code[*pc].m;

	*pc += 1;

	return 0;
}

int execute_Cycle (instruction ir, int *stack, int *rf, int *bp, int *sp, int *pc, int *halt, int *call) {
	int sio = 0;

	switch (ir.op) {
		case 1:
			// LIT
			rf[ir.r] = ir.m;
			printf("LIT\t");
			break;

		case 2:
			// RTN
			*sp = *bp - 1;
			*bp = stack[*sp + 3];
			*pc = stack[*sp + 4];
			*call = 2;
			printf("RTN\t");
			break;

		case 3:
			// LOD
			rf[ir.r] = stack[base(ir.l, *bp, stack) + ir.m];
			printf("LOD\t");
			break;

		case 4:
			// STO
			stack[base(ir.l, *bp, stack) + ir.m] = rf[ir.r];
			printf("STO\t");
			break;

		case 5:
			// CAL
			stack[*sp + 1] = 0;
			stack[*sp + 2] = base(ir.l, *bp, stack);
			stack[*sp + 3] = *bp;
			stack[*sp + 4] = *pc;
			*bp = *sp + 1;
			*pc = ir.m;
			*call = 1;
			printf("CAL\t");
			break;

		case 6:
			// INC
			*sp = *sp + ir.m;
			printf("INC\t");
			break;

		case 7:
			// JMP
			*pc = ir.m;
			printf("JMP\t");
			break;

		case 8:
			// JPC
			if (rf[ir.r] == 0)
				*pc = ir.m;
			printf("JPC\t");
			break;

		case 9:
			// SIO
			sio = 1;
			printf("SIO\t");
			break;

		case 10:
			// SIO
			sio = 2;
			printf("SIO\t");
			break;

		case 11:
			// SIO
			*halt = 1;
			printf("SIO\t");
			break;

		case 12:
			// NEG
			rf[ir.r] = -rf[ir.l];
			printf("NEG\t");
			break;

		case 13:
			// ADD
		    rf[ir.r] = rf[ir.l] + rf[ir.m];
		    printf("ADD\t");
		    break;

		case 14:
			// SUB
			rf[ir.r] = rf[ir.l] - rf[ir.m];
			printf("SUB\t");
			break;

		case 15:
			// MUL
			rf[ir.r] = rf[ir.l] * rf[ir.m];
			printf("MUL\t");
			break;

		case 16:
			// Div
			rf[ir.r] = rf[ir.l] / rf[ir.m];
			printf("Div\t");
			break;

		case 17:
			// ODD
			rf[ir.r] = rf[ir.r] % 2;
			printf("ODD\t");
 			break;

 		case 18:
 			// MOD
 			rf[ir.r] = rf[ir.l] % rf[ir.m];
 			printf("MOD\t");
 			break;

 		case 19:
 			// EQL
 			rf[ir.r] = (rf[ir.l] == rf[ir.m]);
 			printf("EQL\t");
 			break;

 		case 20:
 			// NEQ
 			rf[ir.r] = rf[ir.l] != rf[ir.m];
 			printf("NEQ\t");
 			break;

 		case 21:
 			// LSS
 			rf[ir.r] = rf[ir.l] < rf[ir.m];
 			printf("LSS\t");
 			break;

 		case 22:
 			// LEQ
 			rf[ir.r] = rf[ir.l] <= rf[ir.m];
 			printf("LEQ\t");
 			break;

 		case 23:
 			// GTR
 			rf[ir.r] = rf[ir.l] > rf[ir.m];
 			printf("GTR\t");
 			break;

 		case 24:
 			// GEQ
 			rf[ir.r] = rf[ir.l] >= rf[ir.m];
 			printf("GEQ\t");
 			break;
 		default:
 			return 1;
	}

	printf("%d\t%d\t%d\t%d\t%d\t%d\t\n", ir.r, ir.l, ir.m, *pc, *bp, *sp);

	// Standard Input/Output
	if (sio == 1)
		printf("Register: %d\n", rf[ir.r]);
	else if (sio ==2)
		scanf("%d", &rf[ir.r]);

	// CPU Trace
	printf("CPU:\t");
	for (int i = 0 ; i < 16 ; i ++)
		printf("%d ", rf[i]);
	printf("\n");

	return 0;

}

void output_Instruction ( instruction *code, int instructions ) {
	int i;
	printf("\nLine\tOP\tR\tL\tM\n");

	for ( i = 0 ; i < instructions ; i ++ ) {
		printf("%d\t",i);
		switch (code[i].op) {

			case 01:
				// LIT
				printf("LIT\t");
				break;

			case 02:
				// RTN
				printf("RTN\t");
				break;

			case 03:
				// LOD
				printf("LOD\t");
				break;

			case 04:
				// STO
				printf("STO\t");
				break;

			case 05:
				// CAL
				printf("CAL\t");
				break;

			case 06:
				// INC
				printf("INC\t");
				break;

			case 07:
				// JMP
				printf("JMP\t");
				break;

			case 8:
				// JPC
				printf("JPC\t");
				break;

			case 9:
				// SIO
				printf("SIO\t");
				break;

			case 10:
				// SIO
				printf("SIO\t");
				break;

			case 11:
				// SIO
				printf("SIO\t");
				break;

			case 12:
				// NEG
				printf("NEG\t");
				break;

			case 13:
				// ADD
			    printf("ADD\t");
			    break;

			case 14:
				// SUB
				printf("SUB\t");
				break;

			case 15:
				// MUL
				printf("MUL\t");
				break;

			case 16:
				// Div
				printf("Div\t");
				break;

			case 17:
				// ODD
				printf("ODD\t");
	 			break;

	 		case 18:
	 			// MOD
	 			printf("MOD\t");
	 			break;

	 		case 19:
	 			// EQL
	 			printf("EQL\t");
	 			break;

	 		case 20:
	 			// NEQ
	 			printf("NEQ\t");
	 			break;

	 		case 21:
	 			// LSS
	 			printf("LSS\t");
	 			break;

	 		case 22:
	 			// LEQ
	 			printf("LEQ\t");
	 			break;

	 		case 23:
	 			// GTR
	 			printf("GTR\t");
	 			break;

	 		case 24:
	 			// GEQ
	 			printf("GEQ\t");
	 			break;
		}
		printf("%d\t%d\t%d\n",code[i].r,code[i].l,code[i].m);
	}
}