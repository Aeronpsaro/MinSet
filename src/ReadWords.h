#pragma once
#include "StringSet.h"
#include "Map.h"
StringSet *readDict(FILE *dictionary);
Map *readDefs(FILE *dictionary, StringSet *validWords);
