#include <stdio.h>
#include "rstrlib.h"

void PrintString(rstring* string){
	printf("Characters: %s\n", string->characters);
	printf("Length: %llu\n", string->length);
	printf("Capacity: %llu\n", string->capacity);
}

void PrintEveryCharacter(rstring* string){
	size_t currentIndex = 0;
	while(currentIndex < string->length){
		printf("'%c'\t", string->characters[currentIndex]);
		currentIndex++;
	}
}

int main(int argc, char const *argv[]){
	rstring* first_string = CreateString("Hello World", 15);
	rstring* r = ExtractRightSubstring(first_string, 5);
	rstring* l = ExtractLeftSubstring(first_string, 5);
	
	PrintString(first_string);
	PrintString(r);
	PrintString(l);
	PrintEveryCharacter(r);
	PrintEveryCharacter(l);

	DeleteString(first_string);
	DeleteString(r);
	DeleteString(l);
	return 0;
}