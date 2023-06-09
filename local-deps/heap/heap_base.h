#pragma once

#include <stdbool.h>
#include <stddef.h>

struct heap_base {
	size_t size;
	size_t allocated;
	const void **elements;
	bool (*compare)(const void *, const void *);
};

void heap_base_init(struct heap_base *heap,
		    bool (*compare)(const void *, const void *));
void heap_base_push(struct heap_base *heap, const void *element);
const void *heap_base_pop(struct heap_base *heap);
void heap_base_free(struct heap_base *heap);
