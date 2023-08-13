#include <stdio.h>
#include "rstrlib.h"

void PrintString(rstring* string){
	printf("Characters: %s\n", string->characters);
	printf("Length: %llu\n", string->length);
	printf("Capacity: %llu\n", string->capacity);
}

int main(int argc, char const *argv[]){
	printf("sizeof(rstring) = %llu\n", sizeof(rstring));
	return 0;
}