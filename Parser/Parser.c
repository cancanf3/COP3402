/* Author: Jose Pena
 * UCFID: 4142431
 * Tittle: Parser
 * Class: COP3402
 */


#include "Parser.h"

void program ( queue* q ) {
	printf("entra program:\n");
	block(q);
	// Terminal Period
	token t = deQueue(q);
	if ( t.tokenType !=  periodsym)
		error(9);
}

void block ( queue* q ) {
	printf("entra block:\n");
	constDeclaration(q);
	varDeclaration(q);
	procDeclaration(q);

	statement(q);
}

void constDeclaration ( queue* q ) {
	printf("entra const:\n");
	token t;
	if ( q->head->value.tokenType != constsym)
		return;

	do {

		// Terminal const or Comma
		t = deQueue(q);

		// Terminal Identifier
		t = deQueue(q);
		if ( t.tokenType != identsym )
			error(4);

		// Terminal =
		t = deQueue(q);
		if (t.tokenType != eqlsym )
			error(0);

		// Terminal literal number
		t = deQueue(q);
		if (t.tokenType != numbersym )
			error(2);
	} while ( q->head->value.tokenType == commasym );

	// Terminal Semicolon
	t = deQueue(q);
	if ( t.tokenType != semicolonsym )
		error(5);

}

void varDeclaration ( queue* q ) {
	printf("entra var:\n");
	token t;
	if ( q->head->value.tokenType != varsym )
		return;

	do {

		// Terminal var or Comma
		t = deQueue(q);

		// Terminal Identifier
		t = deQueue(q);
		if ( t.tokenType != identsym )
			error(4);

	} while ( q->head->value.tokenType == commasym );

	// Terminal Semicolon
	t = deQueue(q);
	if ( t.tokenType != semicolonsym )
		error(5);
}

void procDeclaration ( queue* q ) {
	printf("entra procedure:\n");
	
	if ( q->head->value.tokenType == procsym ) {

			// Terminal Procedure
			token t = deQueue(q);

			// Terminal Identifier
			t = deQueue(q);
			if ( t.tokenType != identsym )
				error(4);

			// Terminal Semicolon
			t = deQueue(q);
			if ( t.tokenType != semicolonsym )
				error(5);

			block(q);

			// Terminal Semicolon
			t = deQueue(q);
			if ( t.tokenType != semicolonsym )
				error(5);

			procDeclaration(q);
	}
	statement(q);


}

void statement ( queue* q) {
	printf("entra statement:\n");
	token t;
	// Terminal Identifier
	if ( q->head->value.tokenType == identsym ) {
		t = deQueue(q);

		// Terminal :=
		t = deQueue(q);
		if ( t.tokenType != becomessym )
			error(3);

		expression(q);

	} // Terminal Call
	else if ( q->head->value.tokenType == callsym ) {
		t = deQueue(q);

		// Terminal Identifier
		t = deQueue(q);
		if ( t.tokenType != identsym )
			error(14);


	} // Terminal if
	else if ( q->head->value.tokenType == ifsym ){
		t = deQueue(q);

		condition(q);

		// Terminal Then
		t = deQueue(q);
		if ( t.tokenType != thensym )
			error(16);

		statement(q);

		// Terminal Else
		if ( q->head->value.tokenType == elsesym ) {
			t = deQueue(q);

			statement(q);
		}
	} // Terminal While
	else if ( q->head->value.tokenType == whilesym ) {
		t = deQueue(q);

		condition(q);

		// Terminal Do
		t = deQueue(q);
		if ( t.tokenType != dosym )
			error(18);

		statement(q);
	} // Terminal Read
	else if ( q->head->value.tokenType == readsym ) {
		t = deQueue(q);

		// Terminal Identifier
		t = deQueue(q);
		if ( t.tokenType != identsym )
			error(29);


	} // Terminal Write
	else if ( q->head->value.tokenType == writesym ) {
		t = deQueue(q);

		// Terminal Identifier
		t = deQueue(q);
		if ( t.tokenType != identsym )
			error(29);

	} // Terminal Begin
	else if ( q->head->value.tokenType == beginsym ) {
		t = deQueue(q);

		statement(q);

		// Terminal Semicolon
		while ( q->head->value.tokenType == semicolonsym ) {
			t = deQueue(q);
			statement(q);
		}

		// Terminal End
		t = deQueue(q);
		if ( t.tokenType != endsym )
			error(28);

	}

}

void condition (queue *q) {
	printf("entra condition:\n");

	token t;

	// Terminal odd
	if ( q->head->value.tokenType == oddsym ) {
		t = deQueue(q);
		expression(q);
	}
	else {
		expression(q);
		relOp(q);
		expression(q);
	}
}

void relOp( queue *q ) {
	printf(" entra relOp:\n");
	token t = deQueue(q);
	if ( t.tokenType != eqlsym && t.tokenType != neqsym &&
		t.tokenType != lessym && t.tokenType != leqsym &&
		t.tokenType != gtrsym && t.tokenType != geqsym )
		error(30);
}

void expression ( queue* q ) {
	printf("entra expression:\n");
	token t;
	// Terminal + or -
	if ( q->head->value.tokenType == plussym || q->head->value.tokenType == minussym) {
		t = deQueue(q);
	}
	term(q); 
	// Terminal + or -
	while ( q->head->value.tokenType == plussym || q->head->value.tokenType == minussym) {
		t = deQueue(q);
		term(q);
	}
}

void term ( queue* q ) {
	printf(" entra term:\n");
	token t;
	factor(q);
	// Terminal * or /
	while ( q->head->value.tokenType == multsym || q->head->value.tokenType == slashsym ) {
		t = deQueue(q);
		factor(q);
	}
}

void factor (queue* q) {
	printf(" entra factor:\n");
	token t;
	// Identifier
	if (q->head->value.tokenType == identsym )
		t = deQueue(q);
	// Terminal Number
	else if (q->head->value.tokenType == numbersym )
		t = deQueue(q);
	// Terminal (
	else if (q->head->value.tokenType == lparentsym ) {
		t = deQueue(q);

		expression(q);

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