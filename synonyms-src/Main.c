#include "../deps/csv-fast-reader/csv.h"
#include "Synonym.h"
#include "SynonymFinder.h"
#include "WordArray.h"
#include "WordFinder.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>

int main(int argc, const char *argv[argc + 1]) {
	CsvHandle csv = CsvOpen2("dict/synonymMatrix.csv", ';', '"', '\\');
	const char *word = argv[1];
	WordArray wordArray = findWord(&csv, word);
	CsvClose(csv);
	WordArray *total = malloc(sizeof(WordArray));
	*total = wordArray;
	for (uint i = 2; i < argc; i++) {
		CsvHandle csv = CsvOpen2("dict/synonymMatrix.csv", ';', '"', '\\');
		const char *word = argv[i];
		WordArray wordArray = findWord(&csv, word);
		CsvClose(csv);
		if (wordArray.length == 0) {
			printf("La palabra %s no está en el diccionario.\n", word);
			return 1;
		}
		WordArray *tmp = wordArraySum(total, &wordArray);
		free(total);
		total = tmp;
	}
	csv = CsvOpen2("dict/synonymMatrix.csv", ';', '"', '\\');
	SynonymHeap synonyms = *findSynonyms(&csv, total);
	// printf("%s\n", wordArray.word);
	// wordArrayPrint(&wordArray);
	for (uint i = 1; i <= 30; i++) {
		const Synonym *synonym = heap_pop(&synonyms);
		printf("Sinónimo %u, %s, Distancia: %f\n", i, synonym->word,
		       synonym->distance);
	}
}
