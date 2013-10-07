/*
	CS156 HW1
	Author: Dean Bisogno
	Date: 10/2/2013
	Purpose: To get 100% on homework 1 (oh, and to accept two integers and tell you some facinating facts about them).
	Revision 10/7/2013: Added some more comments.
*/
#include <stdio.h>

int main() 
{
	int arg1; // We will store the first number entered her
	int arg2; // The second number entered will be stored here.

	printf("Enter numbers: ");
	scanf("%d %d", &arg1, &arg2);

	// We don't do math with 4.
	if(arg1 == 4 || arg2 == 4) {
		printf("Bad luck!\n");
		return 0;
	}

	// Incase you forget what you typed in less than a second ago.
	printf("Your numbers are %d and %d\n", arg1, arg2);

	// Dividing by zero is impolite.
	if(0 == arg2) {
		printf("%d divided by zero: boom!\n", arg1);
	}else {
		// Going to use type casting so I don't need to store double/float versions of arg1 and arg2. I could use 
		// printf("%d divided by %d: %lf\n", arg1, arg2, (arg1 * 1.0) / arg2);
		// but that seems needlessly verbose. Much like this comment.
		printf("%d divided by %d: %lf\n", arg1, arg2, (double)arg1 / (double)arg2);
	}

	// Here we use the conditional ternary operator to save space. 
	// conditional ternary operator takes the form expression-to-eval-for-truthiness ? expression-to-execute-if-true : expression-to-execute-if-false;
	printf("Difference: %d\n", arg1 > arg2 ? arg1 - arg2 : arg2 - arg1);


	// You might be expecting a switch statement here, but I think switch feels clunky in this circumstance.
	if((arg1 % 7) == 0 && (arg2 % 7) == 0) {
		printf("Both are divisible by seven.\n");
	}else if((arg1 % 7) != 0 && (arg2 % 7) != 0) {
		printf("Neither is divisible by seven.\n");
	}else if((arg1 % 7) == 0 && (arg2 % 7) != 0) {
		printf("%d is divisible by seven, however, %d isn't.\n", arg1, arg2);
	}else if((arg1 % 7) != 0 && (arg2 % 7) == 0) {
		printf("%d isn't divisible by seven, but %d is.\n", arg1, arg2);
	}
	return 0;
}