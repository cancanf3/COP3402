/* Author: Jose Pena
 * UCFID: 4142431
 * Tittle: Compiler Driver
 * Class: COP3402
 */
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include "./Lexical Analyzer/LexicalAnalyzer.h"
#include "./Parser/Parser.h"

int main (int argc, char* argv[]) {

	queue* tokens;
	int lFlag = 0;
	int aFlag = 0;
	int vFlag = 0;
	int opt;

	// Parsing the the flags
	while (( opt = getopt(argc, argv, "lav")) != -1) {
		switch (opt) {
			case 'l':
				lFlag = 1;
				break;
			case 'a':
				aFlag = 1;
				break;
			case 'v':
				vFlag = 1;
				break;
			default: 
				printf("Usage: %s [-l Tokens] [-a Assembly Code] [-v stack & cpu trace] \n", argv[0]);
				exit(EXIT_FAILURE);

		}
	}


	tokens = LexicalAnalyzer(lFlag);
	if (tokens == NULL) {
		printf("Error in the Lexer\n");
		return 1;
	}

	program(tokens);

	// Freeing the Queue
	node* aux = tokens->head;
	while (aux != NULL) {
		node* freedom = aux;
		aux = aux->next;
		free(freedom);
	}
	free(tokens);


}