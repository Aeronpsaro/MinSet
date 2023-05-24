#include "Node.h"
#include <stdio.h>
#include <sys/types.h>

void printChildren(Node *word) {
	printf("Define a:\n");
	NodeSetIterator iterator;
	cset_iterator__init(&iterator, &word->children);
	for (Node **child;; cset_iterator__done(&iterator)) {
		cset_iterator__next(&iterator, child);
		printf("%s ", (*child)->word);
	}
	printf("\n");
}

void printParents(Node *word) {
	printf("Definición: ");
	const NodePointer *parent;
	hashmap_foreach_key(parent, &word->parents) {
		printf("%s ", (*parent)->word);
	}
	printf("\n");
}
