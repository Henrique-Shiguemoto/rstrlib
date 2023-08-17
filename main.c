#include <stdio.h>
#include "rstrlib.h"

#define RSTRLIB_ASSERT(x); \
	if(!(x)){ fprintf(stderr, "ASSERTION FAILED AT: LINE %d - FILE %s\n", __LINE__, __FILE__); exit(1); }

int main(int argc, const char *argv[]){
	// Creating strings (characters in ASCII are supported only)
	
	// passing a non-const char* like this makes it possible to change the characters while being on the stack
	char* s_buffer = "Hello";
	rstring r = CreateStringInStack(s_buffer); 

	// passing a string literal like this make it impossible to change the characters in the array (because it is a const char*)	
	//		it's pretty much just a constant
	rstring s = CreateStringInStack("Stack Allocation"); 
	rstring s0 = CreateStringInStack(NULL);
	
	rstring s1 = CreateString("Heap Allocation");

	// or just char buffers (maybe map a file? which isn't very big lul) (since this isn't a const char*, you can change the characters)
	char* c_buffer = "yy";
	rstring s2 = CreateString(c_buffer);
	rstring s3 = CreateString("");
	rstring s4 = CreateString("AHSOANONQ WDNJNDOAA_DKWNDE DIADNEU[.NDAOKSAPSDU9A SAKMSASMA^CAIENFAOIC]NACASASK");

	// Calculating characters array size
	RSTRLIB_ASSERT(CalculateStringLength(r.characters) == 5);
	RSTRLIB_ASSERT(CalculateStringLength(s.characters) == 16);
	RSTRLIB_ASSERT(CalculateStringLength(s0.characters) == 0);
	RSTRLIB_ASSERT(CalculateStringLength(s1.characters) == 15);
	RSTRLIB_ASSERT(CalculateStringLength(s2.characters) == 2);
	RSTRLIB_ASSERT(CalculateStringLength(s3.characters) == 0);
	RSTRLIB_ASSERT(CalculateStringLength(s4.characters) == 79);

	// Every string created by CreateString needs to be deleted
	// Stack allocated rstrings don't need to be deallocated (duh)
	DeleteString(&s1); 
	DeleteString(&s2);
	DeleteString(&s3);
	DeleteString(&s4);

// ----------------------------------------------------------------------------------------------------------------

	// Copying strings
	rstring s5 = CreateString("brown fox jumps over the lazy dog");
	rstring s5_copy = CopyString(&s5);

	// Comparing an rstring and its copy (same length and characters)
	RSTRLIB_ASSERT(s5.length == s5_copy.length);
	RSTRLIB_ASSERT(CompareStrings(&s5, &s5_copy));

	// Copies also need to be deleted
	DeleteString(&s5);
	DeleteString(&s5_copy);

// ----------------------------------------------------------------------------------------------------------------

	// Concatenating strings
	rstring s6 = CreateString("Hello ");
	rstring s7 = CreateString("World");
	ConcatenateStrings(&s6, &s7); // first parameter gets changed

	RSTRLIB_ASSERT(CompareStrings(&s6, &(rstring){.characters = "Hello World", .length = 11}));

	DeleteString(&s6);
	DeleteString(&s7);

// ----------------------------------------------------------------------------------------------------------------

	// Character looking
	rstring s8 = CreateStringInStack("a b c d e f g h i j k l m n o p q r s t u v w x y z A B C D E F G H I J K L M N O P Q R S T U V W X Y Z");
	
	RSTRLIB_ASSERT(FindFirstOccurrenceOf('a', &s8) == 0);
	RSTRLIB_ASSERT(FindFirstOccurrenceOf('Z', &s8) == 102);
	RSTRLIB_ASSERT(FindFirstOccurrenceOf('#', &s8) == (size_t)-1); //-1 for size_t is the maximum value of size_t because of wrapping
	RSTRLIB_ASSERT(FindFirstOccurrenceOf(' ', &s8) == 1);
	RSTRLIB_ASSERT(FindFirstOccurrenceOf('Q', &s8) == 84);
	RSTRLIB_ASSERT(FindFirstOccurrenceOf('B', NULL) == (size_t)-1);

	RSTRLIB_ASSERT(IsCharactersInString('Q', &s8));
	RSTRLIB_ASSERT(IsCharactersInString('f', &s8));
	RSTRLIB_ASSERT(!IsCharactersInString('?', &s8));

// ----------------------------------------------------------------------------------------------------------------

	// Comparing strings
	rstring s9 = CreateString("RSTRLIB.C");
	rstring s10 = CreateString("RSTRLIB.H");
	rstring s11 = CreateString("RSTRLIB.C");
	rstring s12 = CreateString("rstrlib.h");
	rstring s13 = CreateString("RsTrLiB.C");
	
	RSTRLIB_ASSERT(CompareStrings(&s9, &s11));
	RSTRLIB_ASSERT(CompareStrings(&s12, &s12));
	RSTRLIB_ASSERT(!CompareStrings(&s9, &s10));
	RSTRLIB_ASSERT(!CompareStrings(&s10, &s11));
	RSTRLIB_ASSERT(!CompareStrings(NULL, &s12));
	RSTRLIB_ASSERT(!CompareStrings(NULL, NULL));
	RSTRLIB_ASSERT(CompareStringsCaseInsensitive(&s10, &s12));
	RSTRLIB_ASSERT(CompareStringsCaseInsensitive(&s9, &s13));
	RSTRLIB_ASSERT(!CompareStringsCaseInsensitive(&s9, NULL));
	RSTRLIB_ASSERT(!CompareStringsCaseInsensitive(NULL, NULL));
	RSTRLIB_ASSERT(CompareStringToCStr(&s10, "RSTRLIB.H"));
	RSTRLIB_ASSERT(!CompareStringToCStr(&s12, "rstrlib.hpp"));
	RSTRLIB_ASSERT(!CompareStringToCStr(&s13, NULL));
	RSTRLIB_ASSERT(!CompareStringToCStr(NULL, "Hello"));

	DeleteString(&s9);
	DeleteString(&s10);
	DeleteString(&s11);
	DeleteString(&s12);
	DeleteString(&s13);

// ----------------------------------------------------------------------------------------------------------------

	// Extracting substrings
	rstring s14 = CreateString("If You Can't Stand the Heat, Get Out of the Kitchen!");
	ExtractSubstring(&s14, 7, 35); // parameter gets changed
	RSTRLIB_ASSERT(CompareStrings(&s14, &(rstring){.characters = "Can't Stand the Heat, Get Out", .length = 29}));

	ExtractLeftSubstring(&s14, 20); // parameter gets changed
	RSTRLIB_ASSERT(CompareStrings(&s14, &(rstring){.characters = "Can't Stand the Heat", .length = 20}));

	ExtractRightSubstring(&s14, 4); // parameter gets changed
	RSTRLIB_ASSERT(CompareStrings(&s14, &(rstring){.characters = "Heat", .length = 4}));

	DeleteString(&s14);

// ----------------------------------------------------------------------------------------------------------------

	// Trimming strings
	rstring s15 = CreateString(" a ");
	rstring s16 = CreateString(" Rick   ");
	rstring s17 = CreateString("      Hello World  ");
	
	TrimString(&s15);
	TrimStringLeft(&s16);
	TrimStringRight(&s17);

	RSTRLIB_ASSERT(CompareStrings(&s15, &(rstring){.characters = "a", .length = 1}));
	RSTRLIB_ASSERT(CompareStrings(&s16, &(rstring){.characters = "Rick   ", .length = 7}));
	RSTRLIB_ASSERT(CompareStrings(&s17, &(rstring){.characters = "      Hello World", .length = 17}));

	DeleteString(&s15);
	DeleteString(&s16);
	DeleteString(&s17);

// ----------------------------------------------------------------------------------------------------------------

	// Converting strings

	rstring s18 = CreateString("lower case words");
	rstring s19 = CreateString("UPPER CASE WORDS");

	ConvertToUpperCase(&s18);
	ConvertToLowerCase(&s19);

	RSTRLIB_ASSERT(CompareStrings(&s18, &(rstring){.characters = "LOWER CASE WORDS", .length = 16}));
	RSTRLIB_ASSERT(CompareStrings(&s19, &(rstring){.characters = "upper case words", .length = 16}));

	DeleteString(&s18);
	DeleteString(&s19);

	rstring s20 = CreateString("10029384");
	rstring s21 = CreateString("3.1415");
	rstring s22 = CreateString("random");
	int integer = 0;
	float decimal = 0.0f;

	ConvertStringToInt(&s20, &integer);
	RSTRLIB_ASSERT(integer == 10029384);

	ConvertStringToFloat(&s21, &decimal);
	RSTRLIB_ASSERT(decimal == 3.1415f);

	int result_int = ConvertStringToInt(&s22, &integer);
	RSTRLIB_ASSERT(integer == 0 && result_int == 0); // 0 means failure

	float result_float = ConvertStringToFloat(&s22, &decimal);
	RSTRLIB_ASSERT(decimal == 0.0f && result_float == 0); // 0 means failure

	DeleteString(&s20);
	DeleteString(&s21);
	DeleteString(&s22);

// ----------------------------------------------------------------------------------------------------------------

	// Getting Information about Characters
	rstring s23 = CreateString("Hello World 123");

	RSTRLIB_ASSERT(IsUpperCase(s23.characters[0]));
	RSTRLIB_ASSERT(!IsUpperCase(s23.characters[1]));
	RSTRLIB_ASSERT(IsLowerCase(s23.characters[8]));
	RSTRLIB_ASSERT(!IsLowerCase(s23.characters[6]));
	RSTRLIB_ASSERT(IsLetter(s23.characters[10]));
	RSTRLIB_ASSERT(!IsLowerCase(s23.characters[6]));
	RSTRLIB_ASSERT(IsDigit(s23.characters[s23.length - 1]));
	RSTRLIB_ASSERT(!IsDigit(s23.characters[3]));

	DeleteString(&s23);

// ----------------------------------------------------------------------------------------------------------------

	// Counting Characters
	rstring s24 = CreateString("HDGAT452HD649J1BSA6184DDAKA");
	rstring s25 = CreateString("9");
	rstring s26 = CreateString("aaa");

	RSTRLIB_ASSERT(CalculateNumberOfLetters(&s24) == 16);
	RSTRLIB_ASSERT(CalculateNumberOfDigits(&s24)  == 11);
	RSTRLIB_ASSERT(CalculateNumberOfLetters(&s25) == 0);
	RSTRLIB_ASSERT(CalculateNumberOfDigits(&s25)  == 1);
	RSTRLIB_ASSERT(CalculateNumberOfLetters(&s26) == 3);
	RSTRLIB_ASSERT(CalculateNumberOfDigits(&s26)  == 0);

	DeleteString(&s24);
	DeleteString(&s25);
	DeleteString(&s26);

// ----------------------------------------------------------------------------------------------------------------

	// Splitting / Tokenizing strings

	rstring s27 = CreateString("#include<stdio.h>\nint main(void){\nreturn 0;\n}");
	rstring token = {0};

	SplitStringByDelimiter(&s27, '\n', &token);
	RSTRLIB_ASSERT(CompareStrings(&token, &(rstring){.characters = "#include<stdio.h>", .length = 17}));
	RSTRLIB_ASSERT(CompareStrings(&s27, &(rstring){.characters = "int main(void){\nreturn 0;\n}", .length = 27}));

	SplitStringByDelimiter(&s27, '\n', &token);
	RSTRLIB_ASSERT(CompareStrings(&token, &(rstring){.characters = "int main(void){", .length = 15}));
	RSTRLIB_ASSERT(CompareStrings(&s27, &(rstring){.characters = "return 0;\n}", .length = 11}));

	SplitStringByDelimiter(&s27, '\n', &token);
	RSTRLIB_ASSERT(CompareStrings(&token, &(rstring){.characters = "return 0;", .length = 9}));
	RSTRLIB_ASSERT(CompareStrings(&s27, &(rstring){.characters = "}", .length = 1}));

	SplitStringByDelimiter(&s27, '\n', &token);
	RSTRLIB_ASSERT(CompareStrings(&token, &(rstring){.characters = NULL, .length = 0})); // delimiter couldn't be found, so it is zero-initialized
	RSTRLIB_ASSERT(CompareStrings(&s27, &(rstring){.characters = "}", .length = 1}));

	DeleteString(&s27);
	DeleteString(&token);

// ----------------------------------------------------------------------------------------------------------------

	// Reversing strings

	rstring s28 = CreateString("Hello World");
	rstring s29 = CreateString("");
	rstring s30 = CreateString("a");
	
	ReverseString(&s28);
	ReverseString(&s29);
	ReverseString(&s30);
	RSTRLIB_ASSERT(CompareStrings(&s28, &(rstring){.characters = "dlroW olleH", .length = 11}));
	RSTRLIB_ASSERT(CompareStrings(&s29, &(rstring){.characters = "", .length = 0}));
	RSTRLIB_ASSERT(CompareStrings(&s30, &(rstring){.characters = "a", .length = 1}));

	DeleteString(&s28);
	DeleteString(&s29);
	DeleteString(&s30);

	return 0;
}