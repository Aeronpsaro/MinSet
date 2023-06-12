#pragma once

#include <sys/types.h>

typedef struct {
	const char *word;
	size_t length;
	uint *appearances;
} WordArray;

float wordDistance(const WordArray *, const WordArray *);
void wordArrayPrint(const WordArray *word);
