/* Author: Jose Pena
 * UCFID: 4142431
 * Tittle: Queue header
 * Class: COP3402
 */

#ifndef QUEUE
#define QUEUE

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

typedef enum { 
	nulsym = 1, identsym, numbersym, plussym, minussym,
	multsym, slashsym, oddsym, eqlsym, neqsym, lessym, 
	leqsym, gtrsym, geqsym, lparentsym, rparentsym, 
	commasym, semicolonsym, periodsym, becomessym, 
	beginsym, endsym, ifsym, thensym, whilesym, dosym, 
	callsym, constsym, varsym, procsym, writesym, 
	readsym , elsesym 
} token_type;

typedef struct {
	char value[12];
	char tokenNum[2];
	token_type tokenType;

} token;


typedef struct node {
	token value;
	struct node* next;
} node;

typedef struct queue {
	node* head;
	node* tail;
	
} queue;

queue* addQueue ( token value, queue *q );
token deQueue ( queue* q );

#endif



