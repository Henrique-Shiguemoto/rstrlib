#ifndef RSTRLIB_H
#define RSTRLIB_H

#define RS_STRING_MAX_LENGTH 32000

// inspired by Tsoding's sv library (https://github.com/tsoding/sv)
#define RS_STR_FMT 	"%.*s"
#define RS_ARG(rs) 	(int) (rs)->length, (rs)->buffer

#define RS_SUCCESS 1
#define RS_FAILURE 0

#include <stdio.h>
#include <stdlib.h>

typedef struct rs_string{
	int length; // DON'T CHANGE THIS ATTRIBUTE!
	char* buffer;
} rs_string;

int 		rs_length(const char* s);
rs_string	rs_create(const char* s);
void 		rs_delete(rs_string* s);
int			rs_copy(rs_string* src_s, rs_string* dest_s);
int 		rs_concatenate(rs_string* dest, rs_string* str_to_append);
int 		rs_first_occurrence(char c, rs_string* s);
int         rs_is_char_in_string(char c, rs_string* s);
int 		rs_compare(rs_string* s1, rs_string* s2);
int         rs_compare_to_cstr(rs_string* rs_str, char* cstr);
int 		rs_compare_case_insensitive(rs_string* s1, rs_string* s2);
int         rs_compare_to_cstr_case_insensitive(rs_string* rs_str, char* cstr);
int 		rs_extract(rs_string* s, int from, int to);
int 		rs_extract_left(rs_string* s, int characterCount);
int 		rs_extract_right(rs_string* s, int characterCount);
int 		rs_trim(rs_string* s);
int 		rs_trim_left(rs_string* s);
int 		rs_trim_right(rs_string* s);
int  		rs_convert_upper(rs_string* s);
int  		rs_convert_lower(rs_string* s);
int 		rs_convert_to_int(rs_string* s, int* n);
int 		rs_convert_to_float(rs_string* s, float* n);
int  		rs_is_upper(char c);
int  		rs_is_lower(char c);
int  		rs_is_letter(char c);
int  		rs_is_digit(char c);
int  		rs_count_letters(rs_string* s);
int  		rs_count_digits(rs_string* s);
int 	  	rs_split_by_delimiter(rs_string* s, char delimiter, rs_string* token);
int 		rs_reverse(rs_string* s);
void  		rs_print(rs_string* s);

#endif // RSTRLIB_H