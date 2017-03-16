

#ifndef LEXER
#define LEXER

#include "../Auxiliar Structures/Queue.h"
void clean_buffer (char* word);
void outputTable (queue* lexeme_list);
void outputList (queue* lexeme_list);
int issymbol (char letter);
queue* LexicalAnalyzer ( int flag );

#endif