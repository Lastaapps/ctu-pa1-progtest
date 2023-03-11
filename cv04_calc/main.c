
#include <stdio.h>
#include <math.h>

void printError();

int main(int argsCount, char **args) {

	printf("Zadejte vzorec:\n");

	double number1 = -1.0, number2 = -1.0;
	char operation = '\0', equals = '\0';
	
	//reading input - double operator double forced =
	int valid = scanf(" %lf %c %lf %c", &number1, &operation, &number2, &equals);

	//basic input intergity
	if (valid != 4) {
		printError();
		return 2;
	}

	if (equals != '=') {
		printError();
		return 3;
	}

	//checks for the special invalid values
	if (number1 == NAN || number1 == -NAN || number1 == INFINITY || number1 == -INFINITY 
			|| number2 == NAN || number2 == -NAN || number2 == INFINITY || number2 == -INFINITY) {

		printError();	
		return 6;
	}


	double result;

	// Math is math
	if (operation == '+') {
		result = number1 + number2;

	} else if (operation == '-') {
		result = number1 - number2;

	} else if (operation == '*') {
		result = number1 * number2;

	} else if (operation == '/') {

		// dividing by Ovcacek is never fun
		if (number2 == 0.0) {
			printError();
			return 5;
		}

		//trunc values to simulate integer like division
		result = trunc(number1 / number2);

	} else {

		//invalid operator
		printError();
		return 4;
	}

	//print output
	printf("%lg\n", result);

	return 0;
}

/**
 * prints an error message
 */
void printError() {
	printf("Nespravny vstup.\n");
}

