#include "Node.h"
#include "Map.h"
#include "PrintUtils.h"
#include <stdbool.h>
#include <stdlib.h>
#include <sys/types.h>

size_t nodePointerHash(const Node *x) {
	return hashmap_hash_default(&x, sizeof(Node *));
}

int nodePointerCompare(const Node *x, const Node *y) {
	return x - y;
}

Node *initializeNode(const string word) {
	Node *node = (Node *)malloc(sizeof(Node));
	node->word = word;
	NodeSet children;
	cset__init(&children);
	node->children = children;
	NodeMap parents;
	hashmap_init(&parents, hashmap_hash_string, strcmp);
	node->parents = parents;
	return node;
}

void addParent(Node *node, Node *parentNode) {
	uint *parentCount;
	if (!(parentCount = hashmap_get(&node->parents, parentNode->word))) {
		parentCount = malloc(sizeof(uint));
		*parentCount = 1;
		hashmap_put(&node->parents, parentNode->word, parentCount);
	} else {
		*parentCount = *parentCount + 1;
	}
}

void freeNode(Node *node) {
	cset__free(&node->children);
	uint *appearances;
	hashmap_foreach_data(appearances, &node->parents){
		free(appearances);
	}
	hashmap_cleanup(&node->parents);
	free(node);
}

bool isChild(const Node *child, Node *parent) {
	bool isChild;
	cset__contains(&parent->children, child, &isChild);
	return isChild;
}

size_t nodeChildCount(const Node *node) { return cset__size(&node->children); }

uint parentCount(const Node *node) { return hashmap_size(&node->parents); }

Node *getNodeFromWord(const char *word) {
	return hashmap_get(graphDict, word);
}
