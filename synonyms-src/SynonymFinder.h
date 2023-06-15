#pragma once

#include "../deps/csv-fast-reader/csv.h"
#include "../local-deps/heap/heap.h"
#include "Synonym.h"
#include "WordArray.h"

typedef HEAP(Synonym) SynonymHeap;

SynonymHeap *findSynonyms(CsvHandle *csv, WordArray *wordArray);
