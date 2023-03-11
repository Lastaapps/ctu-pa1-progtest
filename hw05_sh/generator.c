#include <stdio.h>
#include <stdlib.h>

int main(void) {

	printf("420\n");

	for (int i = 1; i < 100000; i++) {
		printf("+ %d\n", rand() % 10000);
	}

	printf("#\n");

	return 0;
}
