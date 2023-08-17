#include "rstrlib.h"

size_t CalculateStringLength(char* characters){
	if(!characters) return 0;
	size_t currentLength = 0;
	while(characters[currentLength] != '\0' && currentLength < STRING_LENGTH_MAX) currentLength++;
	return currentLength;
}

rstring CreateString(char* characters){
	if(!characters) return (rstring){0};

	rstring newString = {0};
	newString.length = CalculateStringLength(characters);
	if(newString.length == STRING_LENGTH_MAX) return (rstring){0};
	
	newString.characters = malloc(sizeof(char) * newString.length + 1);

	size_t currentIndex = 0;
	while(currentIndex < newString.length){
		newString.characters[currentIndex] = characters[currentIndex];
		currentIndex++;
	}
	newString.characters[currentIndex] = '\0';

	return newString;
}

rstring CreateStringInStack(char* characters){
	return (rstring){.characters = characters, .length = CalculateStringLength(characters)};
}

void DeleteString(rstring* string){
	if(string){
		free(string->characters);
		string->characters = NULL;
		string->length = 0;
	}
}

rstring CopyString(rstring* inputString){
	return !inputString ? (rstring){0} : CreateString(inputString->characters);
}

int ConcatenateStrings(rstring* in_out_string, rstring* string2){
	if(!in_out_string || !string2) return 0;
	in_out_string->characters = realloc(in_out_string->characters, in_out_string->length + string2->length + 1);
	if(!in_out_string->characters) return 0;

	size_t currentIndex = 0;
	while(currentIndex < string2->length){
		in_out_string->characters[in_out_string->length + currentIndex] = string2->characters[currentIndex];
		currentIndex++;
	}
	in_out_string->characters[in_out_string->length + string2->length] = '\0';
	in_out_string->length += string2->length;
	return 1;
}

size_t FindFirstOccurrenceOf(char characterToFind, rstring* string){
	if(!string || string->length == 0) return -1;

	size_t currentIndex = 0;
	while(currentIndex < string->length && string->characters[currentIndex] != '\0'){
		if(string->characters[currentIndex] == characterToFind) return currentIndex;
		currentIndex++;
	}
	return -1;
}

int IsCharactersInString(char characterToFind, rstring* string){
	return FindFirstOccurrenceOf(characterToFind, string) == (size_t)-1 ? 0 : 1;
}

int CompareStrings(rstring* string1, rstring* string2){
	if(!string1 || !string2 || string1->length != string2->length) return 0;

	size_t currentIndex = 0;
	while(currentIndex < string1->length){
		if(string1->characters[currentIndex] != string2->characters[currentIndex]) return 0;
		currentIndex++;
	}
	return 1;
}

int CompareStringToCStr(rstring* string1, char* string2){
	if(!string1 || !string2) return 0;

	size_t cStrSize = CalculateStringLength(string2);
	if(cStrSize != string1->length) return 0;

	size_t currentIndex = 0;
	while(currentIndex < string1->length){
		if(string1->characters[currentIndex] != string2[currentIndex]) return 0;
		currentIndex++;
	}
	return 1;
}

int CompareStringsCaseInsensitive(rstring* string1, rstring* string2){
	if(!string1 || !string2 || string1->length != string2->length) return 0;
	
	size_t currentIndex = 0;
	while(currentIndex < string1->length){
		char c1 = string1->characters[currentIndex];
		char c2 = string2->characters[currentIndex];
		if(c1 != c2 && c1 - 32 != c2 && c1 != c2 - 32) return 0;
		currentIndex++;
	}

	return 1;
}

int ExtractSubstring(rstring* in_out_string, size_t from, size_t to){
	if(!in_out_string || from > in_out_string->length || to > in_out_string->length || to < from) return 0;

	size_t finalLength = to - from + 1;
	size_t currentIndex = 0;
	while(currentIndex < finalLength){
		in_out_string->characters[currentIndex] = in_out_string->characters[currentIndex + from];
		currentIndex++;
	}
	in_out_string->characters[finalLength] = '\0';
	in_out_string->length = finalLength;
	return 1;
}

int ExtractLeftSubstring(rstring* in_out_string, size_t characterCount){
	return ExtractSubstring(in_out_string, 0, characterCount - 1);
}

int ExtractRightSubstring(rstring* in_out_string, size_t characterCount){
	return ExtractSubstring(in_out_string, in_out_string->length - characterCount, in_out_string->length - 1);
}

int TrimString(rstring* in_out_string){
	if(!in_out_string) return 0;

	size_t startIndex = 0;
	size_t endIndex = in_out_string->length - 1;
	while(in_out_string->characters[startIndex] == ' ' || in_out_string->characters[endIndex] == ' '){
		if(in_out_string->characters[startIndex] == ' ') startIndex++;
		if(in_out_string->characters[endIndex] 	 == ' ') endIndex--;
	}

	ExtractSubstring(in_out_string, startIndex, endIndex);
	return 1;
}

