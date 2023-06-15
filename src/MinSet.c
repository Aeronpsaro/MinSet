#include "MinSet.h"
#include "../deps/cset/cset.h"
#include "../local-deps/heap/heap.h"
#include "Map.h"
#include "Node.h"
#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <sys/types.h>

void addParents(Node *node, Node *parentsNode) {
	const char *parent;
	hashmap_foreach_key(parent, &parentsNode->parents) {
		addParent(node, getNodeFromWord(parent));
	}
}

void addChildren(Node *node, Node *childrenNode) {
	NodeSet *children = &childrenNode->children;
	NodeSet temp;
	cset__init(&temp);
	cset__union(&temp, &node->children, children);
	cset__free(&node->children);
	node->children = temp;
}

void removeNodeFromParent(Node *node, Node *parent) {
	cset__remove(&parent->children, node);
}

uint parentAppearances(Node *node, Node *parent) {
	return *hashmap_get(&node->parents, parent->word);
}

void removeNodeFromChild(Node *node, Node *child) {
	hashmap_remove(&child->parents, node->word);
}

void removeNode(Node *node) {
	NodeSetIterator iterator;
	cset_iterator__init(&iterator, &node->children);
	while (!cset_iterator__done(&iterator)) {
		Node **child;
		cset_iterator__next(&iterator, child);
		addParents(*child, node);
		removeNodeFromChild(node, *child);
	}
	const char *parent;
	hashmap_foreach_key(parent, &node->parents) {
		addChildren(getNodeFromWord(parent), node);
		removeNodeFromParent(node, getNodeFromWord(parent));
	}
	freeNode(node);
}

bool isSelfParent(Node *node) {
	bool isSelfParent;
	cset__contains(&node->children, node, &isSelfParent);
	return isSelfParent;
}

bool nodeCompare(const Node *node1, const Node *node2) {
	return nodeChildCount(node1) < nodeChildCount(node2);
}

typedef HEAP(Node) NodeHeap;

void getMinSet(Map *graphDict) {
	const char *word;
	void *tmp;
	bool removeable;
	NodeHeap nodeHeap;
	heap_init(&nodeHeap, nodeCompare);
	Node *node;
	hashmap_foreach_data(node, graphDict) { heap_push(&nodeHeap, node); }
	do {
		NodeHeap newHeap;
		heap_init(&newHeap, nodeCompare);
		removeable = false;
		while ((node = heap_pop(&nodeHeap))) {
			if (!isSelfParent(node) && parentCount(node) >= 1) {
				hashmap_remove(graphDict, node->word);
				removeNode(node);
				removeable = true;
				printf("%zu\n", hashmap_size(graphDict));
			} else {
				heap_push(&newHeap, node);
			}
		}
		nodeHeap = newHeap;
	} while (removeable);
}
