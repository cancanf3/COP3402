/* Author: Jose Pena
 * UCFID: 4142431
 * Tittle: Parser header
 * Class: COP3402
 */



#ifndef PARSER
#define PARSER

#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include "../Auxiliar Structures/Queue.h"

void program ( queue* q );
void block ( queue* q );
void constDeclaration ( queue* q );
void varDeclaration ( queue* q );
void procDeclaration ( queue* q );
void statement ( queue* q);
void condition (queue *q);
void relOp( queue *q );
void expression ( queue* q );
void term ( queue* q );
void factor (queue* q);
void error ( int number );

#endif  