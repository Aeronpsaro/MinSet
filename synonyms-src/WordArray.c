#include "WordArray.h"
#include <math.h>
#include <stdio.h>

void wordArrayPrint(WordArray *word) {
	printf("%s ", word->word);
	for (uint i = 0; i < word->length; i++) {
		printf("%u ", word->appearances[i]);
	}
}

float euclideanWordDistance(WordArray *word1, WordArray *word2) {
	float distance = 0;
	for (uint i = 0; i < word1->length; i++) {
		float tmp = (word1->appearances[i] - word2->appearances[i]);
		distance += tmp * tmp;
	}
	return distance;
}

float logWordDistance(WordArray *word1, WordArray *word2) {
	float distance = 0;
	for (uint i = 0; i < word1->length; i++) {
		distance += fabs(log(word1->appearances[i] + 1) -
			     log(word2->appearances[i] + 1));
	}
	return distance;
}

float wordDistance(WordArray *word1, WordArray *word2) {
	return logWordDistance(word1, word2);
}
