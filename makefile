pcc : Queue.o Stack.o HashTable.o Set.o LexicalAnalyzer.o CodeGenerator.o Parser.o VirtualMachine.o CompilerDriver.o
	cc -o pcc Queue.o Stack.o HashTable.o Set.o LexicalAnalyzer.o CodeGenerator.o Parser.o VirtualMachine.o CompilerDriver.o


Queue.o : ./Auxiliar\ Structures/Queue.c ./Auxiliar\ Structures/Queue.h
	cc -c ./Auxiliar\ Structures/Queue.c
Stack.o : ./Auxiliar\ Structures/Stack.c ./Auxiliar\ Structures/Stack.h
	cc -c ./Auxiliar\ Structures/Stack.c
HashTable.o : ./Auxiliar\ Structures/HashTable.c ./Auxiliar\ Structures/HashTable.h
	cc -c ./Auxiliar\ Structures/HashTable.c
Set.o : ./Auxiliar\ Structures/Set.c ./Auxiliar\ Structures/Set.h ./Auxiliar\ Structures/Queue.h
	cc -c ./Auxiliar\ Structures/Set.c
LexicalAnalyzer.o : ./Lexical\ Analyzer/LexicalAnalyzer.c ./Lexical\ Analyzer/LexicalAnalyzer.h ./Auxiliar\ Structures/Queue.h
	cc -c ./Lexical\ Analyzer/LexicalAnalyzer.c
CodeGenerator.o : ./Code\ Generator/CodeGenerator.c ./Code\ Generator/CodeGenerator.h ./Auxiliar\ Structures/Stack.h
	cc -c ./Code\ Generator/CodeGenerator.c
Parser.o : ./Parser/Parser.c ./Parser/Parser.h ./Auxiliar\ Structures/Queue.h ./Auxiliar\ Structures/HashTable.h ./Auxiliar\ Structures/Set.h ./Code\ Generator/CodeGenerator.h
	cc -c ./Parser/Parser.c
VirtualMachine.o : ./Virtual\ Machine/VirtualMachine.c ./Virtual\ Machine/VirtualMachine.h ./Code\ Generator/CodeGenerator.h
	cc -c ./Virtual\ Machine/VirtualMachine.c
CompilerDriver.o : ./CompilerDriver.c ./Lexical\ Analyzer/LexicalAnalyzer.h ./Parser/Parser.h ./Code\ Generator/CodeGenerator.h ./Virtual\ Machine/VirtualMachine.h
	cc -c ./CompilerDriver.c

clean :
	rm pcc Queue.o Stack.o HashTable.o Set.o LexicalAnalyzer.o CodeGenerator.o Parser.o VirtualMachine.o CompilerDriver.o