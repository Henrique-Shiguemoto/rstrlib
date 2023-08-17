#ifndef RSTRLIB_H
#define RSTRLIB_H

#include <stdlib.h>
#include <stdio.h>

#define STRING_LENGTH_MAX 4096

typedef struct rstring{
	char* characters; // assumed to have a null byte at the end
	size_t length;    // null byte not counted
} rstring;

/**
 * 
 * Calculates the number of characters in a string.
 * In case NULL is passed as a parameter, 0 is returned.
 * 
 * */
size_t 		CalculateStringLength(char* string);

/**
 * 
 * Returns a newly created rstring structure with information according to the "characters" parameter.
 * In case NULL is passed as a parameter, a zero-initialized rstring structure is returned.
 * 
 * It is necessary to call DeleteString() after the rstring structure isn't in use anymore.
 * 
 * */
rstring		CreateString(char* characters);

/**
 * 
 * Deletes an rstring structure from memory.
 * In case NULL is passed as a parameter, nothing happens.
 * 
 * */
void 		DeleteString(rstring* string);

/**
 * 
 * Copies the contents of the "inputString" parameter to a new created rstring structure, then returns this structure.
 * In case NULL is passed as a parameter, a zero-initialized rstring structure is returned.
 * 
 * It is necessary to call DeleteString() after the rstring structure isn't in use anymore.
 * 
 * */
rstring		CopyString(rstring* inputString);

/**
 * 
 * Copies the characters from "string2" parameter to the "in_out_string" characters array, then returns 1.
 * In case NULL is passed as a parameter, 0 is returned.
 * 
 * */
int 		ConcatenateStrings(rstring* in_out_string, rstring* string2);

/**
 * 
 * Returns the first index in which "characterToFind" is in the characters array from the "string" parameter.
 * In case NULL is passed as a parameter, -1 (max size_t value because of wrapping).
 * 
 * */
size_t 		FindFirstOccurrenceOf(char characterToFind, rstring* string);

/**
 * 
 * Returns 1 if "characterToFind" is located in the "characters" array of "string", 0 otherwise.
 * 
 * */
int         IsCharactersInString(char characterToFind, rstring* string);

/**
 * 
 * Compares lengths and characters from both parameters, returns 1 on match.
 * In case NULL is passed as a parameter, 0 is returned.
 * 
 * */
int 		CompareStrings(rstring* string1, rstring* string2);

/**
 * 
 * Compares lengths and characters from both parameters, returns 1 on match.
 * In case NULL is passed as a parameter, 0 is returned.
 * 
 * */
int         CompareStringToCStr(rstring* string1, char* string2);

/**
 * 
 * Compares lengths and characters from both parameters (characters may be in different cases), returns 1 on match.
 * In case NULL is passed as a parameter, 0 is returned.
 * 
 * */
int 		CompareStringsCaseInsensitive(rstring* string1, rstring* string2);

/**
 * 
 * Changes the "in_out_string" struct with only the characters in the "characters" array from the index "from" to the index "to", then returns 1.
 * In case NULL is passed as a parameter, 0 is returned.
 * 
 * */
int 		ExtractSubstring(rstring* in_out_string, size_t from, size_t to);

/**
 * 
 * Changes the "in_out_string" struct with only with the first "characterCount" characters in the "characters" array, then returns 1.
 * In case NULL is passed as a parameter, 0 is returned.
 * 
 * */
int 		ExtractLeftSubstring(rstring* in_out_string, size_t characterCount);

/**
 * 
 * Changes the "in_out_string" struct with only with the last "characterCount" characters in the "characters" array, then returns 1.
 * In case NULL is passed as a parameter, 0 is returned.
 * 
 * */
int 		ExtractRightSubstring(rstring* in_out_string, size_t characterCount);

/**
 * 
 * Changes the "in_out_string" struct without whitespaces in the start and the end, then it returns 1.
 * In case NULL is passed as a parameter, 0 is returned.
 * 
 * */
int 		TrimString(rstring* in_out_string);

/**
 * 
 * Changes the "in_out_string" struct without whitespaces in the start, then it returns 1.
 * In case NULL is passed as a parameter, 0 is returned.
 * 
 * */
int 		TrimStringLeft(rstring* in_out_string);

/**
 * 
 * Changes the "in_out_string" struct without whitespaces in the end, then it returns 1.
 * In case NULL is passed as a parameter, 0 is returned.
 * 
 * */
int 		TrimStringRight(rstring* in_out_string);

/**
 * 
 * Changes the "in_out_string" struct with all lower case letter changed to upper case letters, then it returns 1.
 * In case NULL is passed as a parameter, 0 is returned.
 * 
 * */
int  		ConvertToUpperCase(rstring* in_out_string);

/**
 * 
 * Changes the "in_out_string" struct with all upper case letters changed to lower case letters, then it returns 1.
 * In case NULL is passed as a parameter, 0 is returned.
 * 
 * */
int  		ConvertToLowerCase(rstring* in_out_string);

/**
 * 
 * Returns 1 if it's an upper case letter, 0 otherwise.
 * 
 * */
int  		IsUpperCase(char c);

/**
 * 
 * Returns 1 if it's a lower case letter, 0 otherwise.
 * 
 * */
int  		IsLowerCase(char c);

/**
 * 
 * Returns 1 if it's a letter, 0 otherwise.
 * 
 * */
int  		IsLetter(char c);

/**
 * 
 * Returns 1 if it's a digit (0 through 9), 0 otherwise.
 * 
 * */
int  		IsDigit(char c);

/**
 * 
 * Returns the number of letters in the characters field of the "string" parameter.
 * In case NULL is passed as a parameter, 0 is returned.
 * 
 * */
int  		CalculateNumberOfLetters(rstring* string);

/**
 * 
 * Returns the number of digits in the characters field of the "string" parameter.
 * In case NULL is passed as a parameter, 0 is returned.
 * 
 * */
int  		CalculateNumberOfDigits(rstring* string);

/**
 * 
 * Tokenizes the "string" struct by "delimiter" (saves the token into "token") and leaves the rest of the characters in "string", then returns 1.
 * In case NULL is passed as a parameter, 0 is returned.
 * In case the delimiter isn't found in the "string" parameter, 0 is returned.
 * 
 * It is necessary to call DeleteString() after the rstring structure isn't in use anymore.
 * 
 * */
int 	  	SplitStringByDelimiter(rstring* string, char delimiter, rstring* token);

/**
 * 
 * Reverses the "in_out_string" characters array, then it returns 1.
 * In case NULL is passed as a parameter (string or outputNumber), 0 is returned.
 * 
 * */
int 		ReverseString(rstring* in_out_string);

/**
 * 
 * Tries to convert the characters array from "string" to an integer and store it in "outputNumber".
 * In case NULL is passed as a parameter (string or outputNumber), 0 is returned.
 * In case the conversion couldn't be made (malformed string), 0 is returned.
 * 
 * */
int 		ConvertStringToInt(rstring* string, int* outputNumber);

/**
 * 
 * Tries to convert the characters array from "string" to a float and store it in "outputNumber".
 * In case NULL is passed as a parameter (string or outputNumber), 0 is returned.
 * In case the conversion couldn't be made (malformed string), 0 is returned.
 * 
 * */
int 		ConvertStringToFloat(rstring* string, float* outputNumber);



#endif // RSTRLIB_H