#ifndef __PROGTEST__
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#endif /* __PROGTEST__ */



/**
 * Shifts array to right moving items from the end to start
 * @param[out] array array to rotate
 * @param[in] arrayLen the length of the array
 * @param[in] rotateBy how much should be the array shifted to the right, negative numbers mean rotation to the left
 */
void rotateArray ( int array [], int arrayLen, int rotateBy );
/**
 * Do shift, called from rotateArray
 * @param[out] array array to rotate
 * @param[in] arrayLen the length of the array
 * @param[in] rotateBy how much should be the array shifted to the right, negative numbers mean rotation to the left
 */
void doShift( int array[], int length, int shift);
/**
 * Finds the greates common divisor acording to Euclidean algorithm
 * @param[in] a the first number
 * @param[in] b the second number
 * @return a and b common divisor
 */
int greatestCommonDivisor(int a, int b);



void rotateArray ( int array [], int length, int rotateBy ) {

	if (length == 0)
		return;

	rotateBy = rotateBy % length;

	if (rotateBy == 0)
		return;

	if (rotateBy < 0)
		rotateBy = length - (-1 * rotateBy);

	int divided = length / greatestCommonDivisor(length, rotateBy);

	int previous = array[0];

	for (int j = 0; j < length; j++) {

		if (j % divided == 0)
			previous = array[j / divided];

		int current = previous;
		previous = array[((j % divided + 1) * rotateBy + j / divided) % length];
		array[((j % divided + 1) * rotateBy + j / divided) % length] = current;
	}


	/* Explanation of the solution above
	int cycles = greatestCommonDivisor(length, rotateBy);

	for (int j = 0; j < length; j++) {

		int s = j / (length / cycles);
		int i = j % (length / cycles);

		if (i == 0)
			previous = array[s];

		int current = previous;
		previous = array[((i + 1) * rotateBy + s) % length];
		array[((i + 1) * rotateBy + s) % length] = current;
	}
	*/
}

//Implementation of The Euclidean algorithm for fiding the greatest common divisor
int greatestCommonDivisor(int a, int b) {

	int tmp;

	while (b != 0) {
		tmp = b;
		b = a % b;
		a = tmp;
	}

	return a;
}


#ifndef __PROGTEST__

/**
 * Checsk if two arrays are identical on a range given
 * @param[in] a the first array to check
 * @param[in] b the second array to check
 * @param[in] length the length to check
 * @return 1 if the arrays are the same, 0 otherwise
 */
int identicalArrays ( const int a[], const int b[], int length );
/**
 * Prints array content in {...} format
 * @param[in] arr array to print
 * @param[in] length array length
 */
void printArray(const int arr[], int length);

int main (int argc, char * argv [])
{

	assert(greatestCommonDivisor(12, 16) == 4);
	assert(greatestCommonDivisor(5, 1) == 1);
	assert(greatestCommonDivisor(9, 3) == 3);
	assert(greatestCommonDivisor(13, 16) == 1);

	//progtest default tests
	int in0 []  = { 1, 2, 3, 4, 5 };
	int out0 [] = { 5, 1, 2, 3, 4 };

	printf("%d, %d\n", 5, 1);
	printArray(in0, 5);
	rotateArray ( in0, 5, 1 );
	printArray(in0, 5);
	assert ( identicalArrays ( in0, out0, 5 ) );

	int in1 []  = { 1, 2, 3, 4, 5 };
	int out1 [] = { 2, 3, 4, 5, 1 };

	printf("%d, %d\n", 5, -1);
	printArray(in1, 5);
	rotateArray ( in1, 5, -1 );
	printArray(in1, 5);
	assert ( identicalArrays ( in1, out1, 5 ) );

	int in2 []  = { 1, 2, 3, 4, 5, 6 };
	int out2 [] = { 4, 5, 6, 1, 2, 3 };

	printf("%d, %d\n", 6, -3);
	printArray(in2, 6);
	rotateArray ( in2, 6, -3 );
	printArray(in2, 6);
	assert ( identicalArrays ( in2, out2, 6 ) );

	int in3 []  = { 1, 2, 3, 4, 5, 6, 7 };
	int out3 [] = { 3, 4, 5, 6, 7, 1, 2 };

	printf("%d, %d\n", 7, 12);
	printArray(in3, 7);
	rotateArray ( in3, 7, 12 );
	printArray(in3, 7);
	assert ( identicalArrays ( in3, out3, 7 ) );

	int in4 []  = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	int out4 [] = { 2, 3, 4, 5, 6, 7, 8, 9, 1 };

	printf("%d, %d\n", 9, -100);
	printArray(in4, 9);
	rotateArray ( in4, 9, -100 );
	printArray(in4, 9);
	assert ( identicalArrays ( in4, out4, 9 ) );

	//my tests
	int in5 [] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11};
	int out5 [] = {4, 5, 6, 7, 8, 9, 10, 11, 0, 1, 2, 3};

	printf("%d, %d\n", 5, 12);
	printArray(in5, 12);
	rotateArray(in5, 12, 8);
	printArray(in5, 12);
	assert( identicalArrays(in5, out5, 12));

	return 0;
}

int identicalArrays ( const int a[], const int b[], int length ) {

	for (int i = 0; i < length; i++) {
		if (a[i] != b[i])
			return 0;
	}

	return 1;
}

void printArray(const int arr[], int length) {
	printf("{");
	for (int i = 0; i < length; i++) {
		if (i != 0)
			printf(", ");

		printf("%d", arr[i]);
	}
	printf("}\n");
}


#endif /* __PROGTEST__ */

