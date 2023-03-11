
#include <stdio.h>

int readTime(char name);
int computeTime(int hours, int minutes, int seconds, int millis);
int stringSize(char *str);
char inRange(int x, int min, int max);
void printError();

//enables debug printing
//#define DEBUG

int main( int argCount, char **argValues ) {
	
	// input for t1
	int t1 = readTime(1);

	// invalid time read, aborting
	if (t1 < 0) {
		printError();
		return 10 - t1;
	}


	//input for t2
	int t2 = readTime(2);

	// invalid time read, aborting
	if (t2 < 0) {
		printError();
		return 20 - t2;
	}


	// checks if t1 is smaller than t2 
	if (t1 > t2) {
		printError();
		return 4;
	}

	// time difference
	int dT = t2 - t1;

	// compute elements used for printing
	int dHours = dT / (3600 * 1000);
	dT -= dHours * 3600 * 1000;

	int dMinutes = dT / (60 * 1000);
	dT -= dMinutes * 60 * 1000;

	int dSeconds = dT / 1000;
	dT -= dSeconds * 1000;

	printf("Doba:%3d:%02d:%02d,%03d\n", dHours, dMinutes, dSeconds, dT);

	return 0;
}

/** Reads time input
 * @return the time read in ms or a negative number on malformed input
 */
int readTime(char name) {

	printf("Zadejte cas t%d:\n", name);

	// -1 is default in case something goes wrong on input
	int hours = -1, minutes = -1, seconds = -1, millis = -1;
	//reads 4 characters insted of three, so imputs like ,1111 can be marked invalid
	char millisStr[5];

	//should return 4
	int validity = scanf(" %2d : %2d : %2d , %4[0-9]", &hours, &minutes, &seconds, millisStr);

#ifdef DEBUG
	printf("Validity: %d\n", validity);
	printf("Read: %s\n", millisStr);
#endif

	if (validity != 4) {
		return -2;
	}

	//how many digits have been read
	int millisSize = stringSize(millisStr);
	millis = 0;

#ifdef DEBUG
	printf("Size: %d\n", millisSize);
#endif

	//if no more or less digits have been read
	if (!inRange(millisSize, 1, 3)) {
		return -3;
	}

	//convert digits into actula millisecond
	if (millisSize >= 1) {
    	millis += (millisStr[0] - '0') * 100;
    } 
	if (millisSize >= 2) {
    	millis += (millisStr[1] - '0') * 10;
	} 
	if (millisSize >= 3) {
    	millis += (millisStr[2] - '0');
    } 
	

#ifdef DEBUG
	printf("Millis: %d\n", millis);
#endif

	// checks if input is in read boundaries
	if (inRange(hours, 0, 23) && inRange(minutes, 0, 59) && inRange(seconds, 0, 59) && inRange(millis, 0, 999)) {
		return computeTime(hours, minutes, seconds, millis);
	} else {
		return -4;
	}
}

/**
 * @return time in ms form data given
 */
int computeTime(int hours, int minutes, int seconds, int millis) {
	return (((hours * 60) + minutes) * 60 + seconds) * 1000 + millis; 
}

/**
 * @return the size of string given
 */
int stringSize(char *str) {
	int size;
   	for (size = 0; str[size] != '\0'; ) {
    	size++;
	}	
	return size;
}

/**
 * @return if x is in the range given by min and max
 */
char inRange(int x, int min, int max) {
	return min <= x && x <= max;
}

/**
 * prints the error message right before program exit
 */
void printError() {
	printf("Nespravny vstup.\n");
}

