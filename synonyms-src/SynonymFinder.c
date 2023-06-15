#include "SynonymFinder.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool synonymCompare(const Synonym *synonym1, const Synonym *synonym2) {
	return synonym1->distance - synonym2->distance <= 0;
}

SynonymHeap *findSynonyms(CsvHandle *csv, WordArray *wordArray) {
	SynonymHeap *synonyms = malloc(sizeof(SynonymHeap));
	heap_init(synonyms, synonymCompare);
	char *row;
	CsvReadNextRow(*csv);
	while ((row = CsvReadNextRow(*csv))) {
		WordArray currentWordArray;
		currentWordArray.length = wordArray->length;
		currentWordArray.appearances =
		    malloc(sizeof(currentWordArray.appearances[0]) *
			   currentWordArray.length);
		const char *col;
		col = CsvReadNextCol(row, *csv);
		assert(col != NULL);
		if (strcmp(col, wordArray->word) == 0)
			continue;
		char *word = malloc(strlen(col) + 1);
		strcpy(word, col);
		uint i = 0;
		while ((col = CsvReadNextCol(row, *csv))) {
			currentWordArray.appearances[i++] = atoi(col);
		}
		Synonym *synonym = malloc(sizeof(Synonym));
		synonym->word = word;
		synonym->distance = wordDistance(wordArray, &currentWordArray);
		heap_push(synonyms, synonym);
	}
	return synonyms;
}
