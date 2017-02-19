CC=gcc
CFLAGS=-I.
DEPS = Lexical_Analyzer.h


%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

lexer: Stack.o Lexical_Analyzer.o
	gcc -o lexer Lexical_Analyzer.o Stack.o -I



