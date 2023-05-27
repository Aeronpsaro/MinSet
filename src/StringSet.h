#pragma once
#include "../deps/cset/cset.h"
#include "String.h"

Cset(string) StringSet;
Cset_iterator(StringSet) StringSetIterator;

void stringSetInitialize(StringSet *stringSet);
