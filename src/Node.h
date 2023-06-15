#pragma once
#include "../deps/cset/cset.h"
#include "../deps/templated-hashmap/hashmap.h"
#include "String.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include <sys/types.h>

typedef struct Node Node;
typedef Node *NodePointer;
Cset(NodePointer) NodeSet;

Cset_iterator(NodeSet) NodeSetIterator;

typedef HASHMAP(char, uint) NodeMap;

struct Node {
	string word;
	NodeSet children;
	NodeMap parents;
};

Node *initializeNode(const string word);

void freeNode(Node *node);

void addParent(Node *node, Node *parentNode);

bool isChild(const Node *child, Node *parent);

size_t nodeChildCount(const Node *node);

uint parentCount(const Node *node);

Node *getNodeFromWord(const char *word);
