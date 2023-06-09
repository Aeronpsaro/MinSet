#pragma once

#include <sys/types.h>

typedef struct {
	const char *word;
	size_t length;
	uint *appearances;
} WordArray;

float wordDistance(WordArray *, WordArray *);
void wordArrayPrint(WordArray *word);
