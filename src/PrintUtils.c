#include <stdio.h>
#include <sys/types.h>
#include "Node.h"

void printChildren(Node *word) {
	printf("Define a:\n");
	NodeSetIterator iterator;
	cset_iterator__init(&iterator, &word->children);
	for(Node **child;; cset_iterator__done(&iterator)) {
		cset_iterator__next(&iterator, child);
		printf("%s ", (*child)->word);
	}
	printf("\n");
}

void printParents(Node *word) {
	printf("Definición: ");
	for (uint i = 0; i < word->parentCount; i++) {
		printf("%s ", word->parents[i]->word);
	}
	printf("\n");
}
