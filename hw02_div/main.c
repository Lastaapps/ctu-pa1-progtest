
#include <stdio.h>
#include <stdlib.h>

void readNumbers(int *divident, int *divisor);
char numberDigits(int number);
char getDigitAt(char index, int number, char length);
int tenPow(char exponent);
int min(int x, int y);


//#define DEBUG

int main(void) {

	int divident, divisor;
	
	readNumbers(&divident, &divisor);

	int result = divident / divisor;

	printf(" %d : %d = %d", divident, divisor, result);

	//number of digits of divident and result
	char divDigits = numberDigits(divident);
	char resultDigits = numberDigits(result);

	//remaining after dividing
	int remaining = divident;

	for (char i = 0; i < resultDigits; i++) {
		
		//10^exponent gives the position of a result digit in reslut
		char exponent = resultDigits - 1 - i;
		char resultDigit = getDigitAt(i, result, resultDigits);

		int toSubtractPrint = resultDigit * divisor;
		int toSubtract = toSubtractPrint * tenPow(exponent);

		printf("\n%*d", divDigits + 1 - exponent, -1 * toSubtractPrint);

		remaining -= toSubtract;

		printf("\n%*d", min(divDigits + 2 - exponent, divDigits + 1), remaining / tenPow(exponent - 1));

	}

	printf(" zbytek\n");

	return 0;
}

/**
 * Read divident and divisor from stdin and validate them
 */
void readNumbers(int *divident, int *divisor) {

	printf("Zadejte dve cisla:\n");

	if (scanf(" %d %d", divident, divisor) != 2 || *divident < 0 || *divisor <= 0) {
		printf("Nespravny vstup.\n");
		exit(2);
	}
}

/**
 * @return number of digits in the number given
 * for 0 it returns 1
 */
char numberDigits(int number) {

	char digits = 1;

	while((number /= 10) != 0) {
		digits ++;
	}

	return digits;
}

/**
 * @return digit of the number given at the index from number start
 */
char getDigitAt(char index, int number, char length) {
	int tenTimes = tenPow(length - 1 - index);

	return (number / tenTimes) % 10;
}

/**
 * pows ten to the positive exponent given
 * for negative numbers and 0 it returns 1
 */
int tenPow(char exponent) {
	int value = 1;

	for (char i = 0; i < exponent; i++) {
		value *= 10;
	}

	return value;
}

/**
 * @return the smaller number from x and y given
 */
int min(int x, int y) {
	return x < y ? x : y;
}



