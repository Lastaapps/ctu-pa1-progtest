
#include <stdio.h>

int readColor(int *r, int *g, int *b);
void printColor(int r, int g, int b);
char validateColor(int x);
void printError();


int main(int argCount, char **args) {

	int r, g, b;
	r = g = b = -1;

    int result = readColor(&r, &g, &b);

	if (result != 0) {
		printError();
		return result + 10;
	}

	printColor(r, g, b);

	return 0;
}

/**
 * Reads a color from stdin
 * @return result code (0 == Success, other == ERROR)
 */
int readColor(int *r, int *g, int *b) {

	printf("Zadejte barvu v RGB formatu:\n");
	
	//to prevent stdin end before the last required character - the bracket
	char bracket = '\0';

	int result = scanf(" rgb ( %3d , %3d , %3d %c", r, g, b, &bracket);

	if (result != 4) {
		return 2;
	}

	if (validateColor(*r) && validateColor(*g) && validateColor(*b) && (bracket == ')') != 0) {
		return 0;	
	} else {
		return 3;
	}
}

/**
 * prints the color given if the HEX format
 */
void printColor(int r, int g, int b) {
	printf("#%02X%02X%02X\n", r, g, b);	
}

/**
 * @return if x is between min and max
 */
char validateColor(int x) {
	return (0 <= x) && (x <= 255);
}

/**
 * Prints an error message
 */
void printError() {
	printf("Nespravny vstup.\n");
}


