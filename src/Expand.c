#include "Map.h"
#include "Node.h"
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

bool inMinSet(const char *word) {
	return !(hashmap_get(graphDict, word) == NULL);
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

void addDefinition(const char *word, uint appearances, NodeMap *defs) {
	Node *wordNode = hashmap_get(fullDict, word);
	const char *defWord;
	uint *defWordCount;
	hashmap_foreach(defWord, defWordCount, &wordNode->parents) {
		if (inMinSet(defWord)) {
			uint *finalCount = malloc(sizeof(uint));
			*finalCount = appearances * (*defWordCount);
			addToDefs(defs, defWord, finalCount);
		} else {
			addDefinition(defWord, appearances * (*defWordCount), defs);
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
			addDefinition(word, *wordCount, minDef);
		}
	}
	return minDef;
}
