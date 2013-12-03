/*
* Name: Dean Bisogno
* Course: CS 157
* Purpose: Homework 3
* Date: December 2, 2013
*/

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>


int check_arguments(int count, char *values[]); 
int find_area_info(char *to_find, FILE *info_file);
int check_query_type(char *mystery_string);

int main(int argc, char *argv[]) {
	// If we have fewer than 3 arguments (including the name of the program) or 
	// the number of arguements (including the name of the program) is even,
	// then we have an incomplete command. 
	int result;
	if((result = check_arguments(argc, argv)))
		return result;

// Lets get that file open and complain if we can't.
	FILE *area_code_info;
	if((area_code_info = fopen(argv[1], "r")) == NULL) {
		fprintf(stderr, 
			"Error in %s.\n"
			"Problem opening area code file '%s'.\n", 
			argv[0], argv[1]);
		return 2;
	}

	for(int i = 2; i < argc; i++) {
		find_area_info(argv[i], area_code_info);
	}


	fclose(area_code_info);
	return 0;
}

// Input the number of arguments to the program, and the array of their values
// Return 1 if there is a problem with the arguments, return 0 if there are three or more.
int check_arguments(int count, char *values[]) {
	if (count < 3) 
	{
		fprintf(stderr,
			"USAGE: %s <area-code-file> <query> ...\n",
			values[0]);

		return 1;
	}
	return 0;
}

typedef struct info_element_struct {
	char info[500];
	struct info_element *next;
} info_element;

int find_area_info(char *to_find, FILE *info_file) {
	rewind(info_file); // Make sure we're starting from the beginning of the file.

	bool searching_for_acode = check_query_type(to_find);
	char buf[500] = {0};
	char matches_list[10][500];
	int match_count = 0;

	int c;
	int line_length = 0;
	while ((c = fgetc(info_file)) != EOF) {	
		buf[line_length] = c;
		line_length++;
		if('\n' == c) {
			char *position = strstr(buf, to_find);
			if(position != NULL)
			{
				if(position[0] == buf[0] && searching_for_acode) {
					if(match_count < 10)
						strcpy(matches_list[match_count],buf);
					match_count++;
				} else if (!searching_for_acode){		
					if(match_count < 10)					
						strcpy(matches_list[match_count],buf);
					match_count++;
				}
			}
			memset(buf, 0, sizeof(buf));
			line_length = 0;
		}

		
	}

	printf("Area codes for \"%s\":\n", to_find);
	if(match_count > 10)
		printf("   that gave %d matches\n", match_count);
	else
		for(int i = 0; i < match_count; i++)
			printf("   %s", matches_list[i]);

 return 0;
}

// Input a string.
// Returns 1 if we want to consider it an area code query 0 if it should be handled as a string.
int check_query_type(char *mystery_string) {
	int length = 0;
	if(*mystery_string == '-')
		return 0;  // we will consider negative numbers strings... who ever heard of a negative area code?

	do {
		if(length > 3) // area codes are only three long, if we pass three digits, it's gonna be treated as a string.
			return 0;

		//printf("%c is being checked.\n", *mystery_string);
		if(isdigit(*mystery_string)) {
			mystery_string++;
			length++;
			continue;
		} // If we're looking at a digit then it's still all numeric
		else //It was something other than a digit so its gonna be a string for us.
			return 0;

	}while(*mystery_string != '\0');

	return 1; // We got this far so it must be all digits.
}
