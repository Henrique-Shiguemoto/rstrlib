#include "rstrlib.h"

int rs_length(const char* s){
	int current_length = 0;
	while(*s++ && current_length < RS_STRING_MAX__length) current_length++;
	return current_length;
}

rs_string rs_create(const char* s){
	if(!s) return (rs_string){0};

	rs_string newString = {0};
	newString.length = rs_length(s);
	if(newString.length == RS_STRING_MAX__length) return (rs_string){0};
	
	newString.buffer = malloc(sizeof(char) * newString.length + 1);

	int currentIndex = 0;
	while(currentIndex < newString.length){
		newString.buffer[currentIndex] = s[currentIndex];
		currentIndex++;
	}
	newString.buffer[currentIndex] = '\0';

	return newString;
}


/**
 * 
 * Since we're calling free, the user has to make sure that s->buffer is from the heap (by using rs_create or rs_copy).
 * 		(source: https://stackoverflow.com/questions/2693655/free-on-stack-memory)
 * 
 * */
void rs_delete(rs_string* s){
	if(!s) return;
	if(s->buffer){
		free(s->buffer);
		s->buffer = 0;
		s->length = 0;
	}
}

/**
 * 
 * There's danger in here! The user has to make sure that dest_s->buffer is either a heap allocated buffer (from rs_create for example) 
 * 		or it has to be 0 (like rs_string s = {0};, for example)
 * 
 * If dest_s->buffer points to stack memory (unless it's just the value 0), we'll have an undefined behavior from the free() function.
 * 		(source: https://stackoverflow.com/questions/2693655/free-on-stack-memory)
 * 
 * */
int	rs_copy(rs_string* src_s, rs_string* dest_s){
	if(!src_s || !dest_s || !src_s->buffer) return RS_FAILURE;

	dest_s->length = src_s->length;

	if(dest_s->buffer) free(dest_s->buffer);
	
	dest_s->buffer = malloc(sizeof(char) * dest_s->length + 1);

	int i = 0;
	while(i < dest_s->length){
		dest_s->buffer[i] = src_s->buffer[i];
		i++;
	}
	dest_s->buffer[i] = '\0';

	return RS_SUCCESS;
}

/**
 * 
 * There's danger in here! The user has to make sure that dest_s->buffer is either a heap allocated buffer (from rs_create for example) 
 * 		or it has to be 0 (like rs_string s = {0};, for example)
 * 
 * If dest_s->buffer points to stack memory (unless it's just the value 0), we'll have an undefined behavior from the realloc() function.
 * 		(source: https://linux.die.net/man/3/realloc)
 * 
 * */
int rs_concatenate(rs_string* dest_s, rs_string* str_to_append){
	if(!dest_s || !str_to_append){
		return RS_FAILURE;
	}
	if(!str_to_append->buffer){
		return RS_SUCCESS;
	}
	if(!dest_s->buffer){
		return rs_copy(str_to_append, dest_s);
	}

	char* temp = realloc(dest_s->buffer, dest_s->length + str_to_append->length + 1);
	if(!temp) return RS_FAILURE;
	
	dest_s->buffer = temp;

	int i = 0;
	while(i < str_to_append->length){
		dest_s->buffer[dest_s->length + i] = str_to_append->buffer[i];
		i++;
	}
	dest_s->buffer[dest_s->length + str_to_append->length] = '\0';
	dest_s->length += str_to_append->length;
	return RS_SUCCESS;
}

int rs_first_occurrence(char c, rs_string* s){
	if(!s || !s->buffer || s->length == 0) return -1;

	int currentIndex = 0;
	while(currentIndex < s->length && s->buffer[currentIndex] != '\0'){
		if(s->buffer[currentIndex] == c) return currentIndex;
		currentIndex++;
	}
	return -1;
}

int rs_is_char_in_string(char c, rs_string* s){
	return rs_first_occurrence(c, s) == -1 ? RS_FAILURE : RS_SUCCESS;
}

