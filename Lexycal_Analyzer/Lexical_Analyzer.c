/* Author: Jose Pena
 * UCFID: 4142431
 * Tittle: Lexical Analyzer (Lexer)
 * Class: COP3402
 */

#include "Queue.h"



void clean_buffer (char* word);
void outputTable (queue* lexeme_list);
void outputList (queue* lexeme_list);
int issymbol (char letter);

int main () {

	queue* lexeme_list = (queue *)malloc(sizeof(queue));
	lexeme_list->head = NULL;
	lexeme_list->tail = NULL;
	char lector;
	char word[11];
	int counter;
	FILE *code;



	// Open the file
	char name[100];
	printf("select the input file: ");
	scanf("%s", name);
	code = fopen(name, "r");

	// Avoiding previous trash in memory
	clean_buffer(word);

	while (fscanf(code, "%c", &lector) != EOF ) {	
			
		counter = 0;
		// Ignoring Charaters 
		if (lector == 10 || lector == 32 || lector == 9)
			continue;


		// Identifier or Keywords
		if (isalpha(lector)) {
			int isKeyword = 1;

			while (isalpha(lector) || isdigit(lector)) {
				if (isdigit(lector))
					isKeyword = 0;

				word[counter] = lector;
				counter++;

				if (counter > 11) {
					printf("Exceed identifier name size limit\n");
					return 1;
				}

				fscanf(code, "%c", &lector);
				if (lector == 10 || lector == 32 || lector == 9)
					break;


			}

			// retract from the lookahead
			fseek(code, -1, SEEK_CUR);

			// if identifier, avoid checking innecesary keywords
			if (!isKeyword) {
				isKeyword = counter;
				counter = 12;

			}
			switch (counter) {
				case 2:
					// if, do
					if (strcmp(word, "if") == 0) {
						token keyword;
						keyword.tokenNum[0] = '2';
						keyword.tokenNum[1] = '3';
						keyword.tokenType = ifsym;
						strcpy(keyword.value, word);
						lexeme_list = addQueue(keyword,lexeme_list);
					}
					else if (strcmp(word, "do") == 0) {
						token keyword;
						keyword.tokenNum[0] = '2';
						keyword.tokenNum[1] = '6';
						keyword.tokenType = dosym;
						strcpy(keyword.value, word);
						lexeme_list = addQueue(keyword,lexeme_list);
					}
					else
						goto IDE;
					break;

				case 3:
					// var, end, odd
					if (strcmp(word, "var") == 0) {
						token keyword;
						keyword.tokenNum[0] = '2';
						keyword.tokenNum[1] = '9';
						keyword.tokenType = varsym;
						strcpy(keyword.value, word);
						lexeme_list = addQueue(keyword, lexeme_list);
						
					}
					else if (strcmp(word, "end") == 0) {
						token keyword;
						keyword.tokenNum[0] = '2';
						keyword.tokenNum[1] = '2';
						keyword.tokenType = endsym;
						strcpy(keyword.value, word);
						lexeme_list = addQueue(keyword,lexeme_list);

					}
					else if (strcmp(word, "odd") == 0) {
						token condition;
						condition.tokenNum[0] = '8';
						condition.tokenNum[1] = '\0';
						condition.tokenType = oddsym;
						strcpy(condition.value, word);
						lexeme_list = addQueue(condition,lexeme_list);
					}
					else
						goto IDE;
					break;

				case 4:
					// call, then, else, read, null
					if (strcmp(word, "call") == 0) {
						token keyword;
						keyword.tokenNum[0] = '2';
						keyword.tokenNum[1] = '7';
						keyword.tokenType = callsym;
						strcpy(keyword.value, word);
						lexeme_list = addQueue(keyword,lexeme_list);
					}
					else if (strcmp(word, "then") == 0) {
						token keyword;
						keyword.tokenNum[0] = '2';
						keyword.tokenNum[1] = '4';
						keyword.tokenType = thensym;
						strcpy(keyword.value, word);
						lexeme_list = addQueue(keyword,lexeme_list);
					}
					else if (strcmp(word, "else") == 0) {
						token keyword;
						keyword.tokenNum[0] = '3';
						keyword.tokenNum[1] = '3';
						keyword.tokenType = elsesym;
						strcpy(keyword.value, word);
						lexeme_list = addQueue(keyword,lexeme_list);
					}
					else if (strcmp(word, "read") == 0) {
						token keyword;
						keyword.tokenNum[0] = '3';
						keyword.tokenNum[1] = '2';
						keyword.tokenType = readsym;
						strcpy(keyword.value, word);
						lexeme_list = addQueue(keyword,lexeme_list);
					}
					else if (strcmp(word, "null") == 0) {
						token keyword;
						keyword.tokenNum[0] = '1';
						keyword.tokenNum[1] = '\0';
						keyword.tokenType = nulsym;
						strcpy(keyword.value, word);
						lexeme_list = addQueue(keyword,lexeme_list);
					}
					else
						goto IDE;
					break;

				case 5:
					// const, begin, while, write
					if (strcmp(word, "const") == 0) {
						token keyword;
						keyword.tokenNum[0] = '2';
						keyword.tokenNum[1] = '8';
						keyword.tokenType = constsym;
						strcpy(keyword.value, word);
						lexeme_list = addQueue(keyword,lexeme_list);
					}
					else if (strcmp(word, "begin") == 0) {
						token keyword;
						keyword.tokenNum[0] = '2';
						keyword.tokenNum[1] = '1';
						keyword.tokenType = beginsym;
						strcpy(keyword.value, word);
						lexeme_list = addQueue(keyword,lexeme_list);
					}
					else if (strcmp(word, "while") == 0) {
						token keyword;
						keyword.tokenNum[0] = '2';
						keyword.tokenNum[1] = '5';
						keyword.tokenType = whilesym;
						strcpy(keyword.value, word);
						lexeme_list = addQueue(keyword,lexeme_list);
					}
					else if (strcmp(word, "write") == 0) {
						token keyword;
						keyword.tokenNum[0] = '3';
						keyword.tokenNum[1] = '1';
						keyword.tokenType = writesym;
						strcpy(keyword.value, word);
						lexeme_list = addQueue(keyword,lexeme_list);
					}
					else
						goto IDE;
					break;

				case 9:
					// procedure
					if (strcmp(word, "procedure") == 0) {
						token keyword;
						keyword.tokenNum[0] = '3';
						keyword.tokenNum[0] = '0';
						keyword.tokenType = procsym;
						strcpy(keyword.value, word);
						lexeme_list = addQueue(keyword,lexeme_list);
					}
					else
						goto IDE;
					break;

				IDE:default:
					// identifier
					if (counter == 12)
						counter = isKeyword;

					token identifier;
					strcpy(identifier.value, word);
					identifier.tokenNum[0] = '2';
					identifier.tokenNum[1] = '\0';
					identifier.tokenType = identsym;
					lexeme_list = addQueue(identifier,lexeme_list);
					break;
			}


		}
		// Numbers
		else if (isdigit(lector)) {
			while (isdigit(lector)) {
				word[counter] = lector;
				counter++;

				if (counter > 5) {
					printf("Exceed number size limit\n");
					return 1;
				}

				fscanf(code, "%c", &lector);
				if (lector == 10 || lector == 32 || lector == 9)
					break;
			}
			// retract from the lookahead
			fseek(code, -1, SEEK_CUR);

			token digit;
			strcpy(digit.value, word);
			digit.tokenNum[0] = '3';
			digit.tokenNum[1] = '\0';
			digit.tokenType = numbersym;
			lexeme_list = addQueue(digit,lexeme_list);
		}
		// Comments
		else if (lector == '/') {
			word[counter] = lector;
			counter++;
			fscanf(code, "%c", &lector);
			if (lector != '*') {
				token symbol;
				strcpy(symbol.value, word);
				symbol.tokenNum[0] = '7';
				symbol.tokenNum[1] = '\0';
				symbol.tokenType = slashsym;
				lexeme_list = addQueue(symbol,lexeme_list);
				// retract from the lookahead
				fseek(code, -1, SEEK_CUR);
			}
			else {
				int leaving = 0;
				while (1) {
					fscanf(code, "%c", &lector);
					if (lector == '/' && leaving)
						break;

					if (lector == '*')
						leaving = 1;
					else
						leaving = 0;
				}
			}
		}
		// Symbols
		else if (issymbol(lector)) {
			word[counter] = lector;
			counter++;

			// Especial case of symbol of size 2
			if (lector == ':') {
				fscanf(code, "%c", &lector);
				if (lector != '=') {
					printf("Unkown Symbol \n");
					return 1;
				}
				word[counter] = lector;
				counter++;
			}
			else if (lector == '<' || lector == '>'){
				fscanf(code, "%c", &lector);
				if (lector == '=') {
					word[counter] = lector;
					counter++;
					
				}
				else if (word[0] == '<' && lector == '>') {
					word[counter] = lector;
					counter++;
				}
				else {
					fseek(code, -1, SEEK_CUR);
				}
			}

			switch (counter) {
				case 1:
					if (word[0] == '+') {
						token symbol;
						strcpy(symbol.value, word);
						symbol.tokenNum[0] = '4';
						symbol.tokenNum[1] = '\0';
						symbol.tokenType = plussym;
						lexeme_list = addQueue(symbol,lexeme_list);
					}
					else if (word[0] == '-') {
						token symbol;
						strcpy(symbol.value, word);
						symbol.tokenNum[0] = '5';
						symbol.tokenNum[1] = '\0';
						symbol.tokenType = minussym;
						lexeme_list = addQueue(symbol,lexeme_list);
					}
					else if (word[0] == '*'){
						token symbol;
						strcpy(symbol.value, word);
						symbol.tokenNum[0] = '6';
						symbol.tokenNum[1] = '\0';
						symbol.tokenType = multsym;
						lexeme_list = addQueue(symbol,lexeme_list);
					}
					else if (word[0] == '(') {
						token symbol;
						strcpy(symbol.value, word);
						symbol.tokenNum[0] = '1';
						symbol.tokenNum[1] = '5';
						symbol.tokenType = lparentsym;
						lexeme_list = addQueue(symbol,lexeme_list);
					}
					else if (word[0] == ')') {
						token symbol;
						strcpy(symbol.value, word);
						symbol.tokenNum[0] = '1';
						symbol.tokenNum[1] = '6';
						symbol.tokenType = rparentsym;
						lexeme_list = addQueue(symbol,lexeme_list);
					}
					else if (word[0] == '=') {
						token symbol;
						strcpy(symbol.value, word);
						symbol.tokenNum[0] = '9';
						symbol.tokenNum[1] = '\0';
						symbol.tokenType = eqlsym;
						lexeme_list = addQueue(symbol,lexeme_list);
					}
					else if (word[0] == ',') {
						token symbol;
						strcpy(symbol.value, word);
						symbol.tokenNum[0] = '1';
						symbol.tokenNum[1] = '7';
						symbol.tokenType = commasym;
						lexeme_list = addQueue(symbol,lexeme_list);
					}
					else if (word[0] == ';') {
						token symbol;
						strcpy(symbol.value, word);
						symbol.tokenNum[0] = '1';
						symbol.tokenNum[1] = '8';
						symbol.tokenType = semicolonsym;
						lexeme_list = addQueue(symbol,lexeme_list);
					}
					else if (word[0] == '.') {
						token symbol;
						strcpy(symbol.value, word);
						symbol.tokenNum[0] = '1';
						symbol.tokenNum[1] = '9';
						symbol.tokenType = periodsym;
						lexeme_list = addQueue(symbol,lexeme_list);
					}
					else if (word[0] == '<') {
						token symbol;
						strcpy(symbol.value, word);
						symbol.tokenNum[0] = '1';
						symbol.tokenNum[1] = '1';
						symbol.tokenType = lessym;
						lexeme_list = addQueue(symbol,lexeme_list);
					}
					else if (word[0] == '>') {
						token symbol;
						strcpy(symbol.value, word);
						symbol.tokenNum[0] = '1';
						symbol.tokenNum[1] = '3';
						symbol.tokenType = gtrsym;
						lexeme_list = addQueue(symbol,lexeme_list);
					}
					break;

				case 2:
					if (strcmp(word, ":=") == 0) {
						token symbol;
						strcpy(symbol.value, word);
						symbol.tokenNum[0] = '2';
						symbol.tokenNum[1] = '0';
						symbol.tokenType = becomessym;
						lexeme_list = addQueue(symbol,lexeme_list);
					} 
					else if (strcmp(word, "<=") == 0) {
						token symbol;
						strcpy(symbol.value, word);
						symbol.tokenNum[0] = '1';
						symbol.tokenNum[1] = '2';
						symbol.tokenType = leqsym;
						lexeme_list = addQueue(symbol,lexeme_list);
					}
					else if (strcmp(word, ">=") == 0) {
						token symbol;
						strcpy(symbol.value, word);
						symbol.tokenNum[0] = '1';
						symbol.tokenNum[1] = '4';
						symbol.tokenType = geqsym;
						lexeme_list = addQueue(symbol,lexeme_list);
					}
					else if (strcmp(word, "<>") == 0) {
						token symbol;
						strcpy(symbol.value, word);
						symbol.tokenNum[0] = '1';
						symbol.tokenNum[1] = '0';
						symbol.tokenType = neqsym;
						lexeme_list = addQueue(symbol,lexeme_list);

					}

			}



		}
		// Unkown Characters
		else {
			printf("Unkown Character\n");
			return 1;
		}


		// Cleaning Buffer;
		clean_buffer(word);

	}
	fclose(code);
	// Printing the Table
	outputTable(lexeme_list);

	// Printing the List
	outputList(lexeme_list);

	// Freeing the Queue
	node* aux = lexeme_list->head;
	while (aux != NULL) {
		node* freedom = aux;
		aux = aux->next;
		free(freedom);
	}
	free(lexeme_list);
	return 0;

}

