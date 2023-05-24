#include <stdbool.h>
#include <stdlib.h>
#include <sys/types.h>
#include "../deps/cset/cset.h"
#include "Node.h"
#include "Map.h"

void removeChildlessNode(Node *node) {
	for (uint i = 0; i < node->parentCount; i++) {
		Node *parent = node->parents[i];
		cset__remove(&parent->children, node);
	}
	freeNode(node);
}

void getCore(Map *graphDict) {
	const char *word;
	bool wordsLeft = false;
	do {
		wordsLeft = false;
		void *tmp;
		hashmap_foreach_key_safe(word, graphDict, tmp) {
			Node *wordNode = hashmap_get(graphDict, word);
			if (nodeChildCount(wordNode) == 0) {
				removeChildlessNode(wordNode);
				hashmap_remove(graphDict, word);
				wordsLeft = true;
			}
		}
	} while (wordsLeft);
}
