/* Author: Jose Pena
 * UCFID: 4142431
 * Tittle: Stack header
 * Class: COP3402
 */

#ifndef STACK
#define STACK


#include <stdlib.h>
#include <stdio.h>

typedef struct nodeS {
	int value;
	struct nodeS* next;
} nodeS;


typedef struct stack {
	nodeS* head;
	int size;
} stack;

stack* createStack();
void pushStack( int r, stack* s );
int popStack(stack* s);



#endif