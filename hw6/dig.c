/*
* Name: Dean Bisogno
* Course: CS 157
* Purpose: Homework 2
* Date: November 18, 2013
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

struct Pair {		// Note the capital P.
    char first, second;
    int count;
};

bool is_suspicious(const char);
bool who_in_whoville(char who_to_find[2], int whoville_population, struct Pair whoville[]);

int main(int argc, char *argv[]) {
	struct Pair *found_pairs = calloc(1, sizeof(struct Pair));
	int number_of_pairs = 0;

	if(found_pairs == NULL)
	{
		fprintf(stderr, "%s Error: Fatal error allocating memory for digraph pairs.\n", argv[0]);
		return 2;
	}
	if(argc < 2) {
		fprintf(stderr, 
			"%s Error: Atleast one filename needed.\n"
			"Usage: %s <file1> [...] <fileN> \n", 
			argv[0], argv[0]);
		free(found_pairs);			
		return 1;
	}

	for(int i = 1; i < argc; i ++) {
		FILE *filehandle = fopen(argv[i], "r");
		if(filehandle == NULL) {
			fprintf(stderr, 
			"%s Error: file %s could not be opened.\n",
			argv[0], argv[i]);
			continue;
		}


		int c;
		char digraph[2] = {' ', ' '};
		
		while((c = tolower(fgetc(filehandle))) != EOF)
		{
			digraph[0] = digraph[1];
			digraph[1] = c;
			if(is_suspicious(digraph[0]) || is_suspicious(digraph[1]))
				continue;

			if(!who_in_whoville(digraph, number_of_pairs, found_pairs)){
				number_of_pairs++;
				found_pairs = realloc(found_pairs, sizeof(struct Pair) * number_of_pairs);
				if(found_pairs == NULL) {
					fprintf(stderr, "%s Error: Fatal error reallocating memory for digraph pairs.\n", argv[0]);
					fclose(filehandle);
					free(found_pairs);
					return 4;					
				} else {
					found_pairs[number_of_pairs - 1].first = digraph[0];
					found_pairs[number_of_pairs - 1].second = digraph[1];
					found_pairs[number_of_pairs - 1].count = 1;
				}
			}
		}
		fclose(filehandle);
	}

	for(int i = 0; i < number_of_pairs; i ++) {
		printf("%c%c %d\n", found_pairs[i].first, found_pairs[i].second, found_pairs[i].count);
	}

	free(found_pairs);
	return 0;
}

bool who_in_whoville(char who_to_find[2], int whoville_population, struct Pair whoville[]) {
	int current_whoville_population = whoville_population;
	bool who_found = false;
	if(whoville_population == 0) {		
		whoville[0].first = who_to_find[0];
	    whoville[0].second = who_to_find[1];
	    whoville[0].count = 1;
	    current_whoville_population = 1;
	} else {
		for(int i = 0; i < whoville_population; i++)
		{
			if (who_to_find[0] == whoville[i].first && who_to_find[1] == whoville[i].second) {
				whoville[i].count++;
				who_found = true;
				break;
			} 
		}
	}

	return who_found;
}

bool is_suspicious(const char shifty_looking_character)  {
	if(!isalpha(shifty_looking_character))
		return true;
	else
		return false;
}
