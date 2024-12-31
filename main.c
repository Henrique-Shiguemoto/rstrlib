#include "rstrlib.h"
#include <stdio.h>

#define RS_PRINT(s) do { if((s)->buffer) printf("%.*s\n", (int) (s)->length, (s)->buffer); } while(0)

// This is just to show how to use the library functions

int main(void){
	// Whenever you use rs_create() you need to call rs_delete later
	printf("CREATING AND DELETING STRINGS:\n\n");
	rs_string s0 = rs_create("Hello World\n");
	RS_PRINT(&s0);
	printf("length(s0): %d = %d\n", s0.length, rs_length(s0.buffer));
	rs_delete(&s0);

	// You'll also need to call rs_delete whenever you call rs_copy
	printf("COPYING STRINGS:\n\n");
	rs_string s1 = rs_create("Test String");
	rs_string s2 = rs_create(NULL); // same as (rs_string){0} or {0}
	rs_copy(&s1, &s2);
	RS_PRINT(&s1);
	RS_PRINT(&s2);
	rs_delete(&s1);
	rs_delete(&s2);

	printf("CONCATENATING STRINGS:\n\n");
	rs_string s3 = rs_create("Hello ");
	rs_string s4 = rs_create("World\n");
	rs_concatenate(&s3, &s4);
	RS_PRINT(&s3);
	RS_PRINT(&s4);
	rs_delete(&s3);
	rs_delete(&s4);

	printf("SEARCHING CHARACTERS:\n\n");
	rs_string s5 = rs_create("Hello World\n");
	char c0 = 'W';
	printf("%c is%s in %s\n", c0, rs_is_char_in_string(c0, &s5) ? "" : "n't", s5.buffer);
	printf("%c is at %d\n", c0, rs_first_occurrence(c0, &s5));
	rs_delete(&s5);

	printf("COMPARING STRINGS:\n\n");
	rs_string s6 = rs_create("Henrique Shiguemoto Felizardo\n");
	rs_string s7 = rs_create("Henrique Shiguemoto Felizardo\n");
	rs_string s8 = rs_create("Henrique SHIGUEMOTO Felizardo\n");
	rs_string s9 = rs_create("henrique shiguemoto felizardo\n");

	printf("%s is%s equal to %s\n", s6.buffer, rs_compare(&s6, &s7) ? "" : "n't", s7.buffer);
	printf("%s is%s equal to %s\n", s7.buffer, rs_compare_to_cstr(&s7, s9.buffer) ? "" : "n't", s9.buffer);
	printf("%s is%s equal to %s\n", s6.buffer, rs_compare_case_insensitive(&s6, &s8) ? "" : "n't", s8.buffer);
	printf("%s is%s equal to %s\n", s7.buffer, rs_compare_to_cstr_case_insensitive(&s6, s8.buffer) ? "" : "n't", s8.buffer);

	rs_delete(&s6);
	rs_delete(&s7);
	rs_delete(&s8);
	rs_delete(&s9);

	printf("EXTRACTING SUBSTRINGS:\n\n");
	rs_string s10 = rs_create("A brown fox jumps over the lazy dog");
	RS_PRINT(&s10);
	rs_extract(&s10, 7, 20);
	RS_PRINT(&s10);
	rs_extract_left(&s10, 8);
	RS_PRINT(&s10);
	rs_extract_right(&s10, 3);
	RS_PRINT(&s10);
	rs_delete(&s10);

	printf("TRIMMING STRINGS:\n\n");
	rs_string s11 = rs_create("       A Little from Column A    ");
	rs_string s12 = rs_create("  a Little from Column B    ");
	rs_string s13 = rs_create(" a Little from Column C          ");
	
	rs_trim_left(&s11);
	rs_trim_right(&s12);
	rs_trim(&s13);
	
	RS_PRINT(&s11);
	RS_PRINT(&s12);
	RS_PRINT(&s13);

	rs_delete(&s11);
	rs_delete(&s12);
	rs_delete(&s13);

	printf("CONVERTING STRINGS:\n\n");
	rs_string s14 = rs_create("High And Dry");
	rs_string s15 = rs_create("314.567");

	RS_PRINT(&s14);
	rs_convert_upper(&s14);
	RS_PRINT(&s14);
	rs_convert_lower(&s14);
	RS_PRINT(&s14);
	
	int a = 0;
	float b = 0.0f;
	rs_convert_to_int(&s15, &a);
	rs_convert_to_float(&s15, &b);
	RS_PRINT(&s15);
	printf("a = %d\n", a);
	printf("b = %f\n\n", b);

	rs_delete(&s14);
	rs_delete(&s15);

	printf("CONVENIENT FUNCTION:\n\n");
	char c1 = 'a';
	printf("%c is%s upper case\n", c1, rs_is_upper(c1) ? "" : "n't");
	printf("%c is%s lower case\n", c1, rs_is_lower(c1) ? "" : "n't");
	printf("%c is%s a letter\n", c1, rs_is_letter(c1) ? "" : "n't");
	printf("%c is%s a digit\n", c1, rs_is_digit(c1) ? "" : "n't");

	rs_string s16 = rs_create("h[\\cW5mZRPFNdv:&");
	printf("number of letters = %d\n", rs_count_letters(&s16));
	printf("number of digits = %d\n\n", rs_count_digits(&s16));
	rs_delete(&s16);

	// rs_split_by_delimiter, when it doesn't return RS_FAILURE, will reallocate memory for the token rs_string (third parameter)
	//		which means the user will need to call rs_delete on that rs_string.
	printf("SPLITTING STRINGS:\n\n");
	rs_string s17 = rs_create("#include <stdio.h>\nint main(void){\n\tprintf(\"Hello World...\");\n}\n");
	rs_string token = rs_create(NULL);
	while(rs_split_by_delimiter(&s17, '\n', &token)){
		printf("rest = "); RS_PRINT(&s17);
		printf("token = "); RS_PRINT(&token);
		printf("-----------------------\n");
	}
	rs_delete(&s17);
	rs_delete(&token);

	printf("REVERSING STRINGS:\n\n");
	rs_string s18 = rs_create("Hello World\n");
	RS_PRINT(&s18);
	rs_reverse(&s18);
	RS_PRINT(&s18);
	rs_delete(&s18);

	return 0;
}
