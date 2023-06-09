#pragma once

#include "../deps/csv-fast-reader/csv.h"
#include "WordArray.h"

WordArray findWord(CsvHandle *restrict csv,const char *restrict word);
