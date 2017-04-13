/* Author: Jose Pena
 * UCFID: 4142431
 * Tittle: Auxiliar structure Queue
 * Class: COP3402
 */

#include "Queue.h" 


// Function to add to the queue
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

// Function to DeQueue from the queue
token deQueue ( queue* q ) {
	if (q->head == NULL) {
		printf("Queue Empty\n");
		exit(EXIT_FAILURE);
	}

	token result = q->head->value;
	node* freeButterfly = q->head;
	q->head = q->head->next;
	free(freeButterfly);
	//printf("Dtoken: %s\n", result.value);
	return result;

}