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
#include "../Auxiliar Structures/Set.h"
#include "../Code Generator/CodeGenerator.h"


void program ( queue* q, stack* stacky,instruction* code);
void block ( queue* q, hashTable* h, stack* stacky,instruction* code, setsym fsys);
void constDeclaration ( queue* q, hashTable* h, stack* stacky,instruction* code);
void varDeclaration ( queue* q, hashTable* h, int* addressPosition, stack* stacky,instruction* code);
void procDeclaration ( queue* q, hashTable* h, stack* stacky,instruction* code, setsym fsys);
void statement ( queue* q, hashTable* h, stack* stacky,instruction* code, setsym fsys);
void condition (queue *q, hashTable* h, stack* stacky,instruction* code, setsym fsys);
void expression ( queue* q, hashTable* h, stack* stacky,instruction* code, setsym fsys);
void term ( queue* q, hashTable* h, stack* stacky,instruction* code, setsym fsys);
void factor (queue* q, hashTable* h, stack* stacky,instruction* code, setsym fsys);
void error ( int recovery, int number );
void test (setsym s1, setsym s2, int n, queue* q);


#endif  