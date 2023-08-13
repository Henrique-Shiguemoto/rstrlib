#include "rstrlib.h"
#include <stdio.h>

size_t CalculateStringLength(const char* characters, size_t capacity){
	size_t currentLength = 0;
	while(characters[currentLength] != '\0' && currentLength < capacity) currentLength++;
	return currentLength;
}

rstring* CreateString(const char* characters, size_t capacity){
	rstring* newString = malloc(sizeof(rstring));
	newString->capacity = capacity;
	newString->length = CalculateStringLength(characters, capacity);
	
	if(newString->capacity < newString->length)  return NULL;
	if(newString->capacity == newString->length) newString->capacity++;

	newString->characters = malloc(sizeof(char) * newString->capacity);
	if(newString->characters){
		size_t currentIndex = 0;
		while(currentIndex < newString->length){
			newString->characters[currentIndex] = characters[currentIndex];
			currentIndex++;
		}
		newString->characters[currentIndex] = '\0';
		return newString;
	}
	return NULL;
}

rstring* CreateEmptyString(size_t capacity){
	return CreateString("", capacity);
}

rstring* CopyString(rstring* string){
	return CreateString(string->characters, string->capacity);
}

void DeleteString(rstring* string){
	free(string->characters);
	string->characters = NULL;
	string->length = 0;
	string->capacity = 0;
}

rstring* ConcatenateStrings(rstring* string1, rstring* string2){
	rstring* newString = CreateEmptyString(string1->capacity + string2->capacity);
	newString->length = string1->length + string2->length;

	size_t currentIndex = 0;
	while(currentIndex < string1->length){
		newString->characters[currentIndex] = string1->characters[currentIndex];
		currentIndex++;
	}
	currentIndex = 0;
	while(currentIndex < string2->length){
		newString->characters[string1->length + currentIndex] = string2->characters[currentIndex];
		currentIndex++;
	}
	newString->characters[newString->length] = '\0';
	return newString;
}

size_t FindFirstOccurrenceOf(char characterToFind, rstring* string){
	size_t currentIndex = 0;
	while(currentIndex < string->length && string->characters[currentIndex] != '\0'){
		if(string->characters[currentIndex] == characterToFind) return currentIndex;
		currentIndex++;
	}
	return -1;
}

//In this function, we don't care about different capacities.
int CompareStrings(rstring* string1, rstring* string2){
	if(string1->length != string2->length) return 0;

	size_t currentIndex = 0;
	while(currentIndex < string1->length){
		if(string1->characters[currentIndex] != string2->characters[currentIndex]){
			return 0;
		}
		currentIndex++;
	}
	return 1;
}

rstring* ExtractSubstring(rstring* string, size_t from, size_t to){
	if(!string || from > string->length || to > string->length || to < from) return NULL;

	rstring* newString = CreateEmptyString(to - from + 1);
	size_t currentIndex = from;
	while(currentIndex < to && currentIndex < string->length){
		newString->characters[currentIndex - from] = string->characters[currentIndex];
		currentIndex++;
	}
	newString->characters[currentIndex - from] = '\0';
	newString->length = to - from;
	return newString;
}

rstring* ExtractLeftSubstring(rstring* string, size_t characterCount){
	return ExtractSubstring(string, 0, characterCount);
}

rstring* ExtractRightSubstring(rstring* string, size_t characterCount){
	return ExtractSubstring(string, string->length - characterCount, string->length);
}
