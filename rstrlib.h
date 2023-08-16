#pragma once

#include <stdlib.h>
#include <stdio.h>

#define STRING_LENGTH_MAX 4096

typedef struct rstring{
	char* characters;
	size_t length;
} rstring;

size_t 		CalculateStringLength(char* string);
rstring		CreateString(char* characters);
void 		DeleteString(rstring* string);
rstring		CopyString(rstring* inputString);
int 		ConcatenateStrings(rstring* in_out_string, rstring* string2);
size_t 		FindFirstOccurrenceOf(char characterToFind, rstring* string);
int 		CompareCharacters(rstring* string1, rstring* string2);
int 		CompareCharactersCaseInsensitive(rstring* string1, rstring* string2);
int 		ExtractSubstring(rstring* in_out_string, size_t from, size_t to);
int 		ExtractLeftSubstring(rstring* in_out_string, size_t characterCount);
int 		ExtractRightSubstring(rstring* in_out_string, size_t characterCount);
int 		TrimString(rstring* in_out_string);
int 		TrimStringLeft(rstring* in_out_string);
int 		TrimStringRight(rstring* in_out_string);
int  		ConvertToUpperCase(rstring* in_out_string);
int  		ConvertToLowerCase(rstring* in_out_string);
int  		IsUpperCase(char c);
int  		IsLowerCase(char c);
int  		IsLetter(char c);
int  		IsDigit(char c);
int  		CalculateNumberOfLetters(rstring* string);
int  		CalculateNumberOfDigits(rstring* string);
int 	  	SplitStringByDelimiter(rstring* string, char delimiter, rstring* token);
int 		ReverseString(rstring* in_out_string);
int 		ConvertStringToInt(rstring* string, int* outputNumber);
int 		ConvertStringToFloat(rstring* string, float* outputNumber);