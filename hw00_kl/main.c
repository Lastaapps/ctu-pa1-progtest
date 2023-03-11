
#include <stdio.h>

void printError();

int main(int argsCount, char **args) {
	
	//Hello there
	printf("ml' nob:\n");


	int input = -1;
	int result = scanf(" %1d", &input);

	//checks for valid input
	if (result != 1) {
		printError();
		return 2;
	}

	//checks input range
	if ((input <= 0) || (input > 5)) {
		printError();
		return 3;
	}

	printf("Qapla'\n");

	//print requested text
	if (input == 1) {
		printf("noH QapmeH wo' Qaw'lu'chugh yay chavbe'lu' 'ej wo' choqmeH may' DoHlu'chugh lujbe'lu'.\n");

	} else if (input == 2) {
		printf("Qu' buSHa'chugh SuvwI', batlhHa' vangchugh, qoj matlhHa'chugh, pagh ghaH SuvwI''e'.\n");

	} else if (input == 3) {
		printf("qaStaHvIS wa' ram loS SaD Hugh SIjlaH qetbogh loD.\n");

	} else if (input == 4) {
		printf("Ha'DIbaH DaSop 'e' DaHechbe'chugh yIHoHQo'.\n");

	} else if (input == 5) {
		printf("leghlaHchu'be'chugh mIn lo'laHbe' taj jej.\n");
	}

	return 0;
}

void printError() {
	printf("luj\n");
}

