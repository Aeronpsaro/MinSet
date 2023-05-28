#include "Map.h"
#include "Node.h"
#include "StringSet.h"
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

#define MAX_STACK_DEPTH 10

bool inMinSet(const char *word) {
	bool inMinSet;
	cset__contains(minSet, word, &inMinSet);
	return inMinSet;
}

void addToDefs(NodeMap *defs, const char *word, uint *count) {
	uint *currentCount = hashmap_get(defs, word);
	if (currentCount == NULL) {
		currentCount = malloc(sizeof(uint));
		*currentCount = *count;
		hashmap_put(defs, word, currentCount);
	} else {
		*currentCount += *count;
	}
}

void addDefinition(const char *word, uint appearances, NodeMap *defs, uint stackDepth) {
	if (stackDepth == MAX_STACK_DEPTH) return;
	Node *wordNode = hashmap_get(fullDict, word);
	const char *defWord;
	uint *defWordCount;
	hashmap_foreach(defWord, defWordCount, &wordNode->parents) {
		if (inMinSet(defWord)) {
			uint *finalCount = malloc(sizeof(uint));
			*finalCount = appearances * (*defWordCount);
			addToDefs(defs, defWord, finalCount);
			free(finalCount);
		} else {
			addDefinition(defWord, appearances * (*defWordCount),
				      defs, stackDepth + 1);
		}
	}
}

NodeMap *expandNode(Node *node) {
	NodeMap *minDef = malloc(sizeof(NodeMap));
	hashmap_init(minDef, hashmap_hash_string, strcmp);
	const char *word;
	uint *wordCount;
	if (inMinSet(node->word)) {
		wordCount = malloc(sizeof(uint));
		*wordCount = 1;
		addToDefs(minDef, node->word, wordCount);
		return minDef;
	}
	hashmap_foreach(word, wordCount, &node->parents) {
		if (inMinSet(word)) {
			uint *count = malloc(sizeof(uint));
			*count = *wordCount;
			addToDefs(minDef, word, count);
			free(count);
		} else {
			addDefinition(word, *wordCount, minDef, 0);
		}
	}
	return minDef;
}
