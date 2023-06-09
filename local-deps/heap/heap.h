#pragma once

#include "heap_base.h"

#define HEAP(element_type)                                                     \
	struct {                                                               \
		struct heap_base heap_base;                                    \
		struct {                                                       \
			const element_type *t_element;                         \
			bool (*t_compare_func)(const element_type *,           \
					       const element_type *);          \
			void (*t_push_func)(element_type *);                   \
			element_type *(*t_pop_func)();                         \
		} heap_types[0];                                               \
	}

#define heap_init(heap, compare_func)                                          \
	{                                                                      \
		typeof((heap)->heap_types->t_compare_func) __heap_compare =    \
		    (compare_func);                                            \
		heap_base_init(                                                \
		    &(heap)->heap_base,                                        \
		    (bool (*)(const void *, const void *))__heap_compare);     \
	}

#define heap_push(heap, element)                                               \
	{                                                                      \
		typeof((heap)->heap_types->t_element) __heap_element =         \
		    (element);                                                 \
		heap_base_push(&(heap)->heap_base,                             \
			       (const void *)__heap_element);                  \
	}

#define heap_pop(heap)                                                         \
	(typeof((heap)->heap_types->t_element))heap_base_pop(&(heap)->heap_base)

#define heap_free(heap) heap_base_free(&(heap)->heap_base)
