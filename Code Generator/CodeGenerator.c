#include "CodeGenerator.h"

void gen(int opr, int l, int m, stack* s, instruction* code) {

	switch (opr) {
			case 01:
				// LIT
				code->mem[code->codeSize].op = opr;
				code->mem[code->codeSize].l = l;
				code->mem[code->codeSize].m = m;
				code->mem[code->codeSize].r = s->size;
				pushStack(s->size,s); 
				break;

			case 02:
				// RTN
				code->mem[code->codeSize].op = opr;
				break;

			case 03:
				// LOD
				code->mem[code->codeSize].op = opr;
				code->mem[code->codeSize].l = l;
				code->mem[code->codeSize].m = m;
				code->mem[code->codeSize].r = s->size;
				pushStack(s->size, s);
				break;

			case 04:
				// STO
				code->mem[code->codeSize].op = opr;
				code->mem[code->codeSize].l = l;
				code->mem[code->codeSize].m = m;
				code->mem[code->codeSize].r = popStack(s);
				break;

			case 05:
				// CAL
				break;

			case 06:
				// INC
				code->mem[code->codeSize].op = opr;
				code->mem[code->codeSize].m = m;
				code->mem[code->codeSize].l = l;
				break;

			case 07:
				// JMP
				code->mem[code->codeSize].op = opr;
				code->mem[code->codeSize].l = l;
				code->mem[code->codeSize].m = m;
				break;

			case 8:
				// JPC
				code->mem[code->codeSize].op = opr;
				code->mem[code->codeSize].l = l;
				code->mem[code->codeSize].m = m;
				code->mem[code->codeSize].r = popStack(s);
				break;

			case 9:
				// SIO Write
				code->mem[code->codeSize].op = opr;
				popStack(s);
				code->mem[code->codeSize].r  = s->size;
				pushStack(s->size, s);
				break;

			case 10:
				// SIO Read
				code->mem[code->codeSize].op = opr;
				popStack(s);
				code->mem[code->codeSize].r  = s->size;
				pushStack(s->size, s);
				break;

			case 11:
				// SIO Halt
				code->mem[code->codeSize].op = opr;
				break;

			case 12:
				// NEG
				code->mem[code->codeSize].op = opr;
				code->mem[code->codeSize].l = popStack(s);
				code->mem[code->codeSize].r = s->size;
				pushStack(s->size, s);
				break;

			case 13:
				// ADD
				popStack(s);
				code->mem[code->codeSize].op = opr;
				code->mem[code->codeSize].l = s->size-1;
				code->mem[code->codeSize].m = s->size;
				code->mem[code->codeSize].r = s->size-1;				
			    break;

			case 14:
				// SUB
				popStack(s);
				code->mem[code->codeSize].op = opr;
				code->mem[code->codeSize].l = s->size-1;
				code->mem[code->codeSize].m = s->size;
				code->mem[code->codeSize].r = s->size-1;
				break;

			case 15:
				// MUL
				popStack(s);
				code->mem[code->codeSize].op = opr;
				code->mem[code->codeSize].l = s->size-1;
				code->mem[code->codeSize].m = s->size;
				code->mem[code->codeSize].r = s->size-1;
				break;

			case 16:
				// Div
				popStack(s);
				code->mem[code->codeSize].op = opr;
				code->mem[code->codeSize].l = s->size-1;
				code->mem[code->codeSize].m = s->size;
				code->mem[code->codeSize].r = s->size-1;
				break;

			case 17:
				// ODD
				code->mem[code->codeSize].op = opr;
				code->mem[code->codeSize].r = popStack(s);
				pushStack(s->size, s);
	 			break;

	 		case 18:
	 			// MOD
				popStack(s);
				code->mem[code->codeSize].op = opr;
				code->mem[code->codeSize].l = s->size-1;
				code->mem[code->codeSize].m = s->size;
				code->mem[code->codeSize].r = s->size-1;
	 			break;

	 		case 19:
	 			// EQL
				popStack(s);
				code->mem[code->codeSize].op = opr;
				code->mem[code->codeSize].l = s->size-1;
				code->mem[code->codeSize].m = s->size;
				code->mem[code->codeSize].r = s->size-1;
	 			break;

	 		case 20:
	 			// NEQ
				popStack(s);
				code->mem[code->codeSize].op = opr;
				code->mem[code->codeSize].l = s->size-1;
				code->mem[code->codeSize].m = s->size;
				code->mem[code->codeSize].r = s->size-1;
	 			break;

	 		case 21:
	 			// LSS
				popStack(s);
				code->mem[code->codeSize].op = opr;
				code->mem[code->codeSize].l = s->size-1;
				code->mem[code->codeSize].m = s->size;
				code->mem[code->codeSize].r = s->size-1;
	 			break;

	 		case 22:
	 			// LEQ
				popStack(s);
				code->mem[code->codeSize].op = opr;
				code->mem[code->codeSize].l = s->size-1;
				code->mem[code->codeSize].m = s->size;
				code->mem[code->codeSize].r = s->size-1;
	 			break;

	 		case 23:
	 			// GTR
				popStack(s);
				code->mem[code->codeSize].op = opr;
				code->mem[code->codeSize].l = s->size-1;
				code->mem[code->codeSize].m = s->size;
				code->mem[code->codeSize].r = s->size-1;
	 			break;

	 		case 24:
	 			// GEQ
				popStack(s);
				code->mem[code->codeSize].op = opr;
				code->mem[code->codeSize].l = s->size-1;
				code->mem[code->codeSize].m = s->size;
				code->mem[code->codeSize].r = s->size-1;
	 			break;


	}
	// Incrementing the number of Instructions
	code->codeSize++;

}