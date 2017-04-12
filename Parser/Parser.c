/* Author: Jose Pena
 * UCFID: 4142431
 * Tittle: Parser
 * Class: COP3402
 */


#include "Parser.h"
int actualLevel = 0;


void program ( queue* q, stack* stacky,instruction* code) {

	hashTable* hashy = createHashTable();
	gen(6,0,3,stacky, code);
	block(q,hashy, stacky,code);
	// Terminal Period
	token t = deQueue(q);
	if ( t.tokenType !=  periodsym)
		error(9);

	gen(11,0,0, stacky,code);

	// Freeing the HashTable
	free(hashy);
}

void block ( queue* q, hashTable* h, stack* stacky,instruction* code) {
	int addressPosition;
	if (code->codeSize == 0 )
		addressPosition = 0;
	else
		addressPosition = 4;

	constDeclaration(q,h, stacky,code);
	varDeclaration(q,h,&addressPosition, stacky,code);
	procDeclaration(q,h, stacky,code);
	statement(q,h, stacky,code);
}

void constDeclaration ( queue* q, hashTable* h , stack* stacky,instruction* code) {
	token t;
	symbol s;
	if ( q->head->value.tokenType != constsym)
		return;

	do {
		// Terminal const or Comma
		t = deQueue(q);

		// Terminal Identifier
		t = deQueue(q);
		if ( t.tokenType != identsym )
			error(4);

		strcpy(s.name, t.value);

		// Terminal =
		t = deQueue(q);
		if (t.tokenType != eqlsym )
			error(0);

		// Terminal literal number
		t = deQueue(q);
		if (t.tokenType != numbersym )
			error(2);

		// Adding a Symbol to the table
		s.kind = 1;
		// Will change when procedure is implemented
		s.level = 0;
		
		s.val = atoi(t.value);
		insert(s, h);
	} while ( q->head->value.tokenType == commasym );

	// Terminal Semicolon
	t = deQueue(q);
	if ( t.tokenType != semicolonsym )
		error(5);

}

void varDeclaration ( queue* q, hashTable* h, int* addressPosition, stack* stacky,instruction* code) {
	token t;
	symbol s;
	int i = 0;
	if ( q->head->value.tokenType != varsym )
		return;

	do {
		// Terminal var or Comma
		t = deQueue(q);

		// Terminal Identifier
		t = deQueue(q);
		if ( t.tokenType != identsym )
			error(4);

		// Adding a Symbol to the table
		s.kind = 2;
		strcpy(s.name, t.value);
		// Will change when procedure is implemented
		s.level = 0;
		s.addr = *addressPosition;
		(*addressPosition)++;
		insert(s, h);
		i++;

	} while ( q->head->value.tokenType == commasym );

	// Terminal Semicolon
	t = deQueue(q);
	if ( t.tokenType != semicolonsym )
		error(5);
	gen(6,0,i,stacky, code);
}

void procDeclaration ( queue* q, hashTable* h, stack* stacky,instruction* code) {

	while ( q->head->value.tokenType == procsym ) {
		token t;
		symbol s;
		int temp = code->codeSize;
		gen(7,0,0, stacky,code);

		// Terminal Procedure
		t = deQueue(q);

		// Terminal Identifier
		t = deQueue(q);
		if ( t.tokenType != identsym )
			error(4);

		// Adding a Symbol to the table
		s.kind = 3;
		strcpy(s.name, t.value);
		s.level = actualLevel++;
		s.addr = code->codeSize;
		insert(s, h);
		hashTable* copy;
		copy = copyHashTable(h);

		// Terminal Semicolon
		t = deQueue(q);
		if ( t.tokenType != semicolonsym )
			error(5);
		gen(6,0,4,stacky, code);
		block(q,copy, stacky,code);
		gen(2,0,0, stacky, code);
		// Terminal Semicolon
		t = deQueue(q);
		if ( t.tokenType != semicolonsym )
			error(5);

		actualLevel--;
		free(copy);
		code->mem[temp].m = code->codeSize;
	}

}

