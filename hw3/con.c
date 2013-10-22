/*
* Name: Dean Bisogno
* Course: CS 156
* Purpose: Homework 3, and to do some converstions: score to letter grade and integer to astrological signs. Along with a nice help menu.
* Date: October 21, 2013
*/

#include <stdio.h>

//Required functions. Names are self-explainatory.
void print_menu();
void print_sign(int index);
char score_to_grade(double score);

int main() {
	char letter;
	int astrologicalIndex;
	double score;
	char enter;

	printf("Let's convert stuff!\n");
	do {
		printf("Do what? ");
		scanf("%c%c", &letter, &enter);

		switch(letter) {
			case 'h':       // Print the menu when user enters `h`.
			   print_menu();
			   break;
			case 'a':       // Get integer, pass to print_sign which prints the name of the corresponding astrological sign.
			   printf("What sign? ");
			   scanf("%d%c", &astrologicalIndex, &enter);
			   print_sign(astrologicalIndex);
			   break;
			case 's':      // Get floating-point score, pass to score_to_grade and print conversion.
			  printf("What score? ");
			  scanf("%lf%c", &score, &enter);
			  printf("%lf corresponds to %c\n", score, score_to_grade(score));
			  break;
			case 'q':      // Allow do-while loop to exit
			   break;
			default:       // User inputn ot recognized, print warning.
			   printf("Invalid command '%c'; 'h' for help.\n", letter);
			   break;
		}

	} while(letter != 'q');

	return 0;
}

// Prints the menu.... not much more to say about it.
void print_menu() {
	printf("q - quit\nh - help\na - print the astrological sign for that number\ns - print the grade for a given score\n");
}

/*
*	Function print_sign
*   Returns void
*   Argument: (int)index 
*   `(int)index` is mapped in the following way
*   1 - Aries
*   2 - Taurus
*   3 - Gemini
*   4 - Cancer
*   5 - Leo
*   6 - Virgo
*   7 - Libra
*   8 - Scorpio
*   9 - Sagittarius
*  10 - Capricorn
*  11 - Aquarius
*  12 - Pisces
*  Any other integer is mapped to UNKNOWN.
*/
void print_sign(int index) {
    printf("%d is ", index);
    // Test each known integer to print the mapped astrological sign name.
	switch(index) {
		case 1:
		  printf("Aries\n");
		  break;
		case 2:
		  printf("Taurus\n");
		  break;
		case 3:		
		  printf("Gemini\n");
		  break;
		case 4:
		  printf("Cancer\n");
		  break;
		case 5:
		  printf("Leo\n");
		  break;
		case 6:
		  printf("Virgo\n");
		  break;
		case 7:
		  printf("Libra\n");
		  break;
		case 8:
		  printf("Scorpio\n");
		  break;
		case 9:
		  printf("Sagittarius\n");
		  break;
		case 10:
		  printf("Capricorn\n");
		  break;
		case 11:
		  printf("Aquarius\n");
		  break;
		case 12:
		  printf("Pisces\n");
		  break;
		default:
		  printf("UNKNOWN\n");
		  break;
	}

}

/*
*  Function score_to_grade
*  Returns: char based on input
*  Arguement: (double)percentage
*  `(double)percentage` is mapped to the return char in the following way
*  score >= 90 returns `A`
*  score >= 80 returns `B`
*  score >= 70 returns `C`
*  score >= 60 returns `D`
*  score >  0  returns `F`
*  score <= 0  returns `Z`
*/
char score_to_grade(double percentage) {
	if(percentage >= 90)
		return 'A';
	else if(percentage >= 80)
		return 'B';
	else if(percentage >= 70)
		return 'C';
	else if(percentage >= 60)
		return 'D';
	else if(percentage > 0)
		return 'F';
	else
		return 'Z';

}