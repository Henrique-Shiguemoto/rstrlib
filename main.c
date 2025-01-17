#include "rstrlib.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define RS_ASSERT(x) do { if(!(x)) { printf("\nERROR: %s assertion failed! (%s:%i)\n\n", (#x), __FILE__, __LINE__); exit(1); } } while(0)

int main(void){
	printf("\nTest CREATING, SETTING AND DELETING STRINGS...\n");
	{
		// Every time you use rs_create, you'll have to call rs_delete
		rs_string s0 = rs_create("Hello World\n");
		RS_ASSERT(s0.length == 12); 
		RS_ASSERT(memcmp(s0.buffer, "Hello World\n", s0.length) == 0);
		rs_delete(&s0);
		
		rs_string s1 = rs_create("");
		RS_ASSERT(s1.length == 0); 
		RS_ASSERT(memcmp(s1.buffer, "", s1.length) == 0);
		rs_set(&s1, "RSTRLIB");
		RS_ASSERT(s1.length == 7); 
		RS_ASSERT(memcmp(s1.buffer, "RSTRLIB", s1.length) == 0);
		rs_delete(&s1);
		
		rs_string s2 = rs_create(NULL); // same as (rs_string){0} or {0}
		RS_ASSERT(s2.length == 0); 
		RS_ASSERT(memcmp(s2.buffer, NULL, s2.length) == 0);
		rs_delete(&s2);
		
		rs_string s3 = rs_create("A brown fox jumps over the lazy dog");
		RS_ASSERT(s3.length == 35); 
		RS_ASSERT(memcmp(s3.buffer, "A brown fox jumps over the lazy dog", s3.length) == 0);
		rs_set(&s3, ""); // can clear strings
		RS_ASSERT(s3.length == 0);
		RS_ASSERT(memcmp(s3.buffer, "", s3.length) == 0); // not necessary
		rs_delete(&s3);
	}
	printf("Test CREATING, SETTING AND DELETING STRINGS finished...\n");

	printf("\nTest COPYING STRINGS...\n");
	{
		// You'll also need to call rs_delete whenever you call rs_copy
		rs_string s0 = rs_create("Test String");
		rs_string s1 = rs_create(NULL);
		int result_copy_0 = rs_copy(&s0, &s1);
		RS_ASSERT(result_copy_0 == RS_SUCCESS);
		RS_ASSERT(s0.length == s1.length);
		RS_ASSERT(memcmp(s0.buffer, s1.buffer, s0.length) == 0);
		rs_delete(&s0);
		rs_delete(&s1);

		rs_string s2 = rs_create("Hello World\n");
		rs_string s3 = rs_create("AAAAAAAAAAAAAA");
		int result_copy_1 = rs_copy(&s2, &s3); // you'll lose the previous content from the second argument
		RS_ASSERT(result_copy_1 == RS_SUCCESS); 
		RS_ASSERT(s2.length == s3.length); 
		RS_ASSERT(memcmp(s2.buffer, s3.buffer, s2.length) == 0);
		rs_delete(&s2);
		rs_delete(&s3);

		rs_string s4 = rs_create(NULL);
		rs_string s5 = rs_create("Hello");
		int result_copy_2 = rs_copy(&s4, &s5); // if it fails, the destination's contents will be preserved
		RS_ASSERT(result_copy_2 == RS_FAILURE); 
		RS_ASSERT(s4.length != s5.length); 
		RS_ASSERT(s4.buffer == NULL); 
		RS_ASSERT(memcmp(s5.buffer, "Hello", s5.length) == 0);
		rs_delete(&s4);
		rs_delete(&s5);

		rs_string s6 = rs_create("Some test string\n\n\t\t\r\r Hello");
		char buffer[256] = {0};
		char buffer1[4] = {0};
		int result_copy_3 = rs_copy_to_cstr(&s6, buffer, 256);
		int result_copy_4 = rs_copy_to_cstr(&s6, buffer1, 4);
		RS_ASSERT(result_copy_3 == RS_SUCCESS);
		RS_ASSERT((int)strlen(buffer) == s6.length);
		RS_ASSERT(memcmp(buffer, s6.buffer, s6.length) == 0);
		RS_ASSERT(result_copy_4 == RS_FAILURE); // destination HAS to be at least the same size as source
		RS_ASSERT((int)strlen(buffer1) < s6.length);
		RS_ASSERT(memcmp(buffer1, s6.buffer, 4) != 0);
		rs_delete(&s6);
	}
	printf("Test COPYING STRINGS finished...\n");

	printf("\nTest CONCATENATING STRINGS...\n");
	{
		rs_string s0 = rs_create("Hello ");
		rs_string s1 = rs_create("World\n");
		int result_concat_0 = rs_concatenate(&s0, &s1); // For concatenations, the first parameters changes but the second stays the same
		RS_ASSERT(result_concat_0 == RS_SUCCESS);
		RS_ASSERT(s0.length == 12);
		RS_ASSERT(memcmp(s0.buffer, "Hello World\n", s0.length) == 0);
		RS_ASSERT(s1.length == 6);
		RS_ASSERT(memcmp(s1.buffer, "World\n", s1.length) == 0);
		rs_delete(&s0);
		rs_delete(&s1);

		rs_string s2 = rs_create("");
		rs_string s3 = rs_create("RSTRLIB");
		int result_concat_1 = rs_concatenate(&s2, &s3);
		RS_ASSERT(result_concat_1 == RS_SUCCESS);
		RS_ASSERT(s2.length == 7);
		RS_ASSERT(memcmp(s2.buffer, "RSTRLIB", s2.length) == 0);
		RS_ASSERT(s3.length == 7);
		RS_ASSERT(memcmp(s3.buffer, "RSTRLIB", s3.length) == 0);
		rs_delete(&s2);
		rs_delete(&s3);

		rs_string s4 = rs_create(NULL);
		int result_concat_2 = rs_concatenate(&s4, NULL); // if either the buffer is NULL (e.g.: rs_create(NULL)) or either parameter is NULL, the function fails
		RS_ASSERT(result_concat_2 == RS_FAILURE);
		RS_ASSERT(s4.length == 0);
		RS_ASSERT(s4.buffer == NULL);
		rs_delete(&s4);

		rs_string s5 = rs_create("abcdefg");
		rs_string s6 = rs_create("");
		int result_concat_3 = rs_concatenate(&s5, &s6); // nothing changes to s5
		RS_ASSERT(result_concat_3 == RS_SUCCESS);
		RS_ASSERT(s5.length == 7);
		RS_ASSERT(memcmp(s5.buffer, "abcdefg", s5.length) == 0);
		RS_ASSERT(s6.length == 0);
		RS_ASSERT(memcmp(s6.buffer, "", s6.length) == 0); // not necessary
		rs_delete(&s5);
		rs_delete(&s6);
	}
	printf("Test CONCATENATING STRINGS finished...\n");

	printf("\nTest SEARCHING CHARACTERS AND SUBSTRINGS...\n");
	{
		rs_string s0 = rs_create("Hello World112344 yyyy\n");
		RS_ASSERT(rs_is_char_in_string(&s0, 'W'));
		RS_ASSERT(rs_is_char_in_string(&s0, '\n'));
		RS_ASSERT(rs_is_char_in_string(&s0, ' '));
		RS_ASSERT(rs_is_char_in_string(&s0, 'H'));
		RS_ASSERT(rs_is_char_in_string(&s0, 'd'));
		RS_ASSERT(!rs_is_char_in_string(&s0, 'k'));
		RS_ASSERT(!rs_is_char_in_string(&s0, ';'));
		RS_ASSERT(rs_first_char_occurrence(&s0, 'H') == 0);
		RS_ASSERT(rs_first_char_occurrence(&s0, 'l') == 2); // not 3 nor 9, these aren't the first ocurrence
		RS_ASSERT(rs_first_char_occurrence(&s0, '\n') == s0.length - 1);
		RS_ASSERT(rs_first_char_occurrence(&s0, ' ') == 5);
		RS_ASSERT(rs_first_char_occurrence(&s0, 'w') == -1);
		RS_ASSERT(rs_first_char_occurrence(&s0, 'P') == -1);
		RS_ASSERT(rs_first_substring_ocurrence(&s0, "Hello") == 0);
		RS_ASSERT(rs_first_substring_ocurrence(&s0, "234") == 13);
		RS_ASSERT(rs_first_substring_ocurrence(&s0, "yy") == 18);
		RS_ASSERT(rs_first_substring_ocurrence(&s0, "\n") == 22);
		RS_ASSERT(rs_count_letters(&s0) == 14);
		RS_ASSERT(rs_count_digits(&s0) == 6);
		RS_ASSERT(rs_count_character(&s0, 'H') == 1);
		RS_ASSERT(rs_count_character(&s0, 'l') == 3);
		RS_ASSERT(rs_count_character(&s0, 'o') == 2);
		RS_ASSERT(rs_count_character(&s0, '-') == 0);
		RS_ASSERT(rs_count_substring(&s0, "World") == 1);
		RS_ASSERT(rs_count_substring(&s0, "yy") == 2);
		RS_ASSERT(rs_count_substring(&s0, "Hell") == 1);
		RS_ASSERT(rs_count_substring(&s0, "   ") == 0);
		rs_delete(&s0);

		rs_string s1 = rs_create(NULL); // Here s1.length == 0 and s1.buffer == NULL
		rs_string s2 = rs_create(""); 	// Here s2.length == 0 and s2.buffer != NULL
		RS_ASSERT(rs_is_char_in_string(&s1, 'A') == RS_FAILURE); // all these tests should fail
		RS_ASSERT(rs_is_char_in_string(&s1, ' ') == RS_FAILURE);
		RS_ASSERT(rs_is_char_in_string(&s1, '0') == RS_FAILURE);
		RS_ASSERT(rs_is_char_in_string(&s2, '\0') == RS_FAILURE);
		RS_ASSERT(rs_is_char_in_string(&s2, ' ') == RS_FAILURE);
		RS_ASSERT(rs_is_char_in_string(&s2, '0') == RS_FAILURE);
		RS_ASSERT(rs_count_letters(&s1) == -1);
		RS_ASSERT(rs_count_letters(&s2) == 0);
		RS_ASSERT(rs_count_digits(&s1) == -1);
		RS_ASSERT(rs_count_digits(&s2) == 0);
		RS_ASSERT(rs_count_character(&s1, '\0') == 0);
		RS_ASSERT(rs_count_character(&s2, '\0') == 0);
		RS_ASSERT(rs_count_substring(&s1, "Hello") == 0);
		RS_ASSERT(rs_count_substring(&s2, "Hello") == 0);
		RS_ASSERT(rs_first_char_occurrence(&s1, 'N') == -1); // all these tests should fail
		RS_ASSERT(rs_first_char_occurrence(&s1, '\n') == -1);
		RS_ASSERT(rs_first_char_occurrence(&s1, '\0') == -1);
		RS_ASSERT(rs_first_char_occurrence(&s2, '\0') == -1);
		RS_ASSERT(rs_first_char_occurrence(&s2, ' ') == -1);
		RS_ASSERT(rs_first_char_occurrence(&s2, '0') == -1);
		RS_ASSERT(rs_first_substring_ocurrence(&s1, "Hello") == -1); // if buffer is NULL, it returns -1
		RS_ASSERT(rs_first_substring_ocurrence(&s2, "234") == -1); // if length is 0, it returns -1
		rs_delete(&s1);
		rs_delete(&s2);
	}
	printf("Test SEARCHING CHARACTERS AND SUBSTRINGS finished...\n");

	printf("\nTest COMPARING STRINGS...\n");
	{
		rs_string s6 = rs_create("Henrique Shiguemoto Felizardo\n");
		rs_string s7 = rs_create("Henrique Shiguemoto Felizardo\n");
		rs_string s8 = rs_create("Henrique SHIGUEMOTO Felizardo\n");
		rs_string s9 = rs_create("henrique shiguemoto felizardo\n");
		rs_string s10 = rs_create("Henrique S. Felizardo\n");

		char* buffer = "Henrique Shiguemoto Felizardo\n";
		RS_ASSERT(rs_compare(&s6, &s7) == RS_SUCCESS);
		RS_ASSERT(rs_compare(&s6, &s8) == RS_FAILURE);
		RS_ASSERT(rs_compare(&s7, &s9) == RS_FAILURE);
		RS_ASSERT(rs_compare(&s6, &s10) == RS_FAILURE);
		RS_ASSERT(rs_compare_to_cstr(&s6, "Henrique Shiguemoto Felizardo\n") == RS_SUCCESS);
		RS_ASSERT(rs_compare_to_cstr(&s7, buffer) == RS_SUCCESS);
		RS_ASSERT(rs_compare_to_cstr(&s8, "HENRIQUE SHIGUEMOTO FELIZARDO\n") == RS_FAILURE);
		RS_ASSERT(rs_compare_case_insensitive(&s6, &s8) == RS_SUCCESS);
		RS_ASSERT(rs_compare_case_insensitive(&s7, &s9) == RS_SUCCESS);
		RS_ASSERT(rs_compare_case_insensitive(&s8, &s10) == RS_FAILURE);
		RS_ASSERT(rs_compare_to_cstr_case_insensitive(&s6, s8.buffer) == RS_SUCCESS);
		RS_ASSERT(rs_compare_to_cstr_case_insensitive(&s9, buffer) == RS_SUCCESS);
		RS_ASSERT(rs_compare_to_cstr_case_insensitive(&s8, "henrique s. felizardo\n") == RS_FAILURE);

		rs_delete(&s6);
		rs_delete(&s7);
		rs_delete(&s8);
		rs_delete(&s9);
		rs_delete(&s10);
	}
	printf("Test COMPARING STRINGS finished...\n");

	printf("\nTest EXTRACTING SUBSTRINGS...\n");
	{
		rs_string s0 = rs_create("A brown fox jumps over the lazy dog");
		rs_string s1 = rs_create("111222333");
		rs_string s2 = rs_create("");
		rs_string s3 = rs_create(NULL);
		rs_string s4 = rs_create("Hello World\n");
		RS_ASSERT(rs_extract(&s0, 0, 15) == RS_SUCCESS); // Index 15 is included in the result
		RS_ASSERT(s0.length == 16);
		RS_ASSERT(memcmp(s0.buffer, "A brown fox jump", s0.length) == 0);
		RS_ASSERT(rs_extract(&s0, 5, 10) == RS_SUCCESS); // Index 10 is included in the result
		RS_ASSERT(s0.length == 6);
		RS_ASSERT(memcmp(s0.buffer, "wn fox", s0.length) == 0);

		RS_ASSERT(rs_extract_left(&s1, 7) == RS_SUCCESS);
		RS_ASSERT(s1.length == 7);
		RS_ASSERT(memcmp(s1.buffer, "1112223", s1.length) == 0);
		RS_ASSERT(rs_extract_right(&s1, 5) == RS_SUCCESS);
		RS_ASSERT(s1.length == 5);
		RS_ASSERT(memcmp(s1.buffer, "12223", s1.length) == 0);
		RS_ASSERT(rs_remove_delimiter(&s1, '2') == RS_SUCCESS);
		RS_ASSERT(s1.length == 2);
		RS_ASSERT(memcmp(s1.buffer, "13", s1.length) == 0);

		RS_ASSERT(rs_extract(&s2, 0, 1) == RS_FAILURE); // If buffer is empty, then it fails
		RS_ASSERT(rs_extract(&s3, 0, 1) == RS_FAILURE); // If buffer is NULL, then it fails
		RS_ASSERT(rs_extract(&s4, 0, 256) == RS_FAILURE); // If either integer parameter falls outside the bound of the string, it fails

		rs_delete(&s0);
		rs_delete(&s1);
		rs_delete(&s2);
		rs_delete(&s3);
		rs_delete(&s4);
	}
	printf("Test EXTRACTING SUBSTRINGS finished...\n");

	printf("\nTest TRIMMING STRINGS...\n");
	{
		rs_string s0 = rs_create("       A Little from Column A    ");
		rs_string s1 = rs_create("  a Little from Column B    ");
		rs_string s2 = rs_create(" a Little from Column C          ");
		rs_string s3 = rs_create("******a******");
		rs_string s4 = rs_create(NULL);
		
		RS_ASSERT(rs_trim(&s0) == RS_SUCCESS);
		RS_ASSERT(s0.length == 22);
		RS_ASSERT(memcmp(s0.buffer, "A Little from Column A", s0.length) == 0);
		
		RS_ASSERT(rs_trim_left(&s1) == RS_SUCCESS);
		RS_ASSERT(s1.length == 26);
		RS_ASSERT(memcmp(s1.buffer, "a Little from Column B    ", s1.length) == 0);
		
		RS_ASSERT(rs_trim_right(&s2) == RS_SUCCESS);
		RS_ASSERT(s2.length == 23);
		RS_ASSERT(memcmp(s2.buffer, " a Little from Column C", s2.length) == 0);
		
		RS_ASSERT(rs_trim_delimiter(&s3, '*') == RS_SUCCESS);
		RS_ASSERT(s3.length == 1);
		RS_ASSERT(memcmp(s3.buffer, "a", s3.length) == 0);
		
		RS_ASSERT(rs_trim(&s4) == RS_FAILURE); // if character buffer is NULL, all functions fails
		RS_ASSERT(rs_trim_left(&s4) == RS_FAILURE);
		RS_ASSERT(rs_trim_right(&s4) == RS_FAILURE);
		RS_ASSERT(rs_trim_delimiter(&s4, ' ') == RS_FAILURE);
		RS_ASSERT(rs_trim(NULL) == RS_FAILURE); // if the parameter is NULL, all functions fails
		RS_ASSERT(rs_trim_left(NULL) == RS_FAILURE);
		RS_ASSERT(rs_trim_right(NULL) == RS_FAILURE);
		RS_ASSERT(rs_trim_delimiter(NULL, 'A') == RS_FAILURE);
		
		rs_delete(&s0);
		rs_delete(&s1);
		rs_delete(&s2);
		rs_delete(&s3);
	}
	printf("Test TRIMMING STRINGS finished...\n");

	printf("\nTest CONVERTING STRINGS...\n");
	{
		rs_string s0 = rs_create("High And Dry");
		rs_string s1 = rs_create(NULL);
		RS_ASSERT(rs_convert_upper(&s0) == RS_SUCCESS);
		RS_ASSERT(s0.length == 12);
		RS_ASSERT(memcmp(s0.buffer, "HIGH AND DRY", s0.length) == 0);
		RS_ASSERT(rs_convert_lower(&s0) == RS_SUCCESS);
		RS_ASSERT(s0.length == 12);
		RS_ASSERT(memcmp(s0.buffer, "high and dry", s0.length) == 0);
		RS_ASSERT(rs_convert_upper(&s1) == RS_FAILURE); // If parameter has a NULL buffer or is NULL itself, these functions fails
		RS_ASSERT(s1.length == 0);
		RS_ASSERT(s1.buffer == NULL);
		RS_ASSERT(memcmp(s1.buffer, "", s1.length) == 0);
		RS_ASSERT(rs_convert_lower(&s1) == RS_FAILURE);
		RS_ASSERT(s1.length == 0);
		RS_ASSERT(s1.buffer == NULL);
		RS_ASSERT(memcmp(s1.buffer, "", s1.length) == 0);
		RS_ASSERT(rs_convert_upper(NULL) == RS_FAILURE);
		RS_ASSERT(rs_convert_lower(NULL) == RS_FAILURE);
		
		rs_string s2 = rs_create("314.567");
		rs_string s3 = rs_create("Not a valid float");
		rs_string s4 = rs_create("10");
		rs_string s5 = rs_create("0.567764");
		rs_string s6 = rs_create("100000000000.567764999999");
		rs_string s7 = rs_create("0.0f");
		rs_string s8 = rs_create("+100.56");
		rs_string s9 = rs_create("-12.3");
		rs_string s10 = rs_create(NULL);
		rs_string s11 = rs_create("");
		rs_string s12 = rs_create("23.4-5/6");

		float b = 0.0f;
		RS_ASSERT(rs_convert_to_float(&s2, &b) == RS_SUCCESS);
		RS_ASSERT(b == 314.567f);
		RS_ASSERT(rs_convert_to_float(&s3, &b) == RS_FAILURE);
		RS_ASSERT(b == 314.567f); // b is untouched when the function fails
		RS_ASSERT(rs_convert_to_float(&s4, &b) == RS_SUCCESS);
		RS_ASSERT(b == 10.0f); // works with string formatted as integers too
		RS_ASSERT(rs_convert_to_float(&s5, &b) == RS_SUCCESS);
		RS_ASSERT(-0.0000001 < (b - 0.567764f) && (b - 0.567764f) < 0.0000001); // better precision with numbers closer to 0.0f
		RS_ASSERT(rs_convert_to_float(&s6, &b) == RS_SUCCESS); // this is a huge number for conversions, which obviously will give you meaningless numbers, but I want to leave this test here to show that this isn't an error per se
		b = 0.0f;
		RS_ASSERT(rs_convert_to_float(&s7, &b) == RS_FAILURE); // cannot have characters in the number, even if it's an 'f' character at the end
		RS_ASSERT(b == 0.0f);
		RS_ASSERT(rs_convert_to_float(&s8, &b) == RS_SUCCESS);
		RS_ASSERT(b == 100.56f);
		RS_ASSERT(rs_convert_to_float(&s9, &b) == RS_SUCCESS);
		RS_ASSERT(b == -12.3f);
		RS_ASSERT(rs_convert_to_float(&s10, &b) == RS_FAILURE); // if buffer is null, it fails
		RS_ASSERT(b == -12.3f);
		RS_ASSERT(rs_convert_to_float(NULL, &b) == RS_FAILURE); // if parameter is NULL it fails
		RS_ASSERT(b == -12.3f);
		RS_ASSERT(rs_convert_to_float(&s11, &b) == RS_FAILURE); // if length is 0, it fails
		RS_ASSERT(b == -12.3f);
		RS_ASSERT(rs_convert_to_float(&s12, &b) == RS_FAILURE);
		RS_ASSERT(b == -12.3f);
		
		rs_string s13 = rs_create("100");
		rs_string s14 = rs_create("0.345");
		rs_string s15 = rs_create("Not a valid integer");
		rs_string s16 = rs_create("9999999L");
		rs_string s17 = rs_create("+2147483647");
		rs_string s18 = rs_create("-2147483648");
		rs_string s19 = rs_create("23.5647");
		rs_string s20 = rs_create("+2323+2323");
		rs_string s21 = rs_create("-2323-2323");
		rs_string s22 = rs_create(".");
		rs_string s23 = rs_create("");
		rs_string s24 = rs_create(NULL);
		int a = 0;
		RS_ASSERT(rs_convert_to_int(&s13, &a) == RS_SUCCESS);
		RS_ASSERT(a == 100);
		RS_ASSERT(rs_convert_to_int(&s14, &a) == RS_SUCCESS);
		RS_ASSERT(a == 0);
		RS_ASSERT(rs_convert_to_int(&s15, &a) == RS_FAILURE); // a is untouched when the function fails
		RS_ASSERT(a == 0);
		RS_ASSERT(rs_convert_to_int(&s16, &a) == RS_FAILURE); // can't have a character in the string. even if it's the 'L' character
		RS_ASSERT(a == 0);
		RS_ASSERT(rs_convert_to_int(&s17, &a) == RS_SUCCESS);
		RS_ASSERT(a == 2147483647);
		RS_ASSERT(rs_convert_to_int(&s18, &a) == RS_SUCCESS);
		RS_ASSERT(a == -2147483648);
		RS_ASSERT(rs_convert_to_int(&s19, &a) == RS_SUCCESS);
		RS_ASSERT(a == 23);
		RS_ASSERT(rs_convert_to_int(&s20, &a) == RS_FAILURE);
		RS_ASSERT(a == 23);
		RS_ASSERT(rs_convert_to_int(&s21, &a) == RS_FAILURE);
		RS_ASSERT(a == 23);
		RS_ASSERT(rs_convert_to_int(&s22, &a) == RS_FAILURE); // strings should start with a number, '+' or '-' (numbers like .003 don't work)
		RS_ASSERT(a == 23);
		RS_ASSERT(rs_convert_to_int(&s23, &a) == RS_FAILURE); // if length is 0, function fails
		RS_ASSERT(a == 23);
		RS_ASSERT(rs_convert_to_int(&s24, &a) == RS_FAILURE); // if buffer is NULL, function fails
		RS_ASSERT(a == 23);
		RS_ASSERT(rs_convert_to_int(NULL, &a) == RS_FAILURE); // if parameter is NULL, function fails
		RS_ASSERT(a == 23);

		rs_string s25 = rs_create("0xFFFFFFFF"); // must start with 0x or 0X
		rs_string s26 = rs_create("0xFFF");
		rs_string s27 = rs_create("0xA");
		rs_string s28 = rs_create("0X0aFa123"); // works with upper case X and lowercase letters too
		rs_string s29 = rs_create("0x1234");
		rs_string s30 = rs_create("");
		rs_string s31 = rs_create(NULL);
		rs_string s32 = rs_create("FAFAFA"); // doesn't start with 0X
		rs_string s33 = rs_create("0xAAAAAAAAAA"); // too many digits, must 0x then 8 digits max
		unsigned int c = 0;
		RS_ASSERT(rs_convert_hex_to_uint(&s25, &c) == RS_SUCCESS);
		RS_ASSERT(c == 0xFFFFFFFF);
		RS_ASSERT(rs_convert_hex_to_uint(&s26, &c) == RS_SUCCESS);
		RS_ASSERT(c == 0xFFF);
		RS_ASSERT(rs_convert_hex_to_uint(&s27, &c) == RS_SUCCESS);
		RS_ASSERT(c == 0xA);
		RS_ASSERT(rs_convert_hex_to_uint(&s28, &c) == RS_SUCCESS);
		RS_ASSERT(c == 0X0aFa123);
		RS_ASSERT(rs_convert_hex_to_uint(&s29, &c) == RS_SUCCESS);
		RS_ASSERT(c == 0x1234);
		RS_ASSERT(rs_convert_hex_to_uint(&s30, &c) == RS_FAILURE);
		RS_ASSERT(c == 0x1234);
		RS_ASSERT(rs_convert_hex_to_uint(&s31, &c) == RS_FAILURE);
		RS_ASSERT(c == 0x1234);
		RS_ASSERT(rs_convert_hex_to_uint(&s32, &c) == RS_FAILURE);
		RS_ASSERT(c == 0x1234);
		RS_ASSERT(rs_convert_hex_to_uint(&s33, &c) == RS_FAILURE);
		RS_ASSERT(c == 0x1234);
		
		rs_string s34 = rs_create("Hello World\n");
		rs_string s35 = rs_create("");
		rs_string s36 = rs_create(NULL);
		rs_string s37 = rs_create("0");
		RS_ASSERT(rs_reverse(&s34) == RS_SUCCESS);
		RS_ASSERT(s34.length == 12);
		RS_ASSERT(memcmp(s34.buffer, "\ndlroW olleH", s34.length) == 0);
		RS_ASSERT(rs_reverse(&s35) == RS_SUCCESS);
		RS_ASSERT(s35.length == 0);
		RS_ASSERT(memcmp(s35.buffer, "", s35.length) == 0); // not necessary
		RS_ASSERT(rs_reverse(&s36) == RS_FAILURE);
		RS_ASSERT(s36.length == 0);
		RS_ASSERT(memcmp(s36.buffer, NULL, s36.length) == 0);
		RS_ASSERT(rs_reverse(&s37) == RS_SUCCESS);
		RS_ASSERT(s37.length == 1);
		RS_ASSERT(memcmp(s37.buffer, "0", s37.length) == 0);
		RS_ASSERT(rs_reverse(NULL) == RS_FAILURE);

		rs_delete(&s0); rs_delete(&s1); rs_delete(&s2); rs_delete(&s3); rs_delete(&s4); 
		rs_delete(&s5); rs_delete(&s6); rs_delete(&s7); rs_delete(&s8); rs_delete(&s9); 
		rs_delete(&s10); rs_delete(&s11); rs_delete(&s12); rs_delete(&s13); rs_delete(&s14); 
		rs_delete(&s15); rs_delete(&s16); rs_delete(&s17); rs_delete(&s18); rs_delete(&s19); 
		rs_delete(&s20); rs_delete(&s21); rs_delete(&s22); rs_delete(&s23); rs_delete(&s24);
		rs_delete(&s25); rs_delete(&s26); rs_delete(&s27); rs_delete(&s28); rs_delete(&s29);
		rs_delete(&s30); rs_delete(&s31); rs_delete(&s32); rs_delete(&s33); rs_delete(&s34); 
		rs_delete(&s35); rs_delete(&s36); rs_delete(&s37);
	}
	printf("Test CONVERTING STRINGS finished...\n");

	printf("\nTest CONVENIENT FUNCTION...\n");
	{
		char c1 = 'a';
		RS_ASSERT(rs_is_upper(c1) == RS_FAILURE);
		RS_ASSERT(rs_is_lower(c1) == RS_SUCCESS);
		RS_ASSERT(rs_is_letter(c1) == RS_SUCCESS);
		RS_ASSERT(rs_is_digit(c1) == RS_FAILURE);

		rs_string s0 = rs_create("h[\\cW5mZ2RPFN4dv:&0");
		rs_string s1 = rs_create("");
		rs_string s2 = rs_create(NULL);
		RS_ASSERT(rs_count_letters(&s0) == 11);
		RS_ASSERT(rs_count_digits(&s0) == 4);
		RS_ASSERT(rs_count_letters(&s1) == 0);
		RS_ASSERT(rs_count_digits(&s1) == 0);
		RS_ASSERT(rs_count_letters(&s2) == -1); // If the buffer is NULL, it returns -1
		RS_ASSERT(rs_count_digits(&s2) == -1);
		RS_ASSERT(rs_count_letters(NULL) == -1);  // If the parameter is NULL, it returns -1
		RS_ASSERT(rs_count_digits(NULL) == -1);
		rs_delete(&s0);
		rs_delete(&s1);
		rs_delete(&s2);
	}
	printf("Test CONVENIENT FUNCTION finished...\n");

	// rs_split_by_delimiter, when it doesn't return RS_FAILURE, will reallocate memory for the token rs_string 
	//		when the size of the token is smaller than the new contents
	//		which means the user will need to call rs_delete on that rs_string.
	printf("\nTest SPLITTING STRINGS...\n");
	{
		rs_string s0 = rs_create("#include <stdio.h>\nint main(void){\n\tprintf(\"Hello World...\");\n}\n");
		rs_string token0 = rs_create(NULL);
		
		RS_ASSERT(rs_split_by_delimiter(&s0, '\n', &token0) == RS_SUCCESS);
		RS_ASSERT(s0.length == 45);
		RS_ASSERT(memcmp(s0.buffer, "int main(void){\n\tprintf(\"Hello World...\");\n}\n", s0.length) == 0);
		RS_ASSERT(token0.length == 18);
		RS_ASSERT(memcmp(token0.buffer, "#include <stdio.h>", token0.length) == 0);
		
		RS_ASSERT(rs_split_by_delimiter(&s0, '\n', &token0) == RS_SUCCESS);
		RS_ASSERT(s0.length == 29);
		RS_ASSERT(memcmp(s0.buffer, "\tprintf(\"Hello World...\");\n}\n", s0.length) == 0);
		RS_ASSERT(token0.length == 15);
		RS_ASSERT(memcmp(token0.buffer, "int main(void){", token0.length) == 0);
		
		RS_ASSERT(rs_split_by_delimiter(&s0, '\n', &token0) == RS_SUCCESS);
		RS_ASSERT(s0.length == 2);
		RS_ASSERT(memcmp(s0.buffer, "}\n", s0.length) == 0);
		RS_ASSERT(token0.length == 26);
		RS_ASSERT(memcmp(token0.buffer, "\tprintf(\"Hello World...\");", token0.length) == 0);
		
		RS_ASSERT(rs_split_by_delimiter(&s0, '\n', &token0) == RS_SUCCESS);
		RS_ASSERT(s0.length == 0);
		RS_ASSERT(memcmp(s0.buffer, "", s0.length) == 0);
		RS_ASSERT(token0.length == 1);
		RS_ASSERT(memcmp(token0.buffer, "}", token0.length) == 0);

		RS_ASSERT(rs_split_by_delimiter(&s0, '\n', &token0) == RS_FAILURE); // Here the buffer is empty, so it fails, token0 is untouched
		RS_ASSERT(s0.length == 0);
		RS_ASSERT(memcmp(s0.buffer, "", s0.length) == 0); // not necessary
		RS_ASSERT(token0.length == 1);
		RS_ASSERT(memcmp(token0.buffer, "}", token0.length) == 0); // not necessary

		RS_ASSERT(rs_split_by_delimiter(NULL, ' ', &token0) == RS_FAILURE); // if the first or third parameter is NULL, then it fails
		RS_ASSERT(rs_split_by_delimiter(&s0, ' ', NULL) == RS_FAILURE);

		rs_string s1 = rs_create(NULL);
		RS_ASSERT(rs_split_by_delimiter(&s1, ' ', &token0) == RS_FAILURE); // if the buffer is NULL, then it fails

		rs_string s2 = rs_create("AAA");
		rs_string token1 = rs_create(NULL);
		RS_ASSERT(rs_split_by_delimiter(&s2, 'A', &token1) == RS_SUCCESS);
		RS_ASSERT(s2.length == 2);
		RS_ASSERT(memcmp(s2.buffer, "AA", s2.length) == 0);
		RS_ASSERT(token1.length == 0);
		RS_ASSERT(memcmp(token1.buffer, NULL, token1.length) == 0);

		rs_string s3 = rs_create("Hello World! Hey! Hello!! Helloo? Hey Hey Ho!!");
		rs_string token2 = rs_create(NULL);
		
		RS_ASSERT(rs_split_by_substring(&s3, "Hello", &token2) == RS_SUCCESS);
		RS_ASSERT(memcmp(s3.buffer, " World! Hey! Hello!! Helloo? Hey Hey Ho!!", s3.length) == 0);
		RS_ASSERT(s3.length == 41);
		RS_ASSERT(memcmp(token2.buffer, "", token2.length) == 0);
		RS_ASSERT(token2.length == 0);

		RS_ASSERT(rs_split_by_substring(&s3, "Hello", &token2) == RS_SUCCESS);
		RS_ASSERT(memcmp(s3.buffer, "!! Helloo? Hey Hey Ho!!", s3.length) == 0);
		RS_ASSERT(s3.length == 23);
		RS_ASSERT(memcmp(token2.buffer, " World! Hey! ", token2.length) == 0);
		RS_ASSERT(token2.length == 13);

		RS_ASSERT(rs_split_by_substring(&s3, "Hello", &token2) == RS_SUCCESS);
		RS_ASSERT(memcmp(s3.buffer, "o? Hey Hey Ho!!", s3.length) == 0);
		RS_ASSERT(s3.length == 15);
		RS_ASSERT(memcmp(token2.buffer, "!! ", token2.length) == 0);
		RS_ASSERT(token2.length == 3);

		RS_ASSERT(rs_split_by_substring(&s3, "Hey", &token2) == RS_SUCCESS);
		RS_ASSERT(memcmp(s3.buffer, " Hey Ho!!", s3.length) == 0);
		RS_ASSERT(s3.length == 9);
		RS_ASSERT(memcmp(token2.buffer, "o? ", token2.length) == 0);
		RS_ASSERT(token2.length == 3);

		RS_ASSERT(rs_split_by_substring(&s3, "Hey", &token2) == RS_SUCCESS);
		RS_ASSERT(memcmp(s3.buffer, " Ho!!", s3.length) == 0);
		RS_ASSERT(s3.length == 5);
		RS_ASSERT(memcmp(token2.buffer, " ", token2.length) == 0);
		RS_ASSERT(token2.length == 1);

		RS_ASSERT(rs_split_by_substring(&s3, "!!", &token2) == RS_SUCCESS);
		RS_ASSERT(memcmp(s3.buffer, "", s3.length) == 0);
		RS_ASSERT(s3.length == 0);
		RS_ASSERT(memcmp(token2.buffer, " Ho", token2.length) == 0);
		RS_ASSERT(token2.length == 3);

		rs_delete(&s0);
		rs_delete(&s1);
		rs_delete(&s2);
		rs_delete(&s3);
		rs_delete(&token0);
		rs_delete(&token1);
		rs_delete(&token2);
	}
	printf("Test SPLITTING STRINGS finished...\n");

	// printf("Test START AND END CHECK...\n");
	// {
	// 	rs_string s0 = rs_create("A brown fox jumps over the lazy dog");
	// 	rs_string s1 = rs_create("n");
	// 	rs_string s2 = rs_create("");
	// 	rs_string s3 = rs_create(NULL);
	// 	// printf("Result(\"A brown fox \") = %i\n", rs_starts_with_substring(&s0, "A brown fox "));
	// 	// printf("Result(\"jumps over\") = %i\n", rs_starts_with_substring(&s0, "jumps over"));
	// 	// printf("Result(\"A brown fox jumps over the lazy dog\") = %i\n", rs_starts_with_substring(&s0, "A brown fox jumps over the lazy dog"));
	// 	// printf("Result(\"over the lazy dog\") = %i\n", rs_ends_with_substring(&s0, "over the lazy dog"));
	// 	// printf("Result(\"brown fox jumps\") = %i\n", rs_ends_with_substring(&s0, "brown fox jumps"));
	// 	// printf("Result(\"A brown fox jumps over the lazy dog\") = %i\n", rs_ends_with_substring(&s0, "A brown fox jumps over the lazy dog"));
	// 	rs_delete(&s0);
	// 	rs_delete(&s1);
	// 	rs_delete(&s2);
	// 	rs_delete(&s3);
	// }
	// printf("Test START AND END CHECK finished...\n");

	// printf("Test REPLACING CHARACTERS / STRINGS...\n");
	// {
	// 	// int rs_replace_character(rs_string* s, const char char_to_replace, const char replacement);
	// 	// int rs_replace_substring(rs_string* s, const char* substring_to_replace, const char* substring_replacement);
	// }
	// printf("Test REPLACING CHARACTERS / STRINGS finished...\n");

	return 0;
}
