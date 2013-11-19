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

//Structure for containing digraphs.
struct Pair {		// Note the capital P.
    char first, second;
    int count;
};

// returns true if the two character array who_to_find is found within the struct Pair array whoville with size whoville_population. 
bool who_in_whoville(char who_to_find[2], int whoville_population, struct Pair whoville[]);

int main(int argc, char *argv[]) {
	// initalize found_pair array of type struct Pair * with enough memory to contain one struct Pair.
	struct Pair *found_pairs = calloc(1, sizeof(struct Pair));
	// how many unique pairs we've found.
	int number_of_pairs = 0;

	// check to make sure that memory was allocated for found_pairs[] successfully, complain and get out of the program if not.
	if(found_pairs == NULL)
	{
		fprintf(stderr, "%s Error: Fatal error allocating memory for digraph pairs.\n", argv[0]);
		return 2;
	}

	// We need atleast two arguments, argv[0] is the program name and all subsequent arguments are file names to process.
	if(argc < 2) {
		fprintf(stderr, 
			"%s Error: Atleast one filename needed.\n"
			"Usage: %s <file1> [...] <fileN> \n", 
			argv[0], argv[0]);
		free(found_pairs);			
		return 1;
	}

	// Loop through the arguments excluding the program name and process each one.
	for(int i = 1; i < argc; i ++) {
		FILE *filehandle = fopen(argv[i], "r");

		// File couldn't be opened, complain and shut it all down.
		if(filehandle == NULL) {
			fprintf(stderr, 
			"%s Error: file %s could not be opened.\n",
			argv[0], argv[i]);
			free(found_pairs);		
			return 3;
		}


		// we'll read a character into c
		int c;
		char digraph[2] = {' ', ' '};	//current digraph, initiating with invalid spaces.	
		while((c = tolower(fgetc(filehandle))) != EOF) // read into c until we hit EOF.
		{
			digraph[0] = digraph[1]; // shift the second character of the digraph into the first.
			digraph[1] = c; // put the new c into the second character slot.
			if(!isalpha(digraph[0]) || !isalpha(digraph[1])) // if either character is not an alpha character then go to the next iteration of the loop.
				continue;

			// Check if the current digraph is in the array of previously found digraphs. If not then lets add it to the list.
			if(!who_in_whoville(digraph, number_of_pairs, found_pairs)){ 
				number_of_pairs++;
				found_pairs = realloc(found_pairs, sizeof(struct Pair) * number_of_pairs); // reallocate memory to fit a new digraph pair.

				 //if we don't get the memory we need, shut it all down.
				if(found_pairs == NULL) {
					fprintf(stderr, "%s Error: Fatal error reallocating memory for digraph pairs.\n", argv[0]);
					fclose(filehandle);
					free(found_pairs);
					return 4;					
				} else {
					// We got the memory so add the values to the appropriate fields.
					found_pairs[number_of_pairs - 1].first = digraph[0];
					found_pairs[number_of_pairs - 1].second = digraph[1];
					found_pairs[number_of_pairs - 1].count = 1;
				}
			}
		}
		fclose(filehandle);
	}

	// We're done processing all the file so print out the pairs and the frequency which they were found.
	for(int i = 0; i < number_of_pairs; i ++) {
		printf("%c%c %d\n", found_pairs[i].first, found_pairs[i].second, found_pairs[i].count);
	}

	free(found_pairs);
	return 0;
}

// function who_in_whoville searches for an element (digraph in our case) in the array of elements (digraphs in our case) and
// returns true if it was found. It takes care of incrementing the appriate counter.
bool who_in_whoville(char who_to_find[2], int whoville_population, struct Pair whoville[]) {
	bool who_found = false; // assume we won't find the digraph we're looking for.

	// If there are no elements in the set then we need to add our first one, wooooooo
	if(whoville_population == 0) {		
		whoville[0].first = who_to_find[0];
	    whoville[0].second = who_to_find[1];
	    whoville[0].count = 1;

	// There is already atleast one element so lets check if we've seen it before.
	} else {
		// Loop through the elements
		for(int i = 0; i < whoville_population; i++)
		{
			// If we found a match then increment the appropriate counter, mark the mission a success and lets get out of here. 
			if (who_to_find[0] == whoville[i].first && who_to_find[1] == whoville[i].second) {
				whoville[i].count++;
				who_found = true;
				break;
			} 
		}
	}

	// Return whether or not the element was found.
	return who_found;
}
