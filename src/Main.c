#include "../deps/cset/cset.h"
#include "../deps/templated-hashmap/hashmap.h"
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

int main() {
	FILE *validWordsDict = fopen("dict/Clave_con_categorías.txt", "r");
	FILE *dictionary = fopen("dict/Clave_Legible.txt", "r");
	StringSet *validWords = readDict(validWordsDict);
	Map *graphDict = readDefs(dictionary, validWords);
	cset__free(validWords);
	printf("El número de palabras del diccionario es %zu\n",
	       hashmap_size(graphDict));
	const char *word;
	Node *node;
	hashmap_foreach_data(node, graphDict) { printParents(node); }
	getCore(graphDict);
	printf("El número de palabras del núcleo del diccionario es %zu\n",
	       hashmap_size(graphDict));
	getMinSet(graphDict);
	printf("El número de palabras del pseudoconjunto mínimo del "
	       "diccionario es %zu\n",
	       hashmap_size(graphDict));
	hashmap_foreach_key(word, graphDict) { printf("%s\n", word); }
}
