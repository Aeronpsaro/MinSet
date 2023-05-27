#pragma once
#include "../deps/templated-hashmap/hashmap.h"
#include "Node.h"

typedef HASHMAP(char, Node) Map;

extern Map *graphDict;
