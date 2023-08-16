#include <stdio.h>
#include "rstrlib.h"

void PrintString(rstring* string){
	printf("Characters: %s | ", string->characters);
	printf("Length: %llu\n", string->length);
}

void PrintEveryCharacter(rstring* string){
	size_t currentIndex = 0;
	while(currentIndex < string->length) printf("'%c'\t", string->characters[currentIndex++]);
	printf("\n");
}

int main(int argc, const char *argv[]){
	rstring r = CreateString("Hello World");
	PrintString(&r);
	PrintEveryCharacter(&r);
	DeleteString(&r);
	return 0;
}