void statement ( queue* q, hashTable* h, stack* stacky,instruction* code) {
	token t;
	symbol* s;
	// Terminal Identifier
	if ( q->head->value.tokenType == identsym ) {
		t = deQueue(q);

		//Checking if exist in the symbol table
		s = NULL;
		int i = actualLevel;
		while ( s == NULL && i != -1 )
			s = lookup(t.value,i--,h);

		if ( s == NULL )
			error(11);

		//Checking if it is a var 
		if (s->kind != 2)
			error(12);

		// Terminal :=
		t = deQueue(q);
		if ( t.tokenType != becomessym )
			error(3);
		expression(q,h, stacky,code);
		//Generating Code
		gen(04,s->level,s->addr, stacky,code);

	} // Terminal Call
	else if ( q->head->value.tokenType == callsym ) {
		t = deQueue(q);

		// Terminal Identifier
		t = deQueue(q);
		if ( t.tokenType != identsym )
			error(14);
		s = NULL;
		int i = actualLevel;
		while ( s == NULL && i != -1 )
			s = lookup(t.value,i--,h);

		if ( s == NULL )
			error(11);

		if (s->kind != 3)
			error(26);

		printf("actual: %d  lvl de la funcion: %d name de la func: %s \n",actualLevel ,s->level, s->name );
		gen(5,actualLevel - s->level, s->addr, stacky, code);


	} // Terminal if
	else if ( q->head->value.tokenType == ifsym ){
		int ctemp, ctemp1;
		t = deQueue(q);

		condition(q,h, stacky,code);

		// Terminal Then
		t = deQueue(q);
		if ( t.tokenType != thensym )
			error(16);

		ctemp = code->codeSize;
		gen(8,0,0, stacky,code);
		statement(q,h, stacky,code);
		ctemp1 = code->codeSize;
		// Terminal Else
		if ( q->head->value.tokenType == elsesym ) {
			gen(7,0,0, stacky,code);
			code->mem[ctemp].m = code->codeSize;
			t = deQueue(q);
			statement(q,h, stacky,code);
			code->mem[ctemp1].m = code->codeSize;
		}
		else
			code->mem[ctemp].m = code->codeSize;
	} // Terminal While
	else if ( q->head->value.tokenType == whilesym ) {
		int cx1 = code->codeSize;
		int cx2;
		t = deQueue(q);

		condition(q,h, stacky,code);

		cx2 = code->codeSize;
		gen(8,0,0, stacky,code);
		// Terminal Do
		t = deQueue(q);
		if ( t.tokenType != dosym )
			error(18);

		statement(q,h, stacky,code);
		gen(7,0,cx1, stacky,code);
		code->mem[cx2].m = code->codeSize;
	} // Terminal Read
	else if ( q->head->value.tokenType == readsym ) {
		t = deQueue(q);

		// Terminal Identifier
		t = deQueue(q);
		if ( t.tokenType != identsym )
			error(29);
				s = NULL;
		int i = actualLevel;
		while ( s == NULL && i != -1 )
			s = lookup(t.value,i--,h);
		gen(03,s->level,s->addr, stacky,code);
		gen(10,0,0,stacky, code);

	} // Terminal Write
	else if ( q->head->value.tokenType == writesym ) {
		t = deQueue(q);

		// Terminal Identifier
		t = deQueue(q);
		if ( t.tokenType != identsym )
			error(29);

		s = NULL;
		int i = actualLevel;
		while ( s == NULL && i != -1 )
			s = lookup(t.value,i--,h);
		gen(9,0,0,stacky, code);
		gen(04,s->level,s->addr, stacky,code);

	} // Terminal Begin
	else if ( q->head->value.tokenType == beginsym ) {
		t = deQueue(q);

		statement(q,h, stacky,code);

		// Terminal Semicolon
		while ( q->head->value.tokenType == semicolonsym ) {
			t = deQueue(q);
			statement(q,h, stacky,code);
		}

		// Terminal End
		t = deQueue(q);
		if ( t.tokenType != endsym )
			error(28);

	}

}

void condition (queue *q, hashTable* h, stack* stacky,instruction* code) {
	token t;
	printf("llega aca\n");
	// Terminal odd
	if ( q->head->value.tokenType == oddsym ) {
		t = deQueue(q);
		expression(q,h, stacky,code);
		gen(17,0,0, stacky,code);
	}
	else {
		expression(q,h, stacky,code);
		t = deQueue(q);
		if ( t.tokenType != eqlsym && t.tokenType != neqsym &&
			t.tokenType != lessym && t.tokenType != leqsym &&
			t.tokenType != gtrsym && t.tokenType != geqsym )
			error(30);

		expression(q,h, stacky,code);

		// Generatin code for the conditional
		if ( t.tokenType == eqlsym )
			gen(19,0,0, stacky,code);
		else if ( t.tokenType == neqsym )
			gen(20,0,0, stacky,code);
		else if ( t.tokenType == lessym )
			gen(21,0,0, stacky,code);
		else if ( t.tokenType == leqsym )
			gen(22,0,0, stacky,code);
		else if ( t.tokenType == gtrsym )
			gen(23,0,0, stacky,code);
		else
			gen(24,0,0, stacky,code);
	}
}

// void relOp( queue *q, hashTable* h ) {
// 	token t = deQueue(q);
// 	if ( t.tokenType != eqlsym && t.tokenType != neqsym &&
// 		t.tokenType != lessym && t.tokenType != leqsym &&
// 		t.tokenType != gtrsym && t.tokenType != geqsym )
// 		error(30);
// }

