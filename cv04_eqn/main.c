
#include <stdio.h>
#include <math.h>

//#define DEBUG

int inRange(double main, double checked, double range);
void printError();

int main(int argsCount, char **args) {

	printf("Zadejte rovnici:\n");

	double number1 = NAN, number2 = NAN, result = NAN;
	char operation = '\0';

	//reading input - double operator double forced =
	int valid = scanf(" %lf %c %lf = %lf", &number1, &operation, &number2, &result);


	//basic input intergity
	if (valid != 4) {
		printError();
		return 2;
	}

	//checks for the special invalid values
	if (number1 == NAN || number1 == -NAN || number1 == INFINITY || number1 == -INFINITY 
			|| number2 == NAN || number2 == -NAN || number2 == INFINITY || number2 == -INFINITY
			|| result == NAN || result == -NAN || result == INFINITY || result == -INFINITY) {

		printError();   
		return 6;
	}


	double combined;

	// Math is math
	if (operation == '+') {
		combined = number1 + number2;

	} else if (operation == '-') {
		combined = number1 - number2;

	} else if (operation == '*') {
		combined = number1 * number2;

	} else if (operation == '/') {

		// dividing by Ovcacek is never fun
		if (number2 == 0.0) {
			printError();
			return 5;
		}

		//trunc values to simulate integer like division
		combined = trunc(number1 / number2);

	} else {

		//invalid operator
		printError();
		return 4;
	}

#ifdef DEBUG
	//debugging printing
	printf("%lf\n", combined);
	printf("%lf\n", result);
	printf("%lf\n", combined - result);
#endif

	//to fix problems with double inaccuary, 
	//the numbers must match with difference not greate than range percent
	double range = pow(10, -10) / 100;

	//print if the eqn is right or not
	if (inRange(result, combined, range) && inRange(combined, result, range)) {
		printf("Rovnice je spravne.\n"); 

	} else {
		//the eqn is wrong
		printf("%lg != %lg\n", combined, result);
		return 1;
	}

	return 0;
}

/**
 * @return if the checked number is in the range around main, meaning if range is in main +- range% interval
 */
int inRange(double main, double checked, double range) {
	//inverts comparission for negative numbers
	double mainNegativity = main < 0.0 ? -1.0 : 1.0;

	return (main * (1 - mainNegativity * range) <= checked) && (checked <= main * (1 + mainNegativity * range));
}

//prints the error message for a wrong input
void printError() {
	printf("Nespravny vstup.\n");
}

