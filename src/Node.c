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

Node *initializeNode(string word) {
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
	// static uint times = 0;
	// if (times > 20)
	// 	exit(EXIT_SUCCESS);
	uint *parentCount;
	if (!(parentCount = hashmap_get(&node->parents, parentNode->word))) {
		parentCount = malloc(sizeof(uint));
		*parentCount = 1;
		hashmap_put(&node->parents, parentNode->word, parentCount);
	} else {
		*parentCount = *parentCount + 1;
	}
	// printParentsAdresses(node);
	// times++;
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

Node *getNodeFromWord(const char *word) {
	return hashmap_get(graphDict, word);
}