void outputTable (queue* lexeme_list) {
	node* aux = lexeme_list->head;
	printf("\nLexeme Table: \n");
	printf("Lexeme\t\t\tToken Type\n");
	while (aux != NULL) {
		printf("%s\t\t\t%c%c\n", aux->value.value, aux->value.tokenNum[0], aux->value.tokenNum[1]);
		aux = aux->next;
	}
}

void outputList (queue* lexeme_list) {
	node* aux = lexeme_list->head;
	printf("\nLexeme List: \n");
	while (aux != NULL) {
		if ((aux->value.tokenNum[0] == '2' || aux->value.tokenNum[0] == '3') && aux->value.tokenNum[1] == '\0')
			printf(" %c%c %s ", aux->value.tokenNum[0], aux->value.tokenNum[1], aux->value.value);
		else
			printf(" %c%c ", aux->value.tokenNum[0], aux->value.tokenNum[1]);
		aux = aux->next;
		if (aux != NULL)
			printf("|");
	}
	printf("\n");

}

void clean_buffer (char* word) {
	int i;
	for (i = 0; i < 11 ; i ++)
		word[i] = '\0';
}


int issymbol (char letter) {
	switch (letter) {
		case '+':
			return 1;
		case '-':
			return 1;
		case '*':
			return 1;
		case '(':
			return 1;
		case ')':
			return 1;
		case '=':
			return 1;
		case ':':
			return 1;
		case ',':
			return 1;
		case '.':
			return 1;
		case '<':
			return 1;
		case '>':
			return 1;
		case ';':
			return 1;
		default:
			return 0;
	}
}