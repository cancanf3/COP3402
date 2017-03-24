/* Author: Jose Pena
 * UCFID: 4142431
 * Tittle: Symbol Table (Hash Table)
 * Class: COP3402
 */

#include "HashTable.h"

// Create a HashTable of size SIZE 
hashTable* createHashTable () {
	int i;
	hashTable *hashy = (hashTable *) malloc(sizeof(hashTable)*SIZE);
	for (i = 0; i < SIZE ; i++){
		*(hashy[i].name) = '\0';
	} 
	return hashy;
}

int toInt ( char *number ) {
	int result = 0; 
	int i;
	int size = 0;
	for ( i = 0 ; i < 6 ; i ++ )
		if (number[i] != '\0')
			size++;


	for ( i = 0; i < size; i++ )
		if ( i == 0 )
			result += number[size-1]-48;
		else 
			result += (number[size-i-1]-48)*(10*i);

	printf("toInt: %d\n", result);
	return result;

}

void destroyHashTable ( hashTable* hashy ) {
	free(hashy);
}


// Generates a Hash Code to look up in the Hash Table
int hashFunction ( char* identifier ) {
	int hashCode = 7;
	int i;

	while (*identifier) {
		hashCode = hashCode * 31 + *identifier;
		identifier++;
	}

	return hashCode;
}

// Lookup in the Hash Table. I probably have to create another input to specify the lvl of the program
symbol* lookup ( char* identifier,int level, hashTable* hashy ) {

	int hashCode = hashFunction(identifier);
	if ( strcmp( hashy[hashCode%SIZE].name, identifier ) == 0 && hashy[hashCode%SIZE].level == level )
		return &hashy[hashCode%SIZE];
	else {
		while( *(hashy[(++hashCode)%SIZE].name) != '\0' ) {
			if ( strcmp( hashy[hashCode%SIZE].name, identifier ) == 0 && hashy[hashCode%SIZE].level == level )
				return &hashy[hashCode%SIZE];
		}
		return NULL;
	}

}

// insert in the Hash Table
void insert ( symbol s , hashTable* hashy ) {
	int i = 0;
	int hashCode = hashFunction(s.name);
	if ( *(hashy[hashCode%SIZE].name) == '\0' && *(hashy[hashCode%SIZE].name) != '\a') {
		hashy[hashCode%SIZE].kind = s.kind;
		strcpy(hashy[hashCode%SIZE].name, s.name);
		hashy[hashCode%SIZE].val = s.val;
		hashy[hashCode%SIZE].level = s.level;
		hashy[hashCode%SIZE].addr = s.addr;
	}
	else {
		while( *(hashy[hashCode%SIZE].name) != '\0' && *(hashy[hashCode%SIZE].name) != '\a') {
			++hashCode;
			++i;
			if (i == SIZE) {
				printf("Symbol Table Full\n");
				return;
			}
		}
		hashy[hashCode%SIZE].kind = s.kind;
		strcpy(hashy[hashCode%SIZE].name, s.name);
		hashy[hashCode%SIZE].val = s.val;
		hashy[hashCode%SIZE].level = s.level;
		hashy[hashCode%SIZE].addr = s.addr;
	}

}


// Return and Delete the symbol from the table
symbol* pop ( char* identifier,int level, hashTable* hashy ) {

	char hack[10] = "\a";
	int hashCode = hashFunction(identifier);

	if ( strcmp( hashy[hashCode%SIZE].name, identifier ) == 0 && hashy[hashCode%SIZE].level == level ) {
		strcpy(hack,hashy[hashCode%SIZE].name);
		return &hashy[hashCode%SIZE];
	}
	else {
		while( *(hashy[(++hashCode)%SIZE].name) != '\0' ) {
			if ( strcmp( hashy[hashCode%SIZE].name, identifier ) == 0 && hashy[hashCode%SIZE].level == level ) {
				strcpy(hack,hashy[hashCode%SIZE].name);
				return &hashy[hashCode%SIZE];
			}
		}
		return NULL;
	}

}