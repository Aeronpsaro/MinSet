typedef char* string;
#include "StringSet.h"

cset__u64 strHash(string *str, cset__u64 (*hash)(void*, size_t)) {
	return hash(*str, strlen(*str));
}

bool strCmp(string *str1, string *str2) {
	return strcmp(*str1, *str2)==0;
}

void stringSetInitialize(StringSet *stringSet) {
	cset__init(stringSet);
	cset__set_hash(stringSet, strHash);
	cset__set_comparator(stringSet, strCmp);
}
