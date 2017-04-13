/* Author: Jose Pena
 * UCFID: 4142431
 * Tittle: Set header
 * Class: COP3402
 */

#ifndef SET
#define SET

#include "Queue.h"

typedef struct {
	token_type set[32];
	int size;
} setsym;

setsym* createSet();
setsym copySet( setsym* s);
void addElement ( token_type t, setsym* s);
int existElement ( token_type t, setsym s);
token_type extractElement ( token_type t, setsym* s);
setsym mergeSet (setsym s1, setsym s2);

#endif