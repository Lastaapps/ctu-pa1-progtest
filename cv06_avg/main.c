#ifndef __PROGTEST__
#include <stdio.h>
#include <limits.h>
#include <assert.h>
#include <stdint.h>
#endif /* __PROGTEST__ */

//#define DEBUG

long long avg3 ( long long a, long long b, long long c )
{
	long long d1 = a / 3, d2 = b / 3, d3 = c / 3;
	int m1 = a % 3, m2 = b % 3, m3 = c % 3;

	if (a < 0 && m1 != 0) {
		d1 -= 1;
		m1 += 3;
	}

	if (b < 0 && m2 != 0) {
		d2 -= 1;
		m2 += 3;
	}

	if (c < 0 && m3 != 0) {
		d3 -= 1;
		m3 += 3;
	}

#ifdef DEBUG
	printf("d1: %lld, d2: %lld, d3: %lld\n", d1, d2, d3);
	printf("m1: %d, m2: %d, m3: %d\n", m1, m2, m3);
#endif

	long long int sum = d1 + d2 + d3;
	int toAdd = (m1 + m2 + m3) / 3;
	if (sum < 0 || (d1 < 0 && d2 < 0 && d3 < 0)) {
		if ((m1 + m2 + m3) % 3 != 0) {
			if (sum + toAdd + 1 <= 0) {
				toAdd += 1;
			}
		}
	}


	long long int output = d1 + d2 + d3 + toAdd;

#ifdef DEBUG
	printf("o: %lld, s: %lld, a: %d\n", output, sum, toAdd);
	printf("\n");
#endif

	return output;
}

#ifndef __PROGTEST__
int main (int argc, char * argv []) {

	assert(avg3( 1, 2, 3 ) == 2);
	assert(avg3( 2, 2, 3 ) == 2);
	assert(avg3( 2, 3, 3 ) == 2);
	assert(avg3( -1, -2, -3 ) == -2);
	assert(avg3( -2, -2, -3 ) == -2);
	assert(avg3( -2, -3, -3 ) == -2);

	assert(avg3( -100, 100, 30) == 10);
	assert(avg3( 1, 2, 2 ) == 1);
	assert(avg3( -1, -2, -2 ) == -1);
	assert(avg3( LLONG_MAX, LLONG_MAX, LLONG_MAX) == LLONG_MAX);

	assert(avg3( 9223372036854775799, 9223372036854775800, -8 ) == 6148914691236517197);

	//data from Progtest help
	assert(avg3( 9223372036854775800, 9223372036854775800, -8 ) == 6148914691236517197);
	assert(avg3( 9223372036854775800, -6, -4611686018427387907 ) == 1537228672809129295);
	assert(avg3( 9223372036854775800, -6, -2 ) == 3074457345618258597);

	assert(avg3 ( -8, -4611686018427387898, 4611686018427387908 ) == 0);
	assert(avg3 ( 9223372036854775800, -4611686018427387906, -4611686018427387896 ) == 0);
	assert(avg3 ( 9223372036854775800, -4611686018427387906, -4611686018427387896 ) == 0);
	assert(avg3 ( 9223372036854775800, -2, -9223372036854775800 ) == 0);
	assert(avg3 ( 9223372036854775800, -2, -9223372036854775800 ) == 0);
	assert(avg3 ( -4611686018427387912, 4611686018427387908, 3 ) == 0);
	assert(avg3 ( -4611686018427387912, 3, 4611686018427387908 ) == 0);
	assert(avg3 ( -4611686018427387912, 4611686018427387908, 2 ) == 0);
	assert(avg3 ( -4611686018427387912, 4611686018427387908, 2 ) == 0);

	//assert(avg3 ( -9223372036854775808, -9223372036854775808, -9223372036854775807 ) == -9223372036854775807);

	return 0;
}
#endif /* __PROGTEST__ */

