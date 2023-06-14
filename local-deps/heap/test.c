#include "heap.h"
#include <assert.h>
#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

static inline unsigned int left(unsigned int index) { return 2 * index + 1; }
static inline unsigned int right(unsigned int index) { return 2 * index + 2; }
static inline unsigned int prev(unsigned int index) { return (index - 1) / 2; }

bool compare(const int *a, const int *b) { return *a > *b; }

int main() {
	srand(time(NULL));
	HEAP(int) heap;
	int a[1000];
	heap_init(&heap, compare);
	for (unsigned int i = 0; i < 1000; i++) {
		a[i] = rand();
		heap_push(&heap, &a[i]);
	}
	for (unsigned int i = 0; i < 1000; i++) {
		unsigned int element =
		    *(unsigned int *)heap.heap_base.elements[i];
		if (left(i) < 100) {
			unsigned int leftElement =
			    *(unsigned int *)heap.heap_base.elements[left(i)];
			assert(element >= leftElement);
		}
		if (right(i) < 100) {
			unsigned int rightElement =
			    *(unsigned int *)heap.heap_base.elements[right(i)];
			assert(element >= rightElement);
		}
	}
	int previous = INT_MAX;
	const int *current;
	int j = 0;
	while ((current = heap_pop(&heap))) {
		assert(previous >= *current);
		printf("%i\n", *current);
		previous = *current;
		j++;
	}
	assert(j == 1000);
	a[0] = rand();
	heap_push(&heap, &a[0]);
	unsigned int i = 1;
	unsigned int k = 1;
	previous = INT_MAX;
	while (i > 0 && k < 1000) {
		if (rand() <= RAND_MAX / 4) {
			unsigned int popped = *heap_pop(&heap);
			i--;
			printf("popped: %u\n", popped);
			assert(previous >= popped);
			previous = popped;
		} else {
			a[k] = rand();
			if (a[k] > previous)
				previous = a[k];
			heap_push(&heap, &a[k]);
			printf("a[%u] = %u\n", k, a[k]);
			k++;
			i++;
			for (unsigned int l = 0; l < i; l++) {
				unsigned int element =
				    *(unsigned int *)heap.heap_base.elements[l];
				if (left(l) < i) {
					unsigned int leftElement =
					    *(unsigned int *)heap.heap_base
						 .elements[left(l)];
					assert(element >= leftElement);
				}
				if (right(l) < i) {
					unsigned int rightElement =
					    *(unsigned int *)heap.heap_base
						 .elements[right(l)];
					assert(element >= rightElement);
				}
			}
		}
		printf("%u\n", i);
	}
}
