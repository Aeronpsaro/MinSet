#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <sys/types.h>
#include "../deps/cset/cset.h"
#include "Node.h"
#include "Map.h"

void addParents(Node *node, uint l, Node *parents[l]) {
	uint initialCount = node->parentCount;
	node->parentCount += l;
	node->parents =
	    realloc(node->parents, node->parentCount * sizeof(Node *));
	for (uint i = initialCount; i < node->parentCount; i++) {
		node->parents[i] = parents[i - initialCount];
	}
}

void addChildren(Node *node, NodeSet *children) {
	NodeSet temp;
	cset__init(&temp);
	cset__union(&temp, &node->children, children);
	node->children = temp;
}

void removeNodeFromParent(Node *node, Node *parent) {
	cset__remove(&parent->children, node);
}

uint parentAppearances(Node *node, Node *parent) {
	uint parentAppearancesCount = 0;
	for (uint i = 0; i < node->parentCount; i++) {
		if (node->parents[i] == parent) {
			parentAppearancesCount++;
		}
	}
	return parentAppearancesCount;
}

void removeNodeFromChild(Node *node, Node *child) {
	uint finalParentCount = child->parentCount - parentAppearances(child, node);
	Node **finalParents = malloc(finalParentCount * sizeof(Node *));
	uint j = 0;
	for (uint i = 0; i < child->parentCount; i++) {
		if (child->parents[i] != node) {
			finalParents[j] = child->parents[i];
			j++;
		}
	}
	//assert(finalParentCount == j);
	free(child->parents);
	child->parents = finalParents;
	child->parentCount = finalParentCount;
}

void removeNode(Node *node) {
	NodeSetIterator iterator;
	cset_iterator__init(&iterator, &node->children);
	while(!cset_iterator__done(&iterator)) {
		Node **child;
		cset_iterator__next(&iterator, child);
		addParents(*child, node->parentCount, node->parents);
		removeNodeFromChild(node, *child);
	}
	for (uint i = 0; i < node->parentCount; i++) {
		addChildren(node->parents[i], &node->children);
		removeNodeFromParent(node, node->parents[i]);
	}
	freeNode(node);
}

bool isSelfParent(Node *node) {
	bool isSelfParent;
	cset__contains(&node->children, node, &isSelfParent);
	return isSelfParent;
	//for (uint i = 0; i < node->parentCount; i++) {
	//	if (node == node->parents[i])
	//		return true;
	//}
	//return false;
}

void getMinSet(Map *graphDict) {
	const char *word;
	void *tmp;
	bool removeable;
	do {
		removeable = false;
		hashmap_foreach_key_safe(word, graphDict, tmp) {
			Node *node = hashmap_get(graphDict, word);
			if (!isSelfParent(node) && node->parentCount >= 1) {
				hashmap_remove(graphDict, word);
				removeNode(node);
				removeable = true;
			}
		}
	} while (removeable);
}
