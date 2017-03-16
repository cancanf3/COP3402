#ifndef HASHTABLE
#define HASHTABLE
#define SIZE 10000;

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

typedef struct { 
	int kind; 		// const = 1, var = 2, proc = 3
	char name[10];	// name up to 11 chars
	int val; 		// number (ASCII value) 
	int level; 		// L level
	int addr; 		// M address
} symbol, hashTable; 

hashTable* createHashTable ();
int hashFunction ( char* identifier );
symbol* lookup ( char* identifier,int level , hashTable* hashy );
void insert ( symbol s , hashTable* hashy );
symbol* pop ( char* identifier,int level, hashTable* hashy );

#endif