#include "WordFinder.h"
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

WordArray findWord(CsvHandle *restrict csv, const char *restrict word) {
	WordArray wordArray;
	wordArray.word = word;
	wordArray.appearances = malloc(0);
	char *row;
	wordArray.length = 0;
	while ((row = CsvReadNextRow(*csv))) {
		const char *col;
		col = CsvReadNextCol(row, *csv);
		assert(col != NULL);
		if (strcmp(col, word) != 0)
			continue;
		uint i = 0;
		while ((col = CsvReadNextCol(row, *csv))) {
			wordArray.appearances =
			    realloc(wordArray.appearances,
				    (i + 1) * sizeof(wordArray.appearances[0]));
			wordArray.appearances[i++] = atoi(col);
		}
		wordArray.length = i;
	}
	return wordArray;
}
