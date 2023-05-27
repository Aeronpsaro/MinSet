#include "ReadWords.h"
#include "../deps/templated-hashmap/hashmap.h"
#include "Map.h"
#include "Node.h"
#include "String.h"
#include "StringSet.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

#define dictSize 41493

StringSet *readDict(FILE *dictionary) {
	StringSet *wordList = malloc(sizeof(StringSet));
	stringSetInitialize(wordList);
	string newWord = malloc(40 * sizeof(char));
	for (uint i = 0; fscanf(dictionary, "%s", newWord) != EOF; i++) {
		cset__add(wordList, newWord);
		newWord = malloc(40 * sizeof(char));
	}
	return wordList;
}

static inline void getDefinition(FILE *dictionary, Map *map, Node *wordNode, Node *copyNode) {
	string parent = malloc(40 * sizeof(char));
	while (fscanf(dictionary, "%s", parent) != EOF) {
		Node *parentNode = hashmap_get(map, parent);
		Node *copyParentNode = hashmap_get(fullDict, parent);
		if (parentNode == NULL) {
			parentNode = initializeNode(parent);
			cset__add(&parentNode->children, wordNode);
			hashmap_put(map, parent, parentNode);
			copyParentNode = initializeNode(parent);
			cset__add(&copyParentNode->children, copyNode);
			hashmap_put(fullDict, parent, copyParentNode);
		} else {
			cset__add(&parentNode->children, wordNode);
			cset__add(&copyParentNode->children, copyNode);
		}
		addParent(wordNode, parentNode);
		addParent(copyNode, copyParentNode);
		if (fgetc(dictionary) == '\n')
			break;
		parent = malloc(40 * sizeof(char));
	}
}

Map *readDefs(FILE *dictionary, StringSet *validWords) {
	Map *graphDict = malloc(sizeof(Map));
	fullDict = malloc(sizeof(Map));
	hashmap_init(graphDict, hashmap_hash_string, strcmp);
	hashmap_init(fullDict, hashmap_hash_string, strcmp);
	string word = malloc(40 * sizeof(char));
	while (fscanf(dictionary, "#%s\n", word) != EOF) {
		bool isValid;
		cset__contains(validWords, word, &isValid);
		if (!isValid) {
			fscanf(dictionary, "%*[^\n]\n");
			continue;
		}
		Node *wordNode = hashmap_get(graphDict, word);
		Node *copyNode = hashmap_get(fullDict, word);
		if (wordNode == NULL) {
			wordNode = initializeNode(word);
			hashmap_put(graphDict, word, wordNode);
			copyNode = initializeNode(word);
			hashmap_put(fullDict, word, copyNode);
		}
		getDefinition(dictionary, graphDict, wordNode, copyNode);
		word = malloc(40 * sizeof(char));
	}
	return graphDict;
}
