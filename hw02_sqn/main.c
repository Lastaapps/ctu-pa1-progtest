
#include <stdio.h>
#include <stdlib.h>

//enables debug printing
//#define DEBUG

int readData(long long int *index, int *base);
void manageInput(long long int index, int base);
long long int digits(int n, int b);
long long int position(int n, int b);
int safeFloor(double number);
void printNumber(long long int number, int base);
long long int intPow(int x, int exponent);


int main(void) {

	printf("Pozice a soustava:\n");
	
	long long int index;
	int base;

	while(readData(&index, &base)) {
		manageInput(index, base);
	}

	return 0;
}

/**
 * read data from stdin and check their validity
 * if the input is invalid (not in the case of EOF) it prints error message
 * @return 0 if the input is valid
 */
int readData(long long int *index, int *base) {

	int code = scanf("%lli %d", index, base);
	if (code < 0) {
		return 0;
	}else if (code != 2 || *index < 0 || *base < 2 || *base > 36) { 
		printf("Nespravny vstup.\n");
		return 0;
	} else {
		return 1;
	}
}

/**
 * Show the output for input given, does all the magic
 */
void manageInput(long long int index, int base) {
	
	//how many digits - 1 does the number have
	int i = 0;
	while (1) {

		long long int d = digits(i, base);

		//breaks the cycle if we have found i
		//or if d has overflown
		if (d > index || d < 0)
			break;

		i++;

#ifdef DEBUG
		printf("Digits: %lld\n", d);

		//to revend endless loops
		if (i > 42)
			exit(42);
#endif
	}

	long long int starting = digits(i - 1, base);
	long long int missing = index - starting;
	long long int toAdd = missing / (i + 1);
	int digit = missing % (i + 1);
	long long int output = position(i, base) + toAdd;

#ifdef DEBUG
	printf("index: %lld\n", index);
	printf("base: %d\n", base);
	printf("i: %d\n", i);
	printf("starting: %lld\n", starting);
	printf("missing: %lld\n", missing);
	printf("toAdd: %lld\n", toAdd);
	printf("digit: %d\n", digit);
	printf("output: %lld\n", output);
#endif

	printNumber(output, base);
	printf("\n");


	//prints spaces to offset ^ number pointer
	for (int j = 0; j < digit; j++) {
		printf(" ");
	}

	printf("^\n");

}

/**
 * @param n - number o digits of a number with this index - 1, for 10 it's 1
 * @param b - base
 * @return number of digits passed for number of digits
 */
long long int digits(int n, int b) {

	if (n < 0)
		return 0;

	//allows for more optimal computation
	n += 1;

	long long int bPowered = intPow(b, n);
	long long int bMorePowered = bPowered * b;

	return (b + n * bMorePowered - (n + 1) * bPowered) / (b - 1);

	/*long long int bPowered = intPow(b, n + 1);
	long long int bMorePowered = bPowered * b;

	return 1 + (1 + bMorePowered - 2 * bPowered + n * (bMorePowered - bPowered)) / (b - 1);
	*/
}

/**
 * @return the smallest number with the number of digits given
 */
long long int position(int n, int b) {
	return n > 0 ? intPow(b, n) : 0;
}

/**
 * prints the number with base given
 */
void printNumber(long long int number, int base) {

	if (number == 0) {
		printf("0");
		return;
	}

	//number of digits to print
	int n = 0;
	long long int toDivide = number;

	while (toDivide > 0) {
		n++;
		toDivide /= base;
	}

	//go thought all the digits from start to end
	long long int boostedBase = intPow(base, n);

	while (boostedBase >= base) {
		
		long long int lowerBoosted = boostedBase / base;
		int digit = (number % boostedBase) / lowerBoosted;

		if (digit <= 9)
			printf("%d", digit);
		else
			printf("%c", digit - 10 + 'a');

		boostedBase = lowerBoosted;
	}
}

/**
 * normal pow function, but uses ints internally, so it's safe, not as double
 * does't work with exponents < 0
 */
long long int intPow(int x, int exponent) {

	long long int result = 1;

	for (int i = 0; i < exponent; i++)
		result *= x;

	return result;
}




