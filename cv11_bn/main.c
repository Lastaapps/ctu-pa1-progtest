#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

uint8_t readNumbers(uint8_t * n, uint16_t * k);
void exploreBinary(uint8_t n, uint16_t k);
void exploreBinaryImpl(uint16_t * total, const uint8_t n, const uint16_t k, size_t num);
uint16_t getDepth(size_t num);
void printBinary(size_t num);
uint8_t match(size_t num, uint16_t k);


int main(void) {

	uint8_t n;
	uint16_t k;

	if (!readNumbers(&n, &k)) {
		printf("Nespravny vstup.\n");
		return 1;
	}

	exploreBinary(n, k);

	return 0;
}

uint8_t readNumbers(uint8_t * n, uint16_t * k) {

	int8_t tmpN;
	int16_t tmpK;

	printf("Pocet cifer:\n");
	if (scanf(" %hhd", &tmpN) != 1 || tmpN <= 0 || tmpN > (int16_t)(8 * sizeof(size_t))) {
		return 0;
	}

	printf("Max. stejnych po sobe:\n");
	if (scanf(" %hd", &tmpK) != 1 || tmpK <= 0) {
		return 0;
	}

	*n = tmpN;
	*k = tmpK;

	return 1;
}

void exploreBinary(uint8_t n, uint16_t k) {

	uint16_t total = 0;

	//for (size_t i = 1; i < 10000000; i += i)
		//printf("%4ld, %d\n", i, getDepth(i));

	exploreBinaryImpl(&total, n, k, 1);

	printf("Celkem: %hd\n", total);
}

void exploreBinaryImpl(uint16_t * total, const uint8_t n, const uint16_t k, size_t num) {

	uint16_t depth = getDepth(num);
	//printf("Depth: %hd\n", depth);

	if (depth > n || match(num, k))
		return;

	*total += 1;
	printBinary(num);
	printf("\n");

	if (depth == 8 * sizeof(num)) return;

	num *= 2;
	exploreBinaryImpl(total, n, k, num);
	exploreBinaryImpl(total, n, k, num + 1);

}

uint16_t getDepth(size_t num) {
	size_t i = 1;
	uint16_t position = 0;

	i <<= sizeof(i) * 8 - 1;

	for (; (i & num) == 0; i >>= 1, position++);

	return sizeof(i) * 8 - position;
}

void printBinary(size_t num) {
	size_t i = 1;

	i <<= sizeof(i) * 8 - 1;

	for (; (i & num) == 0; i >>= 1);

	for (; i != 0; i >>= 1) {
		printf("%c", i & num ? '1' : '0');
	}
}

uint8_t match(size_t num, uint16_t k) {

	uint16_t mask = 1;
	for (uint16_t i = 0; i < k; i++)
		mask = 2 * mask + 1;

	return ((num & mask) == 0) || ((~num & mask) == 0);
}




