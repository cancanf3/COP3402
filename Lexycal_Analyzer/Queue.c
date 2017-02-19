/* Author: Jose Pena
 * UCFID: 4142431
 * Tittle: Auxiliar structure Queue
 * Class: COP3402
 */

#include "Queue.h" 

// Function to initialize the node
void initQueue (node *head) {
	head = NULL;
}

// Function to add to the stack
node* addQueue ( token value, node *head ) {
	node* newToken = NULL;
	newToken = (node *) malloc(sizeof(node));

	newToken->next = head;
	newToken->value = value;
	head = newToken;

	return head;
}

// Function to pop from the stack
token popQueue ( node* head ) {
	token result = head->value;
	node* trash = head;
	head = head->next;
	free(trash);
	return result;
}