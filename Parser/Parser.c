/* Author: Jose Pena
 * UCFID: 4142431
 * Tittle: Parser
 * Class: COP3402
 */


#include "Parser.h"
int actualLevel = 0;
setsym *declbegsys;
setsym *statbegsys;
setsym *facbegsys;

void program ( queue* q, stack* stacky,instruction* code ) {
	setsym fsys;
	fsys.size = 0;
	declbegsys = createSet();
	statbegsys = createSet();
	facbegsys = createSet();

	addElement(constsym, declbegsys);
	addElement(varsym, declbegsys);
	addElement(procsym, declbegsys);

	addElement(beginsym, statbegsys);
	addElement(callsym, statbegsys);
	addElement(ifsym, statbegsys);
	addElement(whilesym, statbegsys);

	addElement(identsym, facbegsys);
	addElement(numbersym, facbegsys);
	addElement(lparentsym, facbegsys);

	fsys = mergeSet(*declbegsys, *statbegsys);
	addElement(periodsym, &fsys);



	hashTable* hashy = createHashTable();
	gen(6,0,3,stacky, code);
	block(q,hashy, stacky,code, fsys);
	// Terminal Period
	token t = deQueue(q);
	if ( t.tokenType !=  periodsym)
		error(0,9);

	gen(11,0,0, stacky,code);

	// Freeing
	free(hashy);
	free(declbegsys);
	free(statbegsys);
	free(facbegsys);
}
// fsys { const, var, procedure, begin, call, if, while, . }
// Proc fsys { const, var, procedure, begin, call, if, while, ., ; }
void block ( queue* q, hashTable* h, stack* stacky,instruction* code, setsym fsys) {
	int addressPosition = 4;
	setsym testset = copySet(statbegsys);
	setsym aux = copySet(&fsys);
	addElement(identsym,&testset);

	constDeclaration(q,h, stacky,code);
	varDeclaration(q,h,&addressPosition, stacky,code);
	procDeclaration(q,h, stacky,code, fsys);
	test(testset, *declbegsys, 7, q);

	if (existElement(q->head->value.tokenType, *declbegsys))
		return;

	addElement(semicolonsym, &fsys);
	addElement(endsym, &fsys);
	statement(q,h, stacky,code,fsys);
	setsym* testset1 = createSet();
	test(aux, *testset1, 8, q);
	free(testset1);
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
			error(0,4);

		strcpy(s.name, t.value);

		// Terminal =
		t = deQueue(q);
		if (t.tokenType != eqlsym )
			error(0,0);

		// Terminal literal number
		t = deQueue(q);
		if (t.tokenType != numbersym )
			error(0,2);

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
		error(0,5);

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
			error(0,4);

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
		error(0,5);
	gen(6,0,i,stacky, code);
}

// fsys { const, var, procedure, begin, call, if, while, . }
void procDeclaration ( queue* q, hashTable* h, stack* stacky,instruction* code, setsym fsys) {

	while ( q->head->value.tokenType == procsym ) {
		token t;
		symbol s;
		setsym aux = copySet(&fsys);
		int temp = code->codeSize;
		gen(7,0,0, stacky,code);

		// Terminal Procedure
		t = deQueue(q);

		// Terminal Identifier
		t = deQueue(q);
		if ( t.tokenType != identsym )
			error(0,4);

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
			error(0,5);
		gen(6,0,4,stacky, code);
		addElement(semicolonsym, &fsys);
		block(q,copy, stacky,code, fsys);
		gen(2,0,0, stacky, code);

		if (!existElement(q->head->value.tokenType, *declbegsys)) {
			// Terminal Semicolon
			t = deQueue(q);
			if ( t.tokenType != semicolonsym )
				error(0,5);
			else {
				addElement(identsym, &aux);
				addElement(procsym, &aux);
				test(*statbegsys, aux, 6, q);
			}

		}

		actualLevel--;
		free(copy);
		code->mem[temp].m = code->codeSize;
	}

}

