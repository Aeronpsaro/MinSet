#include "Node.h"
#include "StringSet.h"
#include <stdio.h>
#include <sys/types.h>

void printSet(StringSet *words) {
	StringSetIterator iterator;
	cset_iterator__init(&iterator, words);
	for (string *word;!cset_iterator__done(&iterator);) {
		cset_iterator__next(&iterator, word);
		printf("%s\n", *word);
	}
}

void printMap(NodeMap *words) {
	const char *word;
	uint *wordAppearances;
	hashmap_foreach(word, wordAppearances, words) {
		printf("%u: %s ", *wordAppearances, word);
	}
	printf("\n");
}

void printChildren(Node *word) {
	printf("Define a:\n");
	NodeSetIterator iterator;
	cset_iterator__init(&iterator, &word->children);
	for (Node **child;!cset_iterator__done(&iterator);) {
		cset_iterator__next(&iterator, child);
		printf("%s ", (*child)->word);
	}
	printf("\n");
}

void printParents(Node *word) {
	printf("Definición: ");
	const char *parent;
	uint *parentAppearances;
	hashmap_foreach(parent, parentAppearances, &word->parents) {
		printf("%u: %s ", *parentAppearances, parent);//getNodeFromWord(parent)->word);
	}
	printf("\n");
}

void printParentsAdresses(Node *word) {
	printf("Definición: ");
	const char *parent;
	hashmap_foreach_key(parent, &word->parents) {
		printf("%p ", parent);
	}
	printf("\n");
}