int rs_compare(rs_string* s1, rs_string* s2){
	if(!s1 || !s2 || !s1->buffer || !s2->buffer || s1->length != s2->length) return RS_FAILURE;

	int currentIndex = 0;
	while(currentIndex < s1->length){
		if(s1->buffer[currentIndex] != s2->buffer[currentIndex]) return RS_FAILURE;
		currentIndex++;
	}
	return RS_SUCCESS;
}

int rs_compare_to_cstr(rs_string* rs_str, char* cstr){
	if(!rs_str || !rs_str->buffer || !cstr) return RS_FAILURE;

	int cStrSize = rs_length(cstr);
	if(cStrSize != rs_str->length) return RS_FAILURE;

	int currentIndex = 0;
	while(currentIndex < rs_str->length){
		if(rs_str->buffer[currentIndex] != cstr[currentIndex]) return RS_FAILURE;
		currentIndex++;
	}
	return RS_SUCCESS;
}

int rs_compare_case_insensitive(rs_string* s1, rs_string* s2){
	if(!s1 || !s1->buffer || !s2 || !s2->buffer || s1->length != s2->length) return RS_FAILURE;
	
	int currentIndex = 0;
	while(currentIndex < s1->length){
		char c1 = s1->buffer[currentIndex];
		char c2 = s2->buffer[currentIndex];
		if(c1 != c2 && c1 - 32 != c2 && c1 != c2 - 32) return RS_FAILURE;
		currentIndex++;
	}

	return RS_FAILURE;
}

int rs_compare_to_cstr_case_insensitive(rs_string* rs_str, char* cstr){
	if(!rs_str || !rs_str->buffer || !cstr) return RS_FAILURE;

	int cStrSize = rs_length(cstr);
	if(cStrSize != rs_str->length) return RS_FAILURE;

	int currentIndex = 0;
	while(currentIndex < rs_str->length){
		char c1 = rs_str->buffer[currentIndex];
		char c2 = cstr[currentIndex];
		if(c1 != c2 && c1 - 32 != c2 && c1 != c2 - 32) return RS_FAILURE;
		currentIndex++;
	}
	return RS_SUCCESS;
}

int rs_extract(rs_string* s, int from, int to){
	if(!s || !s->buffer || from > s->length || to > s->length || to < from) return RS_FAILURE;

	int final_length = to - from + 1;
	int currentIndex = 0;
	while(currentIndex < final_length){
		s->buffer[currentIndex] = s->buffer[currentIndex + from];
		currentIndex++;
	}
	s->buffer[final_length] = '\0';
	s->length = final_length;
	return RS_SUCCESS;
}

int rs_extract_left(rs_string* s, int characterCount){
	return rs_extract(s, 0, characterCount - 1);
}

int rs_extract_right(rs_string* s, int characterCount){
	return rs_extract(s, s->length - characterCount, s->length - 1);
}

int rs_trim(rs_string* s){
	if(!s || !s->buffer) return RS_FAILURE;

	int startIndex = 0;
	int endIndex = s->length - 1;
	while(s->buffer[startIndex] == ' ' || s->buffer[endIndex] == ' '){
		if(s->buffer[startIndex] == ' ') startIndex++;
		if(s->buffer[endIndex] 	 == ' ') endIndex--;
	}

	rs_extract(s, startIndex, endIndex);
	return RS_SUCCESS;
}

int rs_trim_left(rs_string* s){
	if(!s || !s->buffer) return RS_FAILURE;

	int startIndex = 0;
	while(s->buffer[startIndex] == ' ') startIndex++;

	rs_extract(s, startIndex, s->length - 1);
	return RS_SUCCESS;
}

int rs_trim_right(rs_string* s){
	if(!s || !s->buffer) return RS_FAILURE;

	int endIndex = s->length - 1;
	while(s->buffer[endIndex] == ' ') endIndex--;

	rs_extract(s, 0, endIndex);
	return RS_SUCCESS;
}


