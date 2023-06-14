#include "../deps/cset/cset.h"
#include "../deps/templated-hashmap/hashmap.h"
#include "Expand.h"
#include "GetCore.h"
#include "Map.h"
#include "MinSet.h"
#include "Node.h"
#include "PrintUtils.h"
#include "ReadWords.h"
#include "StringSet.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

// #define TEST
#ifndef TEST
	#define VALID_DICT "dict/Vox_con_categorías.txt"
	#define DICT "dict/Clave_Legible.txt"
	#define MATRIX_DICT "dict/synonymMatrix.csv"
#endif
#ifdef TEST
	#define VALID_DICT "dict/Valid_Test.txt"
	#define DICT "dict/Legible_Test.txt"
	#define MATRIX_DICT "dict/synonymMatrixTest.csv"
#endif

Map *graphDict;
Map *fullDict;
StringSet *minSet;

int main() {
	FILE *validWordsDict =
	    fopen(VALID_DICT,
		  "r"); //"dict/Clave_con_categorías.txt", "r");
	FILE *dictionary =
	    fopen(DICT, "r"); //"dict/Clave_Legible.txt", "r");
	StringSet *validWords = readDict(validWordsDict);
	graphDict = readDefs(dictionary, validWords);
	cset__free(validWords);
	printf("El número de palabras del diccionario es %zu\n",
	       hashmap_size(fullDict)); //(graphDict));
	const char *word;
	Node *node;
	// hashmap_foreach_data(node, graphDict) {
	// 	printf("%s\n", node->word);
	// 	printParents(node);
	// }
	getCore(graphDict);
	printf("El número de palabras del núcleo del diccionario es %zu\n",
	       hashmap_size(graphDict));
	getMinSet(graphDict);
	printf("El número de palabras del pseudoconjunto mínimo del "
	       "diccionario es %zu\n",
	       hashmap_size(graphDict));
	// hashmap_foreach_data(node, graphDict) {
	// 	printf("%s\n", node->word);
	// }
	uint i = 0;
	const char *minSetOrder[hashmap_size(graphDict)];
	minSet = malloc(sizeof(StringSet));
	stringSetInitialize(minSet);
	void *tmp;
	hashmap_foreach_safe(word, node, graphDict, tmp) {
		minSetOrder[i] = word;
		i++;
		cset__add(minSet, word);
		freeNode(node);
	}
	hashmap_cleanup(graphDict);
	FILE *synonymMatrix = fopen(MATRIX_DICT, "w");
	for (int j = 0; j < i; j++) {
		fprintf(synonymMatrix, ";%s", minSetOrder[j]);
	}
	hashmap_foreach(word, node, fullDict) {
		fprintf(synonymMatrix, "\n");
		NodeMap *def = expandNode(node);
		// printf("%s\n", word);
		// printMap(def);
		fprintf(synonymMatrix, "%s", word);
		for (int j = 0; j < i; j++) {
			uint *appearancesDir = hashmap_get(def, minSetOrder[j]);
			uint appearances = 0;
			if (!(appearancesDir == NULL)) {
				appearances = *appearancesDir;
				free(appearancesDir);
			}
			fprintf(synonymMatrix, ";%u", appearances);
		}
		hashmap_cleanup(def);
	}
}
