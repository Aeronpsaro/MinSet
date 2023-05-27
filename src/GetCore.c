#include "../deps/cset/cset.h"
#include "Map.h"
#include "Node.h"
#include <stdbool.h>
#include <stdlib.h>
#include <sys/types.h>

void removeChildlessNode(Node *node) {
	const char *parent;
	hashmap_foreach_key(parent, &node->parents) {
		cset__remove(&(getNodeFromWord(parent))->children, node);
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
