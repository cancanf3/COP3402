/* Author: Jose Pena
 * UCFID: 4142431
 * Tittle: Stack
 * Class: COP3402
 */

#include "Stack.h"

// Return a Stack pointer from the Heap
stack* createStack() {
	stack* s = (stack*)malloc(sizeof(stack));
	s->head = NULL;
	s->size = 0;
	return s;
}

// Insert an integer in the stack
void pushStack( int r, stack* s ) {

	nodeS* new = (nodeS*)malloc(sizeof(nodeS));
	new->value = r;
	new->next = s->head;
	s->head = new;
	s->size++;
}

// Remove and retrieve an integer from the stack
int popStack(stack* s) {
	int result = s->head->value;
	nodeS* butterfly = s->head;
	s->head = s->head->next;
	free(butterfly);
	s->size--;
	return result;
}