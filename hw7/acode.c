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

#define MAX_LINE_LENGTH 500
#define MAX_MATCH_LENGTH 10

// Comments for these listed with the function definition.
int check_arguments(int count, char *values[]); 
int find_area_info(char *to_find, FILE *info_file);
int check_query_type(char *mystery_string);
int compare(const void *av, const void *bv);

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

	// Process each query
	for(int i = 2; i < argc; i++) {
		find_area_info(argv[i], area_code_info);
	}


	// All done.
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

int find_area_info(char *to_find, FILE *info_file) {
	rewind(info_file); // Make sure we're starting from the beginning of the file.

	bool searching_for_acode = check_query_type(to_find); // figure out if we're doing an area code search or a string search.
	char buf[MAX_LINE_LENGTH] = {0}; // We'll hold our current line here,
	char matches_list[MAX_MATCH_LENGTH][MAX_LINE_LENGTH]; // We'll keep an array of the first 10 matches.
	int match_count = 0;

	int c;
	int line_length = 0;
	while ((c = fgetc(info_file)) != EOF) {	
		buf[line_length] = c; // read the character into the buffer.
		line_length++; // Track how many characters we've recorded.
		if('\n' == c) { // When we hit the end of the line, let's start looking for matches.
			char *position = strstr(buf, to_find); // Find a match and store it's position.
			if(position != NULL) // If we actually have a match then figure out if it actually counts
			{
				if(position[0] == buf[0] && searching_for_acode) { // we don't want area codes to match in the body of the description.
					if(match_count < MAX_MATCH_LENGTH)
						strcpy(matches_list[match_count],buf);
					match_count++;
				} else if (!searching_for_acode){		
					if(match_count < MAX_MATCH_LENGTH)					
						strcpy(matches_list[match_count],buf);
					match_count++;
				}
			}
			memset(buf, 0, sizeof(buf)); // Clear the buffer so we can check the next line.
			line_length = 0;
		}		
	}

	printf("Area codes for \"%s\":\n", to_find);
	// If there were more than 10 matches, just print how many there were.
	if(match_count > MAX_MATCH_LENGTH) {
		printf("   that gave %d matches\n", match_count);
	} else { // Otherwise, sort the array then print the matches.
		qsort(matches_list, match_count, sizeof(buf), compare);
		for(int i = 0; i < match_count; i++)
			printf("   %s", matches_list[i]);
	}

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

// This is our compare function for qsort.
// Compares to thing and returns -1 if the first comes before the second,
// 1 is the first comes after the second
// 0 if they are equal.
int compare(const void *av, const void *bv) {
        const char *a = av, *b = bv;
        int ai = atoi(a), bi = atoi(b); // this will just convert the area code at the beginning of the line to an int for comparison.
        if (ai < bi) return -1;
        if (ai > bi) return 1;
        return 0;
}