void expression ( queue* q, hashTable* h, stack* stacky,instruction* code) {
	token t;
	// Terminal + or -
	if ( q->head->value.tokenType == plussym || q->head->value.tokenType == minussym) {
		t = deQueue(q);
		term(q,h, stacky,code);

		// Generating Code for NEG operation
		if (t.tokenType == minussym)
			gen(12,0,0, stacky,code); 
	}

	else 
		term(q,h, stacky,code); 
	// Terminal + or -
	while ( q->head->value.tokenType == plussym || q->head->value.tokenType == minussym) {
		t = deQueue(q);
		term(q,h, stacky,code);
		// Generating Code for ADD operation
		if (t.tokenType == plussym)
			gen(13,0,0, stacky,code);
		// Generating Code for SUB operation
		else 
			gen(14,0,0, stacky,code);
	}
}

void term ( queue* q, hashTable* h, stack* stacky,instruction* code) {
	token t;
	factor(q,h, stacky,code);
	// Terminal * or /
	while ( q->head->value.tokenType == multsym || q->head->value.tokenType == slashsym ) {
		t = deQueue(q);
		factor(q,h, stacky,code);
		if (t.tokenType == multsym)
			gen(15,0,0, stacky,code);
		else
			gen(16,0,0, stacky,code);
	}
}

void factor (queue* q, hashTable* h, stack* stacky,instruction* code) {
	token t;
	symbol* s;
	// Identifier
	if (q->head->value.tokenType == identsym ) {
		t = deQueue(q);
		s = NULL;
		int i = actualLevel;
		while ( s == NULL && i != -1 ) {
			s = lookup(t.value,i--,h);
			printf("pegadooo\n");
		}
		if ( s == NULL )
			exit(11);
		if (s->kind == 2)
			gen(03,s->level,s->addr, stacky,code);
		else if (s->kind == 1)
			gen(01, 0,s->val, stacky,code);
		else
			error(12);
	}
	// Terminal Number
	else if (q->head->value.tokenType == numbersym ) {
		t = deQueue(q);
		gen(1, 0,atoi(t.value), stacky,code);
	}
	// Terminal (
	else if (q->head->value.tokenType == lparentsym ) {
		t = deQueue(q);

		expression(q,h, stacky,code);

		//Terminal )
		t = deQueue(q);
		if (t.tokenType != rparentsym)
			error(31);
	}
	else
		error(24);

}




void error ( int number ) {
	switch (number) {
		case 0:
			printf("Const most be followoed by =\n");
			break;
		case 1:
			printf("Use = instead of :=\n");
			break;
		case 2:
			printf("= must be followed by a number\n");
			break;
		case 3:
			printf("Identifier must be followed by :=\n");
			break;
		case 4:
			printf("const, var, procedure must be followed by identifier\n");
			break;
		case 5:
			printf("Semicolon or comma missing\n");
			break;
		case 6:
			printf("Incorrect symbol after procedure declaration\n");
			break;
		case 7:
			printf("Statement expected\n");
			break;
		case 8:
			printf("Incorrect symbol after statement part in block\n");
			break;
		case 9:
			printf("Period expected\n");
			break;
		case 10:
			printf("Semicolon between statements missing\n");
			break;
		case 11:
			printf("Undeclared identifier\n");
			break;
		case 12:
			printf("Assignment to constant or procedure is not allowed\n");
			break;
		case 13:
			printf("Assignment operator expected\n");
			break;
		case 14:
			printf("call must be followed by an identifier\n");
			break;
		case 15:
			printf("Call of a constant or variable is meaningless\n");
			break;
		case 16:
			printf("then	 expected\n");
			break;
		case 17:
			printf("Semicolon or } expected\n");
			break;
		case 18:
			printf("do expected\n");
			break;
		case 19:
			printf("Incorrect symbol following statement\n");
			break;
		case 20:
			printf("Relational operator expected\n");
			break;
		case 21:
			printf("Expression must not contain a procedure identifier\n");
			break;
		case 22:
			printf("Right parenthesis missing\n");
			break;
		case 23:
			printf("The preceding factor cannot begin with this symbol\n");
			break;
		case 24:
			printf("An expression cannot begin with this symbol\n");
			break;
		case 25:
			printf("This number is too large\n");
			break;			
		case 26:
			printf("procedure expected\n");
			break;
		case 27:
			printf("Begin Expected\n");
			break;
		case 28:
			printf("End Expected\n");
			break;
		case 29: 
			printf("Read/Write must be followed by a identifier\n");
			break;
		case 30:
			printf("Compare operator expected\n");
			break;
		case 31:
			printf(") expected\n");
			break;
		default:
			printf("undeclared error\n");
			break;
	}
	exit(EXIT_FAILURE);
}