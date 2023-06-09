#include "../deps/csv-fast-reader/csv.h"
#include "Synonym.h"
#include "SynonymFinder.h"
#include "WordArray.h"
#include "WordFinder.h"
#include <stdio.h>
#include <sys/types.h>

int main(int argc, const char *argv[argc]) {
	const char *word = argv[1];/* "locura:1000"; //"anisotropo:1100"; */
	CsvHandle csv = CsvOpen2("dict/synonymMatrix.csv", ';', '"', '\\');
	WordArray wordArray = findWord(&csv, word);
	CsvClose(csv);
	if (wordArray.length == 0) {
		printf("La palabra %s no está en el diccionario.\n", word);
		return 1;
	}
	csv = CsvOpen2("dict/synonymMatrix.csv", ';', '"', '\\');
	SynonymHeap synonyms = *findSynonyms(&csv, &wordArray);
	// printf("%s\n", wordArray.word);
	// wordArrayPrint(&wordArray);
	for (uint i = 1; i <= 15; i++) {
		const Synonym *synonym = heap_pop(&synonyms);
		printf("Sinónimo %u, %s, Distancia: %f\n", i, synonym->word,
		       synonym->distance);
	}
}