int TrimStringLeft(rstring* in_out_string){
	if(!in_out_string) return 0;

	size_t startIndex = 0;
	while(in_out_string->characters[startIndex] == ' ') startIndex++;

	ExtractSubstring(in_out_string, startIndex, in_out_string->length - 1);
	return 1;
}

int TrimStringRight(rstring* in_out_string){
	if(!in_out_string) return 0;

	size_t endIndex = in_out_string->length - 1;
	while(in_out_string->characters[endIndex] == ' ') endIndex--;

	ExtractSubstring(in_out_string, 0, endIndex);
	return 1;
}


int ConvertToUpperCase(rstring* in_out_string){
	if(!in_out_string) return 0;
	size_t currentIndex = 0;
	while(currentIndex < in_out_string->length){
		if(IsLowerCase(in_out_string->characters[currentIndex])) in_out_string->characters[currentIndex] -= 32;
		currentIndex++;
	}
	return 1;
}

int ConvertToLowerCase(rstring* in_out_string){
	if(!in_out_string) return 0;
	size_t currentIndex = 0;
	while(currentIndex < in_out_string->length){
		if(IsUpperCase(in_out_string->characters[currentIndex])) in_out_string->characters[currentIndex] += 32;
		currentIndex++;
	}
	return 1;
}

int IsUpperCase(char c){
	if('A' <= c && c <= 'Z') return 1;
	return 0;
}

int IsLowerCase(char c){
	if('a' <= c && c <= 'z') return 1;
	return 0;
}

int IsLetter(char c){
	if(IsUpperCase(c) || IsLowerCase(c)) return 1;
	return 0;
}

int IsDigit(char c){
	if('0' <= c && c <= '9') return 1;
	return 0;
}

int CalculateNumberOfLetters(rstring* string){
	if(!string) return 0;
	int count = 0;

	size_t currentIndex = 0;
	while(currentIndex < string->length){
		if(IsLetter(string->characters[currentIndex])) count++;
		currentIndex++;
	}

	return count;
}

int CalculateNumberOfDigits(rstring* string){
	if(!string) return 0;
	int count = 0;

	size_t currentIndex = 0;
	while(currentIndex < string->length){
		if(IsDigit(string->characters[currentIndex])) count++;
		currentIndex++;
	}

	return count;
}

int SplitStringByDelimiter(rstring* string, char delimiter, rstring* token){
	if(!string) return 0;

	size_t currentIndex = 0;
	while(string->characters[currentIndex] != delimiter && string->characters[currentIndex] != '\0') 
		currentIndex++;
	if(currentIndex < string->length - 1){
		if(currentIndex > token->length){
			token->characters = realloc(token->characters, currentIndex + 1);
			if(!token->characters) return 0;
		}
		//we don't need to reallocate if we want to shrink, just use the same buffer and terminate it with '\0'

		size_t copyIndex = 0;
		while(copyIndex < currentIndex){
			token->characters[copyIndex] = string->characters[copyIndex];
			copyIndex++;
		}
		token->characters[currentIndex] = '\0';
		token->length = currentIndex;
		ExtractSubstring(string, currentIndex + 1, string->length - 1);
		return 1;
	}
	token->characters = NULL;
	token->length = 0;
	return 0; //coudn't tokenize
}

int ReverseString(rstring* in_out_string){
	if(!in_out_string) return 0;
	if(in_out_string->length == 1 || in_out_string->length == 0) return 1;

	char aux = 0;
	size_t startIndex = 0;
	size_t endIndex = in_out_string->length - 1;

	while(startIndex < endIndex){
		aux = in_out_string->characters[startIndex];
		in_out_string->characters[startIndex] = in_out_string->characters[endIndex];
		in_out_string->characters[endIndex] = aux;
		startIndex++;
		endIndex--;
	}
	return 1;
}

int ConvertStringToInt(rstring* string, int* outputNumber){
	if(!string || !outputNumber) return 0;
	int r = sscanf(string->characters, "%i", outputNumber);
	if(r == -1 || r == 0){
		//failure or couldn't convert any bytes
		*outputNumber = 0;
		return 0;
	}
	return 1;
}

int ConvertStringToFloat(rstring* string, float* outputNumber){
	if(!string || !outputNumber) return 0;
	int r = sscanf(string->characters, "%f", outputNumber);
	if(r == -1 || r == 0){
		//failure
		*outputNumber = 0.0f;
		return 0;
	}
	return 1;
}
