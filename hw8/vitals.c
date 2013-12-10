/*
* Name: Dean Bisogno
* Course: CS 157
* Purpose: Homework 3
* Date: December 2, 2013
*/

#include <stdio.h>
#include <stdlib.h>
#include "vitals.h"

int fileread = 0;
double *fileData;
int fileDataLength = 0;

// Prints and error and return an int to be used for exit status.
int print_error(char error[]) {
	fprintf(stderr, "Error in vitals.c: %s\n", error);
	return 1;
}

// Attempt to open a file for reading.
// If opening fails, pritn error and exit.
// Otherwise loop through each character, store then in a buffer and read out doubles.
int readfile(char *filename) {

	// Attempt to open the file for reading, otherwise just print error exit.
	FILE *filehandle = fopen(filename, "r");
	if(filehandle == NULL)
		return print_error("Error opening file.");
	
	fileData = malloc(fileDataLength * sizeof(double)); // We will store doubles from the file in here.
	int c; // Hold the current character here.
	char *buf = malloc(1 * sizeof(char)); // We will buffer up allowable characters in here.
	int i = 1; // Keep track of the length of buffer.

	// Make sure  we got memory for bug and filedata, if not complained.
	if(buf == NULL || fileData == NULL) {
		free(fileData);
		return print_error("Problem allocating memory.");
	}

	// Read characters in until we hit EOF. 
	while((c = fgetc(filehandle)) != EOF) {
		// If the character is not a seperator character then store it in the buffer.
		if(c != ' ' && c != '\n' && c != ',') {
			buf[i - 1] = c;
			i++;

			// Reallocate memory for the next character.
			// Check to make sure we got the memory.
			buf = realloc(buf, i * sizeof(char));
			if(buf == NULL) {
				free(fileData);
				return print_error("Problem allocating memory.");
			}

			// If a seperator character, then read the buffer for a double.
		} else {
			fileDataLength++;

			// Request more memory, check to make sure it succeeded, if not then free what we have and exit.
			fileData = realloc(fileData, fileDataLength * sizeof(double));			
			if(fileData == NULL) {
				free(fileData);
				free(buf);
				return print_error("Problem allocating memory.");
			}

			// Read the new double into fileData.
			sscanf(buf, "%lf", &fileData[fileDataLength - 1]);
			// printf("double: %lf\n", fileData[fileDataLength - 1]);

			// Reset all the buffer data to start storing up a new double.
			i=1;
			free(buf);
			buf = calloc(1, sizeof(char));
			if(buf == NULL) {
				free(fileData);
				return print_error("Problem allocating memory.");
			}

		}
	}

	// Flag the file read, free buffere data, and close the file.
	fileread = 1;
	free(buf);
	fclose(filehandle);
	return 0;
}

// Compare to doubles, inputs are pointers to doubles a and b. 
// If a is less than b return -1.
// If a is greater than b return 1.
// If a is equal to b return 0.
int compare(const void *av, const void *bv) {
        const double *a = av, *b = bv;
        if (*a < *b) return -1;
        if (*a > *b) return 1;
        return 0;
}

// Fail if the file has not been read yet.
// Otherwise return the median value of the data set.
double median() {
	if(!fileread)
		return print_error("File has not been read yet.");	

	qsort(fileData, fileDataLength, sizeof(double), compare);
	// for(int i = 0; i < fileDataLength; i++)
	// 	printf("filedata[%d]: %lf\n", i, fileData[i]);

	if((fileDataLength % 2) != 0) 
		 // If there are an odd number of items print the middle one.
		return fileData[(fileDataLength / 2)];
	else
		// If there is an even number of items print the average of the two middle ones.
		return (fileData[(fileDataLength / 2) - 1] + fileData[(fileDataLength / 2)]) / 2; 
}

// Fail if the file has not been read yet.
// Otherwise return the number of items in the data set.
int count() {
	if(!fileread)
		return  print_error("File has not been read yet.");

	return fileDataLength;
}

// If the file has not been read then fail.
// Otherwise free the memory the data is in and set data read variable state to false.
void release_memory() {
	if(!fileread)
		print_error("File has not been read yet.");

	fileread = 0;
	free(fileData);
}
