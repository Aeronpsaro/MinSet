#pragma once
#include <stddef.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../deps/cset/cset.h"
#include "String.h"

typedef struct Node Node;
typedef Node * NodePointer;
Cset(NodePointer) NodeSet;

Cset_iterator(NodeSet) NodeSetIterator;

struct Node {
	string word;
	NodeSet children;
	unsigned int parentCount;
	Node **parents;
};


static inline void freeNode(Node *node) {
	cset__free(&node->children);
	free(node->parents);
	free(node);
}

static inline bool isChild(Node *child, Node *parent) {
	bool isChild;
	cset__contains(&parent->children, child, &isChild);
	return isChild;
}

static inline size_t nodeChildCount(Node *node) {
	return cset__size(&node->children);
}

#define foreachChild(node, child)\
NodeSetIterator iterator;\
cset_iterator__init(&iterator, & node);\
for (Node * child; cset_iterator__next(&iterator, child); cset_iterator__done(&iterator))
