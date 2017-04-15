/* Author: Jose Pena
 * UCFID: 4142431
 * Tittle: Auxiliar structure Set
 * Class: COP3402
 */

#include "Set.h"
// Create an empty set
setsym* createSet() {
	setsym* s = (setsym*)malloc(sizeof(setsym));
	s->size = 0;
	int i;
	for (i = 0; i < 32 ; i ++)
		s->set[i] = nulsym;
	return s; 
}
// make a copycat of a set
setsym copySet(setsym* s) {
	setsym result;
	result.size = s->size;
	int i;
	for (i = 0; i < s->size; i++)
		result.set[i] = s->set[i];
	return result;
}
// Add an element to the set
void addElement ( token_type t, setsym* s) {
	if ( s->size == 32)
		return;
	int i;
	for ( i = 0 ; i < s->size ; i++) {
		if (s->set[i] == t)
			return;
	}
	s->set[s->size++] = t;
}
// Check if a element is in the set
int existElement ( token_type t, setsym s) {
	int i;
	for ( i = 0 ; i < s.size ; i++) {
		if (s.set[i] == t)
			return 1;
	}
	return 0;
}
// Union of two sets
setsym mergeSet (setsym s1, setsym s2) {
	setsym* placeHolder = createSet();
	int i;
	if ( s1.size > s2.size) {
		for ( i = 0 ; i < s1.size ; i++)
			placeHolder->set[i] = s1.set[i];

		placeHolder->size = s1.size;
		for ( i = 0 ; i < s2.size ; i++)
			addElement(s2.set[i], placeHolder);
	}
	else {
		for ( i = 0 ; i < s2.size ; i++)
			placeHolder->set[i] = s2.set[i];
		placeHolder->size = s2.size;
		for ( i = 0 ; i < s1.size ; i++)
			addElement(s1.set[i], placeHolder);
	}
	setsym result = *placeHolder;
	free(placeHolder);
	return result;
}
// Generated prefixed set following the grammar of PL/0
setsym preGenerated (char * nonTerminal) {
	setsym *fsys = createSet();

	if (strcmp(nonTerminal, "block") == 0) {
		addElement(constsym, fsys);
		addElement(procsym, fsys);
		addElement(identsym, fsys);
		addElement(ifsym, fsys);
		addElement(callsym, fsys);
		addElement(beginsym, fsys);
		addElement(whilesym, fsys);
	}
	setsym result = copySet(fsys);
	free(fsys);
	return result;

}