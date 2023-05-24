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
		newWord = malloc(40 * sizeof(char));
		cset__add(wordList, newWord);
	}
	return wordList;
}

static inline void getDefinition(FILE *dictionary, Map *map, Node *wordNode) {
	string parent = malloc(40 * sizeof(string));
	while (fscanf(dictionary, "%s", parent) != EOF) {
		Node *parentNode = hashmap_get(map, parent);
		if (parentNode == NULL) {
			parentNode = initializeNode(parent);
			cset__add(&parentNode->children, wordNode);
			hashmap_put(map, parent, parentNode);
		} else {
			cset__add(&parentNode->children, wordNode);
		}
		addParent(wordNode, parentNode);
		if (fgetc(dictionary) == '\n')
			break;
		parent = malloc(40 * sizeof(string));
	}
}

Map *readDefs(FILE *dictionary, StringSet *validWords) {
	Map *graphDict = malloc(sizeof(Map));
	hashmap_init(graphDict, hashmap_hash_string, strcmp);
	string word = malloc(40 * sizeof(string));
	while (fscanf(dictionary, "#%s\n", word) != EOF) {
		bool isValid;
		cset__contains(validWords, word, &isValid);
		if (!isValid) {
			fscanf(dictionary, "%*[^\n]\n");
			continue;
		}
		Node *wordNode = hashmap_get(graphDict, word);
		if (wordNode == NULL) {
			wordNode = initializeNode(word);
			hashmap_put(graphDict, word, wordNode);
		}
		getDefinition(dictionary, graphDict, wordNode);
		word = malloc(40 * sizeof(string));
	}
	return graphDict;
}
