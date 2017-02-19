/* Author: Jose Pena
 * UCFID: 4142431
 * Tittle: Queue header (Lexer)
 * Class: COP3402
 */


#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>


#ifndef TEST_H
#define TEST_H

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

typedef struct {
	int kind;
	char name[10]; int val;
	int level;
	int addr;
} symbol;

typedef struct node {
	token value;
	struct node* next;
} node;

void initQueue (node *head);
node* addQueue ( token value, node *head );
token popQueue ( node* head );

#endif



