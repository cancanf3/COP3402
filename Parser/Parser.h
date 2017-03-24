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
#include "../Auxiliar Structures/HashTable.h"
#include "../Code Generator/CodeGenerator.h"


void program ( queue* q, hashTable* h, stack* stacky,instruction* code);
void block ( queue* q, hashTable* h, stack* stacky,instruction* code);
void constDeclaration ( queue* q, hashTable* h, stack* stacky,instruction* code);
void varDeclaration ( queue* q, hashTable* h, int* addressPosition, stack* stacky,instruction* code);
void procDeclaration ( queue* q, hashTable* h, stack* stacky,instruction* code);
void statement ( queue* q, hashTable* h, stack* stacky,instruction* code);
void condition (queue *q, hashTable* h, stack* stacky,instruction* code);
void expression ( queue* q, hashTable* h, stack* stacky,instruction* code);
void term ( queue* q, hashTable* h, stack* stacky,instruction* code);
void factor (queue* q, hashTable* h, stack* stacky,instruction* code);
void error ( int number );

#endif  