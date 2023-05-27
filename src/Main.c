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

Map *graphDict;
Map *fullDict;

int main() {
	FILE *validWordsDict = fopen("dict/Clave_con_categorías.txt", "r");
	FILE *dictionary = fopen("dict/Clave_Legible.txt", "r");
	StringSet *validWords = readDict(validWordsDict);
	graphDict = readDefs(dictionary, validWords);
	cset__free(validWords);
	printf("El número de palabras del diccionario es %zu\n",
	       hashmap_size(fullDict)); //(graphDict));
	const char *word;
	Node *node;
	// hashmap_foreach_data(node, graphDict) { printf("%s\n", node->word);
	// printParents(node); }
	getCore(graphDict);
	printf("El número de palabras del núcleo del diccionario es %zu\n",
	       hashmap_size(graphDict));
	getMinSet(graphDict);
	printf("El número de palabras del pseudoconjunto mínimo del "
	       "diccionario es %zu\n",
	       hashmap_size(graphDict));
	uint i = 0;
	string minSetOrder[hashmap_size(graphDict)];
	hashmap_foreach_key(word, graphDict) {
		minSetOrder[i] = word;
		i++;
	}
	FILE *synonymMatrix = fopen("dict/synonymMatrix.csv", "w");
	for (int j = 0; j < i; j++) {
		fprintf(synonymMatrix, ";%s", minSetOrder[j]);
	}
	hashmap_foreach(word, node, fullDict) {
		fprintf(synonymMatrix, "\n");
		NodeMap *def = expandNode(node);
		fprintf(synonymMatrix, "%s", word);
		for (int j = 0; j < i; j++) {
			uint *appearancesDir = hashmap_get(def, minSetOrder[j]);
			uint appearances = 0;
			if (!(appearancesDir == NULL)) {
				appearances = *appearancesDir;
			}
			fprintf(synonymMatrix, ";%u", appearances);
		}
	}
}