// fsys { const, var, procedure, begin, call, if, while, ., ; }
//if fsys { const, var, procedure, begin, call, if, else, while, ., ; }
void statement ( queue* q, hashTable* h, stack* stacky,instruction* code, setsym fsys) {
	token t;
	symbol* s;
	setsym aux = copySet(&fsys);
	// Terminal Identifier
	if ( q->head->value.tokenType == identsym ) {
		t = deQueue(q);

		//Checking if exist in the symbol table
		s = NULL;
		int i = actualLevel;
		while ( s == NULL && i != -1 )
			s = lookup(t.value,i--,h);

		if ( s == NULL )
			error(0,11);

		//Checking if it is a var 
		if (s->kind != 2) {
			printf("its me mario!\n");
			error(0,12);
		}

		// Terminal :=
		t = deQueue(q);
		if ( t.tokenType != becomessym )
			error(0,3);
		expression(q,h, stacky,code, fsys);
		//Generating Code
		gen(04,s->level,s->addr, stacky,code);

	} // Terminal Call
	else if ( q->head->value.tokenType == callsym ) {
		t = deQueue(q);

		// Terminal Identifier
		t = deQueue(q);
		if ( t.tokenType != identsym )
			error(0,14);
		s = NULL;
		int i = actualLevel;
		while ( s == NULL && i != -1 )
			s = lookup(t.value,i--,h);

		if ( s == NULL )
			error(0,11);

		if (s->kind != 3)
			error(0,26);

		gen(5,actualLevel - s->level, s->addr, stacky, code);


	} // Terminal if
	else if ( q->head->value.tokenType == ifsym ){
		int ctemp, ctemp1;
		t = deQueue(q);
		setsym testset = copySet(&fsys);
		addElement(thensym, &testset);
		condition(q,h, stacky,code, testset);

		// Terminal Then
		t = deQueue(q);
		if ( t.tokenType != thensym )
			error(0,16);

		ctemp = code->codeSize;
		gen(8,0,0, stacky,code);
		setsym testset1 = copySet(&fsys);
		addElement(elsesym, &testset1);
		statement(q,h, stacky,code, testset1);
		ctemp1 = code->codeSize;
		// Terminal Else
		if ( q->head->value.tokenType == elsesym ) {
			gen(7,0,0, stacky,code);
			code->mem[ctemp].m = code->codeSize;
			t = deQueue(q);
			statement(q,h, stacky,code, fsys);
			code->mem[ctemp1].m = code->codeSize;
		}
		else
			code->mem[ctemp].m = code->codeSize;
	} // Terminal While
	else if ( q->head->value.tokenType == whilesym ) {
		int cx1 = code->codeSize;
		int cx2;
		t = deQueue(q);
		setsym testset = copySet(&fsys);
		addElement(dosym,&testset);
		condition(q,h, stacky,code, testset);

		cx2 = code->codeSize;
		gen(8,0,0, stacky,code);
		// Terminal Do
		t = deQueue(q);
		if ( t.tokenType != dosym )
			error(0,18);

		statement(q,h, stacky,code, fsys);
		gen(7,0,cx1, stacky,code);
		code->mem[cx2].m = code->codeSize;
	} // Terminal Read
	else if ( q->head->value.tokenType == readsym ) {
		t = deQueue(q);

		// Terminal Identifier
		t = deQueue(q);
		if ( t.tokenType != identsym )
			error(0,29);
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
			error(0,29);

		s = NULL;
		int i = actualLevel;
		while ( s == NULL && i != -1 )
			s = lookup(t.value,i--,h);
		gen(9,0,0,stacky, code);
		gen(04,s->level,s->addr, stacky,code);

	} // Terminal Begin
	else if ( q->head->value.tokenType == beginsym ) {
		t = deQueue(q);
		addElement(semicolonsym, &fsys);
		addElement(endsym, &fsys);
		statement(q,h, stacky,code, fsys);
		setsym testset = copySet(statbegsys);
		addElement(semicolonsym, &testset);
		// Terminal Semicolon
		while ( existElement(q->head->value.tokenType, testset) ) {
			t = deQueue(q);
			if (t.tokenType != semicolonsym)
				error(0,10);
			statement(q,h, stacky,code, fsys);
		}

		// Terminal End
		t = deQueue(q);
		if ( t.tokenType != endsym )
			error(0,28);

	}
	setsym* testset = createSet(); 
	test(aux,*testset,19,q);
	free(testset);

}
// if fsys { const, var, procedure, begin, call, if, while, ., ;, then }
// while fsys { const, var, procedure, begin, call, if, while, ., ;, do }
void condition (queue *q, hashTable* h, stack* stacky,instruction* code, setsym fsys) {
	token t;
	// Terminal odd
	if ( q->head->value.tokenType == oddsym ) {
		t = deQueue(q);
		expression(q,h, stacky,code, fsys);
		gen(17,0,0, stacky,code);
	}
	else {
		setsym testset = copySet(&fsys);
		addElement(eqlsym,&fsys);
		addElement(neqsym, &fsys);
		addElement(lessym,&fsys);
		addElement(gtrsym,&fsys);
		addElement(leqsym, &fsys);
		addElement(geqsym, &fsys);
		expression(q,h, stacky,code, fsys);
		t = deQueue(q);
		if ( t.tokenType != eqlsym && t.tokenType != neqsym &&
			t.tokenType != lessym && t.tokenType != leqsym &&
			t.tokenType != gtrsym && t.tokenType != geqsym )
			error(0,30);

		expression(q,h, stacky,code, testset);

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

// Assigntment fsys { const, var, procedure, begin, call, if, while, ., ; }
// if condition fsys { const, var, procedure, begin, call, if, while, ., ;, then } + { <, >, <=, >=, !=, ==}
// while condition fsys { const, var, procedure, begin, call, if, while, ., ;, do } + { <, >, <=, >=, !=, ==}
void expression ( queue* q, hashTable* h, stack* stacky,instruction* code, setsym fsys) {
	token t;
	addElement(plussym, &fsys);
	addElement(minussym, &fsys);
	// Terminal + or -
	if ( q->head->value.tokenType == plussym || q->head->value.tokenType == minussym) {
		t = deQueue(q);
		term(q,h, stacky,code, fsys);

		// Generating Code for NEG operation
		if (t.tokenType == minussym)
			gen(12,0,0, stacky,code); 
	}

	else 
		term(q,h, stacky,code, fsys); 
	// Terminal + or -
	while ( q->head->value.tokenType == plussym || q->head->value.tokenType == minussym) {
		t = deQueue(q);
		term(q,h, stacky,code, fsys);
		// Generating Code for ADD operation
		if (t.tokenType == plussym)
			gen(13,0,0, stacky,code);
		// Generating Code for SUB operation
		else 
			gen(14,0,0, stacky,code);
	}
}


// Assigntment fsys { const, var, procedure, begin, call, if, while, ., ; } + { +, -}
// if condition fsys { const, var, procedure, begin, call, if, while, ., ;, then } + { <, >, <=, >=, !=, ==} + {+, -}
// while condition fsys { const, var, procedure, begin, call, if, while, ., ;, do } + { <, >, <=, >=, !=, ==} + {+, -}
void term ( queue* q, hashTable* h, stack* stacky,instruction* code, setsym fsys) {
	token t;
	addElement(multsym, &fsys);
	addElement(slashsym, &fsys);
	factor(q,h, stacky,code, fsys);
	// Terminal * or /
	while ( q->head->value.tokenType == multsym || q->head->value.tokenType == slashsym ) {
		t = deQueue(q);
		factor(q,h, stacky,code, fsys);
		if (t.tokenType == multsym)
			gen(15,0,0, stacky,code);
		else
			gen(16,0,0, stacky,code);
	}
}
// Assigntment fsys { const, var, procedure, begin, call, if, while, ., ; } + { +, -} + {*, /}
// if condition fsys { const, var, procedure, begin, call, if, while, ., ;, then } + { <, >, <=, >=, !=, ==} + {+, -} + {*, /}
// while condition fsys { const, var, procedure, begin, call, if, while, ., ;, do } + { <, >, <=, >=, !=, ==} + {+, -} + {*, /}
void factor (queue* q, hashTable* h, stack* stacky,instruction* code, setsym fsys) {
	token t;
	symbol* s;
	setsym testset = copySet(&fsys);
	test(*facbegsys,fsys, 24, q);
	while(existElement(q->head->value.tokenType, *facbegsys)) {
		// Identifier
		if (q->head->value.tokenType == identsym ) {
			t = deQueue(q);
			s = NULL;
			int i = actualLevel;
			while ( s == NULL && i != -1 )
				s = lookup(t.value,i--,h);

			if ( s == NULL )
				exit(11);
			if (s->kind == 2)
				gen(03,s->level,s->addr, stacky,code);
			else if (s->kind == 1)
				gen(01, 0,s->val, stacky,code);
			else 
				error(0,12);
		}
		// Terminal Number
		else if (q->head->value.tokenType == numbersym ) {
			t = deQueue(q);
			gen(1, 0,atoi(t.value), stacky,code);
		}
		// Terminal (
		else if (q->head->value.tokenType == lparentsym ) {
			t = deQueue(q);
			addElement(rparentsym, &fsys);
			expression(q,h, stacky,code, fsys);

			//Terminal )
			t = deQueue(q);
			if (t.tokenType != rparentsym)
				error(0,31);
		}

		setsym *aux = createSet();
		addElement(lparentsym, aux);
		test(testset, *aux, 23, q);
		free(aux);
	}

}


void error ( int recovery, int number ) {
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
	if (!recovery)
		exit(EXIT_FAILURE);
}

void test (setsym s1, setsym s2, int n, queue* q) {
	if ( existElement(q->head->value.tokenType, s1) != 1 ) {
		error(1,n);
		setsym s3 = mergeSet(s1,s2);
		while ( existElement(q->head->value.tokenType, s3) != 1) {
			printf("Ignoring tokens: %s --Error Recovery\n", q->head->value.value);
			deQueue(q);
		}
	}
}


