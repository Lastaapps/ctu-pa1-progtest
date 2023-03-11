
#include <stdio.h>

void printBorder(int fields, int size);

int main(void) {

	int fields, size;

	printf("Zadejte pocet poli:\n");
	if (scanf("%d", &fields) != 1 || fields <= 0) {
		printf("Nespravny vstup.\n");
		return 1;
	}

	printf("Zadejte velikost pole:\n");
	if (scanf("%d", &size) != 1 || size <= 0) {
		printf("Nespravny vstup.\n");
		return 2;
	}

	printBorder(fields, size);

	for (int line = 0; line < fields * size; line++) {
		printf("|");
		
		for (int i = 0; i < fields * size; i++) {
			if ((i / size + line / size) % 2) 
				printf("X");
			else
				printf(" ");
		}

		printf("|\n");
	}

	printBorder(fields, size);

	return 0;
}

void printBorder(int fields, int size) {
	printf("+");
	for (int i = 0;i < size * fields; i++) 
		printf("-");
	printf("+\n");
}

