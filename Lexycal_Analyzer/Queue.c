/* Author: Jose Pena
 * UCFID: 4142431
 * Tittle: Auxiliar structure Queue
 * Class: COP3402
 */

#include "Queue.h" 


// Function to add to the stack
queue* addQueue ( token value, queue *q ) {

	node* newToken = NULL;
	newToken = (node *) malloc(sizeof(node));
	newToken->value = value;
	newToken->next = NULL;

	if ( q->head == NULL ) {
		q->head = newToken;
		q->tail = newToken;
	}
	else {
		q->tail->next = newToken;
		q->tail = newToken;
	}

	return q;
}

// Function to pop from the stack will be develop in parser