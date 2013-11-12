/*
* Name: Dean Bisogno
* Course: CS 157
* Purpose: Homework 1, some currency conversion.
* Date: November 11, 2013
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_FILE_LENGTH 50
#define MAX_LINE_LENGTH 81
#define MAX_CURRENCY_LENGTH 10

int process_file(int numArgs, char *arguments[]);
void sconvert_to_upper(char stringtoconvert[]);

int main(int argc, char *argv[]) {
	// If we have fewer than 3 arguments (including the name of the program) or 
	// the number of arguements (including the name of the program) is even,
	// then we have an incomplete command. 
	if (argc < 3 || (argc % 2) != 0 ) 
	{
		fprintf(stderr, 
			"Error in %s.\n"
			"USAGE: %s <file> <quantity> <currency> [...] <quantityN> <currencyN>\n",
			argv[0], argv[0]);

		return 1;
	}
	return process_file(argc, argv);
}

// Accepts the list of arguments and the number of arguments.
// - Opens the file in argument[1], reads it out into a variable.
// - For each currency type in the arguments it searches for it int the file and complains if it can't find it.
//   if it can find it then it search forward for characters other than space until it gets to the new line.
//   Converts those characters to a double then prints the conversion with the argument that came before the currency name.
int process_file(int numArgs, char *arguments[]) {

	// Open for reading, and complain if the file pointer returns null (error opening... file doesn't exist or permissions error).
	FILE *fileHandle = fopen(arguments[1], "r");
		if(fileHandle != NULL) {

	        //We will stick the file contents here. Probably more memory than searchign through but it allows for osme more inuitive code ahead.
	        //We know the file will at most be the max number of lines (50) times the max number of characters per line (80 + 1 for new line.) plus 1 for the string temrination character.
			char file_contents[MAX_FILE_LENGTH * MAX_LINE_LENGTH + 1] = "";

			//each line we read we'll stick here then concatenate with the other file contents. +1  for null character.
			char current_line[MAX_LINE_LENGTH + 1] = "";

			//Read through the file and push each set of text read into file_conents.
			while(fgets(current_line, MAX_LINE_LENGTH, fileHandle) != NULL)
				strcat(file_contents, current_line);

			// We will stick a pointer to the position of each currency here
			char *currency_location;

			// We'll loop through the arguments passed to the program starting at argument 3 which is the first currency name. 
			// Each subsequent currency type is in the succeeding odd (5, 7, ..., 11, ..., and so on) arguments.
			for(int i = 3; i < numArgs; i = i + 2)
			{
				// Convert the current currency to uppercase for easy comparing.
				sconvert_to_upper(arguments[i]);
				// Get a pointer to the position of the current currency.
				currency_location = strstr(file_contents, arguments[i]);
				// If the currency wasn't found in the file, complain.
				if(currency_location == NULL)
				{
					fprintf(stderr, 
						"Error in %s.\n"
						"Could not locate currency \'%s\' in file \'%s\'.\n",
						arguments[0], arguments[i], arguments[1]);
					continue;
				}


				// This is how much of the currency we need to convert, stored in the argument preceding the current currency.
				double quantity = atof(arguments[i-1]);

				//The actual length of the currency name. USD = 3.
				int currencyLength = strlen(arguments[i]);

				//We will store the string version of the currency conversion divisor.
				// We know that it is all the characters in the line that don't compose the name of the currency (which is atleast one character) and atleast one space.
				char conversionString[MAX_LINE_LENGTH - 1] = "";

				// strcat is more friendly if we use a string so the first index
				// will be the current character and the second alwasy the string termination character.
				char c[2] = "";

				//We need ot check if we actually found a valid currency.
				// If the character immediately 
				if((*(currency_location + currencyLength) != ' ' && *(currency_location + currencyLength) != '\t')
					|| (currency_location != &file_contents[0] && (*(currency_location - 1) != '\n'))) {
						fprintf(stderr, 
							"Error in %s.\n"
							"Could not locate currency \'%s\' in file \'%s\'.\n",
							arguments[0], arguments[i], arguments[1]);
							continue;
				}
				// instantiate j is the currency length so we're starting at the character after the currency name.
				// Check to make sure we aren't on a \n, the end of the line.
				// Go to the next character index.
				for(int j = currencyLength; (c[0] != '\n') && (j+currencyLength < strlen(file_contents)); j++) {
					// set c[0] to be the character j index past the end of the currency name
					c[0] = *(currency_location + j);

					// if c isn't a space push it onto the end of the currency string.
					if(c[0] != ' ')
						strcat(conversionString, c);
				}

				// Print the conversion.
				printf("%.2lf %s is $%.2lf\n", quantity, arguments[i], quantity/atof(conversionString));

			}
			fclose(fileHandle);
		}else{
			// Print and error if the file containing conversions couldn't be opened.
			fprintf(stderr, 
				"Error in %s.\n"
				"Could not open file %s.\n",
				arguments[0], arguments[1]);

			return 2;
		}
		return 0;
}

// Convert the given string to uppercase.
void sconvert_to_upper(char stringtoconvert[]) {
	for(int i=0; i < strlen(stringtoconvert); i++)
		stringtoconvert[i] = toupper(stringtoconvert[i]);
}
