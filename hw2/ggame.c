/*
	Dean Bisogno
	October 9, 2013
*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>



int checkGuess(int _goal, int _guess, int _numberOfGuesses, int _temp) {

	if(_goal == _guess)
		printf("%d is right in %d guesses.\n", _guess, _numberOfGuesses);
	else {
		printf("%d is ", _guess);
		switch(_temp) {
			case 0:
				printf("scalding.\n", _guess);
				break;
			case 1: 
			    printf("hot.\n", _guess);
			    break;
			case 2:
			    printf("warm.\n", _guess);
				break;
			case 3:
			    printf("chilly.\n", _guess);
				break;
			case 4:
			    printf("cold.\n", _guess);
				break;
			case 5:
			    printf("freezing.\n", _guess);
				break;
		}
	}

	return 0;
}

int getGuess(){
	int _guess;
	printf("What's your guess? ");
	scanf("%d", &_guess);

	if((_guess < 1 || _guess > 100)) 
	{
		printf("%d is not 1-100.\n", _guess);
		return getGuess();
	}
	else
	{
		return _guess; // this is the condition that stops the recursion
	}
}

int main() {
	int goal, guess, numberOfGuesses, deltaG, tempID;

	srand(time(NULL));
	goal = rand() % 100 + 1;
	numberOfGuesses = 0;


	printf("I have thought of a number, 1-100.\n");

	while (guess != goal)
	{
		numberOfGuesses++;
		guess = getGuess();

		deltaG = (guess > goal) ? guess - goal : goal - guess;
		
		if (2 >= deltaG)
			tempID = 0;
		else if (10 >= deltaG)
			tempID = 1;
		else if (20 >= deltaG)
			tempID = 2;
		else if (30 >= deltaG)
			tempID = 3;
		else if (50 >= deltaG)
			tempID = 4;
		else if (50 < deltaG) 
			tempID = 5;

		checkGuess(goal, guess, numberOfGuesses, tempID);
	}

	return 0;
}