int rs_convert_upper(rs_string* s){
	if(!s || !s->buffer) return RS_FAILURE;
	int currentIndex = 0;
	while(currentIndex < s->length){
		if(rs_is_lower(s->buffer[currentIndex])) s->buffer[currentIndex] -= 32;
		currentIndex++;
	}
	return RS_SUCCESS;
}

int rs_convert_lower(rs_string* s){
	if(!s || !s->buffer) return RS_FAILURE;
	int currentIndex = 0;
	while(currentIndex < s->length){
		if(rs_is_upper(s->buffer[currentIndex])) s->buffer[currentIndex] += 32;
		currentIndex++;
	}
	return RS_SUCCESS;
}

int rs_is_upper(char c){
	return ('A' <= c && c <= 'Z') ? RS_SUCCESS : RS_FAILURE;
}

int rs_is_lower(char c){
	return ('a' <= c && c <= 'z') ? RS_SUCCESS : RS_FAILURE;
}

int rs_is_letter(char c){
	return (rs_is_upper(c) || rs_is_lower(c)) ? RS_SUCCESS : RS_FAILURE;
}

int rs_is_digit(char c){
	return ('0' <= c && c <= '9') ? RS_SUCCESS : RS_FAILURE;
}

int rs_count_letters(rs_string* s){
	if(!s || !s->buffer) return 0;
	int count = 0;

	int currentIndex = 0;
	while(currentIndex < s->length){
		if(rs_is_letter(s->buffer[currentIndex])) count++;
		currentIndex++;
	}

	return count;
}

int rs_count_digits(rs_string* s){
	if(!s || !s->buffer) return 0;
	int count = 0;

	int currentIndex = 0;
	while(currentIndex < s->length){
		if(rs_is_digit(s->buffer[currentIndex])) count++;
		currentIndex++;
	}

	return count;
}

int rs_split_by_delimiter(rs_string* s, char delimiter, rs_string* token){
	if(!s || !s->buffer || !token) return RS_FAILURE;

	int currentIndex = 0;
	while(s->buffer[currentIndex] != delimiter && s->buffer[currentIndex] != '\0') 
		currentIndex++;
	if(currentIndex <= s->length - 1){
		if(currentIndex > token->length){
			token->buffer = realloc(token->buffer, currentIndex + 1);
			if(!token->buffer) return RS_FAILURE;
		}
		//we don't need to reallocate if we want to shrink, just use the same buffer and terminate it with '\0'

		int copyIndex = 0;
		while(copyIndex < currentIndex){
			token->buffer[copyIndex] = s->buffer[copyIndex];
			copyIndex++;
		}
		token->buffer[currentIndex] = '\0';
		token->length = currentIndex;
		int extraction_result = rs_extract_right(s, s->length - (currentIndex + 1));
		if(extraction_result == RS_FAILURE){
			s->buffer[0] = '\0';
			s->length = 0;
		}
		return 1;
	}
	token->buffer = 0;
	token->length = 0;
	return RS_FAILURE; //coudn't tokenize
}

int rs_reverse(rs_string* s){
	if(!s || !s->buffer) return RS_FAILURE;
	if(s->length == 1 || s->length == 0) return RS_SUCCESS;

	char aux = 0;
	int startIndex = 0;
	int endIndex = s->length - 1;

	while(startIndex < endIndex){
		aux = s->buffer[startIndex];
		s->buffer[startIndex] = s->buffer[endIndex];
		s->buffer[endIndex] = aux;
		startIndex++;
		endIndex--;
	}
	return RS_SUCCESS;
}

int rs_convert_to_float(rs_string* s, float* n){
	if(!s || !n || !s->buffer) return RS_FAILURE;
	return RS_SUCCESS;
}

int rs_convert_to_int(rs_string* s, int* n){
	if(!s || !n || !s->buffer) return RS_FAILURE;
	return RS_SUCCESS;
}

int rs_find_substring(rs_string* s, char* cstr){
	return -1;
}

int rs_starts_with_substring(rs_string* s, char* cstr){
	return RS_FAILURE;
}

int rs_end_with_substring(rs_string* s, char* cstr){
	return RS_FAILURE;
}

