#pragma once

#include <stdlib.h>

typedef struct rstring{
	char* characters;
	size_t length;
	size_t capacity;
} rstring;

size_t CalculateStringLength(const char* string, size_t capacity);
rstring* CreateString(const char* characters, size_t capacity);
rstring* CreateEmptyString(size_t capacity);
void DeleteString(rstring* string);
rstring* ConcatenateStrings(rstring* string1, rstring* string2);
size_t FindFirstOccurrenceOf(char characterToFind, rstring* string);
int CompareStrings(rstring* string1, rstring* string2);