/*
* Name: Dean Bisogno
* Course: CS 156
* Purpose: Homework 4, Some file action.
* Date: October 28, 2013
*/

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#define FILENAMESIZE 51

// Function prototypes, comments are with function declarations.
void print_menu();
void print_file(char inputFilename[]);
void print_file_info(char inputFilename[]);
int  check_filename(char inputFilename[]);

int main() {
	char cmd;
	char enter;
	char filename[FILENAMESIZE];

	print_menu();
	do {
		printf("Action: ");
		scanf("%c%c", &cmd, &enter);
		switch(cmd) {
			case 'q':
			  // Let it all end.			
			  break;
			case 'm':
			  print_menu(); // it does what it sounds like it does.
			  break;
			case 'v':
			  printf("Filename: ");
			  fgets(filename, sizeof(filename), stdin); // Get a filename
			  filename[strlen(filename) - 1] = '\0'; // Chop the newline off
			  if(check_filename(filename)) // Check it has a .txt at the end.
			  	print_file(filename); // "cat" the file out.
			  break;
			case 'i':
			  printf("Filename: ");
			  fgets(filename, sizeof(filename), stdin); // Get a filename
			  filename[strlen(filename) - 1] = '\0'; // chop the newline off
			  if(check_filename(filename)) // Check that it has a .txt at the end
			    print_file_info(filename); // Give some stats about the file.
			  break;
			default: // Unrecognized action.
			  printf("Invalid action, press 'm' for menu of available actions.\n"); 
			  break;
		}
	}while(cmd != 'q');

	printf("That is all.\n");
	return 0;
}
/*
*  This prints the command menu
*/
void print_menu() {
	printf("m: print this menu\n"
    "v: view a text file\n"
    "i: get information about a text file\n"
    "q: quit\n");
}

/*
*  Return true is ending in `.txt` return false if ending in anything else.
*/
int check_filename(char inputFilename[]) {
	// A pointer for the location of the '.' in the filename.
	char *fileExtPtr;

	// If this isn't true then we don't have a '.'
	if((fileExtPtr = strchr(inputFilename, '.')) != NULL) {
		int extensionLength = strlen(fileExtPtr); // Need the length of the tail of the string after and including the '.'.
		char fileExtension[extensionLength + 1]; // We'll store the extension in here.
		strcpy(fileExtension, fileExtPtr); // Copy it in... probably not necessary but it makes for an easy comparison.
		// Loop through and make each later upper-case.
		for(int i = 0; fileExtension[i] != '\0'; i++)
			fileExtension[i] = toupper(fileExtension[i]);

		// Check to see if we have the right extension.... we could probably compare character by character while we're 
		// making it all upper-case but then we'd need to do some boolean arithmetic and this is just more straightforward.
		if(strcmp(fileExtension, ".TXT") == 0) 
			return 1;
	}
	printf("%s doesn't end in .txt\n", inputFilename);	
	return 0;
}

// Prints out the whole file a la `cat`
void print_file(char inputFilename[]) {
	FILE *fileHandle = fopen(inputFilename, "r");
	if(fileHandle != NULL) {
		char line[100] = ""; //we'll read in 99 characters at a time.
		while(fgets(line, sizeof(line), fileHandle) != NULL) {
			printf("%s", line);
		}
		// If the file didn't end with a newline then we need to print one.
		if(line[strlen(line)-1] != '\n' && strlen(line) > 0)
			printf("\n");

		fclose(fileHandle);
	}
	else
		printf("problem opening %s\n", inputFilename);
}

/*
*  Prints file info, namely: 
*  - number of lines
*  - number of vowels
*  - number of consonants
*  - number of occurances of `doc`
*/
void print_file_info(char inputFilename[]) {
	FILE *fileHandle = fopen(inputFilename, "r");
	if(fileHandle != NULL) {

		// these four are pretty self-explanitory
		int vowels = 0;   
		int consonants = 0;       
		int numlines = 1; // If it ain't empty it's gotta have a line. 
		int numdocs = 0; 

		// current character will be stored here
		int c;

		// we will use the value of doc to figure out if the characters 'd', 'o', and 'c' have occured consequtively
		int doc = 0;

		// This flag gets set if there is anything in the file.
		int not_empty_flag = 0;


		// Loop through each character of the file until we hit EOF.
		while ((c = fgetc(fileHandle)) != EOF) {
			not_empty_flag = 1;
			c = toupper(c);
			switch(c) {
				case 'A':
				case 'E':
				case 'I':
				case 'U':
				  vowels++;
				  break;
				case 'D':
				  consonants++;
				  if(0 == doc) // if `doc` equals 0 then we're searchign for a 'd'. Increment `doc` so that we can look for an 'o'.
				    doc++;
				  break;
				case 'O':
				  vowels++;
				  if(1 == doc) // if doc is 1 then our last character was a 'd', we found an 'o' so increment doc again so we can look for a 'c'
				  	doc++;
				  else
				  	doc = 0;
				  break;
				case 'C':
				  consonants++;
				  if(2 == doc) // if doc is 2 then we have seen 'do' and just need a 'c', increment doc to 3 so we know that we've found all 3 character in a row.
			    	doc++;
			      else
			      	doc = 0;
				  break;
				case '\n':
				  numlines++;
				  break;
				default:
				  doc = 0;
				  if(isalpha(c)) // if not a vowel or a newline then it is a consonant or some other symbol. If it's an alpha then it must be a consonant.
				   consonants++;
				  break;
			}
			if (3 == doc) {
				numdocs++;
				doc = 0;
			}
		}

		// If the file had anythign in it, then print the stats otherwise, print the other message.
		if(not_empty_flag)
			printf(
				"Lines: %d\n"
				"Vowels: %d\n"
				"Consonant: %d\n"
				"Docs: %d\n",
				numlines, vowels, consonants, numdocs);
		else
			printf("That file is empty.\n");

		fclose(fileHandle);
	}
	else // Handle the case that the file couldn't be opened (maybe it doesn't exist or we don't have permission).
		printf("problem opening %s\n", inputFilename);

}



