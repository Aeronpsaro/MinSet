#include "Node.h"
#include <stdbool.h>
#include <sys/types.h>

size_t nodePointerHash(const NodePointer *x) {
	return hashmap_hash_default(x, sizeof(NodePointer));
}

int nodePointerCompare(const NodePointer *x, const NodePointer *y) {
	return !(*x == *y);
}

Node *initializeNode(string word) {
	Node *node = (Node *)malloc(sizeof(Node));
	node->word = word;
	NodeSet children;
	cset__init(&children);
	node->children = children;
	NodeMap parents;
	hashmap_init(&parents, nodePointerHash, nodePointerCompare);
	node->parents = parents;
	return node;
}

void addParent(Node *node, Node *parentNode) {
	uint *parentCount;
	if (!(parentCount = hashmap_get(&node->parents, &parentNode))) {
		parentCount = malloc(sizeof(uint));
		*parentCount = 1;
		hashmap_put(&node->parents, &parentNode, parentCount);
	} else {
		*parentCount = *parentCount + 1;
	}
}

void freeNode(Node *node) {
	cset__free(&node->children);
	hashmap_cleanup(&node->parents);
	free(node);
}

bool isChild(Node *child, Node *parent) {
	bool isChild;
	cset__contains(&parent->children, child, &isChild);
	return isChild;
}

size_t nodeChildCount(Node *node) { return cset__size(&node->children); }

uint parentCount(Node *node) { return hashmap_size(&node->parents); }
