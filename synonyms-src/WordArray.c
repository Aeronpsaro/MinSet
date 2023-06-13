#include "WordArray.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

void wordArrayPrint(const WordArray *word) {
	printf("%s ", word->word);
	for (uint i = 0; i < word->length; i++) {
		printf("%u ", word->appearances[i]);
	}
}

WordArray *wordArraySum(const WordArray *restrict word1,
			const WordArray *restrict word2) {
	WordArray *finalArray = malloc(sizeof(WordArray));
	finalArray->word = "";
	finalArray->appearances =
	    malloc(word1->length * sizeof(finalArray->appearances[0]));
	finalArray->length = word1->length;
	for (uint i = 0; i < word1->length; i++) {
		finalArray->appearances[i] =
		    word1->appearances[i] + word2->appearances[i];
	}
	return finalArray;
}

float euclideanWordDistance(const WordArray *word1, const WordArray *word2) {
	float distance = 0;
	for (uint i = 0; i < word1->length; i++) {
		float tmp = (word1->appearances[i] - word2->appearances[i]);
		distance += tmp * tmp;
	}
	return distance;
}

float logWordDistance(const WordArray *word1, const WordArray *word2) {
	float distance = 0;
	// #pragma omp parallel for reduction(+:distance)
	for (uint i = 0; i < word1->length; i++) {
		distance += fabs(log(word1->appearances[i] + 1) -
				 log(word2->appearances[i] + 1));
	}
	return distance;
}

float customDistance(const WordArray *word1, const WordArray *word2) {
	float distance = 0;
#pragma omp parallel
	{
#pragma omp for reduction(+ : distance)
		for (uint i = 0; i < word1->length; i++) {
			uint wa1 = word1->appearances[i];
			uint wa2 = word1->appearances[i];
			if ((wa1 == 0 && wa2 != 0) || (wa1 != 0 && wa2 == 0)) {
				distance += 3.;
			}
			distance += fabs(log(word1->appearances[i] + 1) -
					 log(word2->appearances[i] + 1));
		}
	}
	return distance;
}

float wordDistance(const WordArray *word1, const WordArray *word2) {
	return logWordDistance(word1, word2);
}
