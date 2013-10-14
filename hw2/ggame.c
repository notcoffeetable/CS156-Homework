/*
	CS156 HW2
	Author: Dean Bisogno
	Date: 10/14/2013
	Purpose: Play a guessing game as defined by hw2 specification. 
	- Calculate a random int between 1 and 100 (inclusive).
	- Accept guesses form user.
	- Give a message based on their guess.

	Note to grader: Set goal on line 98.
*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/*
	Function mapTemp 
	Accepts two integer arguments:
	int _goal  - Target value.
	int _guess - User's attempt at guessing target value.

	Returns an integer which indicates which message should be printed.
	Seven possible integers:
	0 - Guess matches goal. Win game
	1 - Guess within "scalding" range of goal.
	2 - Guess within "hot" range of goal.
	3 - Guess within "warm" range of goal.
	4 - Guess within "chilly" range of goal.
	5 - Guess within "cold" range of goal.
	6 - Guess so far from goal that is is "freezing."
*/
int mapTemp(int _goal, int _guess) {

		int deltaG = (_guess > _goal) ? _guess - _goal : _goal - _guess;
		
		if (0 == deltaG)
			return 0;
		else if (2 >= deltaG)
			return 1;
		else if (10 >= deltaG)
			return 2;
		else if (20 >= deltaG)
			return 3;
		else if (30 >= deltaG)
			return 4;
		else if (50 >= deltaG)
			return 5;
		else if (50 < deltaG) 
			return 6;
}

/*
	Function checkGuess
	Accepts three arguements:
	int _goal            - Target value.
	int _guess           - User guess at target value.
	int _numberOfGuesses - How many times user has guessed (including out of range guesses).

	Returns two possible integers (true/false):
	0 - Guess and goal do not match and the appropriate temperatuye based message has been printed.
	1 - Guess matches goal and winning message has been printed.
*/
int checkGuess(int _goal, int _guess, int _numberOfGuesses) {

	int tempID = mapTemp(_goal, _guess);

	if(0 == tempID) {
		printf("%d is right in %d guesses.\n", _guess, _numberOfGuesses);
		return 1;
	}
	else {
		printf("%d is ", _guess);
		switch(tempID) {
			case 1:
				printf("scalding.\n", _guess);
				break;
			case 2: 
			    printf("hot.\n", _guess);
			    break;
			case 3:
			    printf("warm.\n", _guess);
				break;
			case 4:
			    printf("chilly.\n", _guess);
				break;
			case 5:
			    printf("cold.\n", _guess);
				break;
			case 6:
			    printf("freezing.\n", _guess);
				break;
		}
	}

	return 0;
}

/*
	Function getGuess
	Accepts zero arguments.

	Returns an integer which is a guess scanned in from user.
*/
int getGuess(){
	int _guess;
	printf("What's your guess? ");
	scanf("%d", &_guess);
	return _guess;
}

int main() {
	int goal, guess, numberOfGuesses;

	// Generate random integer between 1 and 100 inclusively.
	srand(time(NULL));
	goal = rand() % 100 + 1;

	numberOfGuesses = 0;
	guess = 0;


	printf("I have thought of a number, 1-100.\n");

	/*
	   Main program loop.
	   - Increment numberofGuesses and accept a guess.
	   - Check that value is in the correct range. If not, start over.
	   - Check valid guess and print appropriate message with checkGuess.
	   - End loop and allow progrtam to exit if user guesses goal.
	*/
	while (1)
	{

		numberOfGuesses++;	
		guess = getGuess();

		if (guess < 1 || guess > 100)
		{
			printf("%d is not 1-100.\n", guess);
			continue;
		}

		if(checkGuess(goal, guess, numberOfGuesses))
			break;
	}

	return 0;
}