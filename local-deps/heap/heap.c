#include "heap_base.h"
#include <stdlib.h>

void heap_base_init(struct heap_base *heap,
		    bool (*compare)(const void *, const void *)) {
	heap->size = 0;
	heap->allocated = 16;
	heap->elements = malloc(heap->allocated * sizeof(void *));
	heap->compare = compare;
}

void heap_base_grow(struct heap_base *heap) {
	heap->size++;
	if (heap->size >= heap->allocated) {
		heap->allocated = 2 * heap->allocated;
		heap->elements =
		    realloc(heap->elements, heap->allocated * sizeof(void *));
	}
}

static inline unsigned int left_child_index(unsigned int index) {
	return 2 * index + 1;
}

static inline unsigned int right_child_index(unsigned int index) {
	return 2 * index + 2;
}

static inline unsigned int parent_index(unsigned int index) {
	return (index - 1) / 2;
}

void heap_base_push(struct heap_base *heap, const void *element) {
	if (heap->size == 0) {
		heap->elements[0] = element;
		heap->size = 1;
		return;
	}
	heap_base_grow(heap);
	unsigned int index = heap->size - 1;
	heap->elements[index] = element;
	while (index > 0 && heap->compare(element, heap->elements[parent_index(index)])) {
		heap->elements[index] = heap->elements[parent_index(index)];
		heap->elements[parent_index(index)] = element;
		index = parent_index(index);
	}
}

void heapify(struct heap_base *heap, unsigned int index) {
	const void *element = heap->elements[index];
	unsigned int largest_index = index;
	if (left_child_index(index) < heap->size &&
	    heap->compare(heap->elements[left_child_index(index)], element)) {
		largest_index = left_child_index(index);
	}
	if (right_child_index(index) < heap->size &&
	    heap->compare(heap->elements[right_child_index(index)],
			  heap->elements[largest_index])) {
		largest_index = right_child_index(index);
	}
	if (largest_index != index) {
		heap->elements[index] = heap->elements[largest_index];
		heap->elements[largest_index] = element;
		heapify(heap, largest_index);
	}
}

const void *heap_base_pop(struct heap_base *heap) {
	if (heap->size == 0)
		return NULL;
	const void *extracted = heap->elements[0];
	heap->size--;
	const void *last = heap->elements[heap->size];
	heap->elements[0] = last;
	heapify(heap, 0);
	return extracted;
}

void heap_base_free(struct heap_base *heap) {
	free(heap->elements);
	free(heap);
}
