#include <stdio.h>
#include <stdlib.h>

/**
 * Fills an array with 0
 * @param array[out] array to fill
 * @param len[in] the length of the array
 */
void nullArray(int array[], int len);

/**
 * Handles log input
 * @param loggedInUsers[in] table of user asseses
 * @param userLogins[in] table of how manytimes user has logged in
 * @param p_position[in] where should be the next user placed
 * @return inputSucces, inputError or inputEnd
 */
char manageInput(int loggedInUsers[], int userLogins[], int * p_position);
/**
 * Read line with information about user access
 * @param loggedInUsers[in] table of user asseses
 * @param userLogins[in] table of how manytimes user has logged in
 * @param p_position[in] where should be the next user placed
 * @return inputSucces, inputError or inputEnd
 */
char readNewLogin(int loggedInUsers[], int userLogins[], int * p_position);
/**
 * Prints how many times user has already logged in
 * @param[in] n number of user logins
 */
void printNthLogin(int n);
/**
 * Reads and process request to get data from a range given
 * @param loggedInUsers[in] table of user asseses
 * @param p_position[in] where should be the next user placed
 * @return inputSucces, inputError or inputEnd
 */
char readFromTo(int loggedInUsers[], const int * p_position);
/**
 * Prints from to line
 * @param[in] number numbe of unique logins
 * @param[in] total total number of logins in an interval
 */
void printFromTo(int number, int total);

/**
 * Prints an error message
 */
void printError();
/**
 * Compare two ints, used for qsort()
 */
int compareInts(const void* a, const void* b);


/**
 * The maximum number of accesses possible
 */
const int maxAccessNumber = 1000000;
/**
 * The maximum value of user id
 */
const int maxId = 100000 - 1;

//result codes
const char inputSucces = 0, inputError = 1, inputEnd = 2;

int main (void) {

	//how many users has already logged in
	int currentAccess = 0;
	//stores the ordred in which user logins came in
	int loggedInUsers[maxAccessNumber];
	//sotres how many times has each user logged in
	int userLogins[maxId + 1];

	nullArray(loggedInUsers, maxAccessNumber);

	printf("Pozadavky:\n");

	while (1) {

		char result = manageInput(loggedInUsers, userLogins, &currentAccess);

		if (result == inputError) {
			printError();
			return EXIT_FAILURE;

		} else if (result == inputEnd) {
			return EXIT_SUCCESS;
		}
	}

	//std ended without an error
	return EXIT_SUCCESS;
}

void nullArray(int array[], int len) {
	for (int * i = array; i < array + len; i++)
		*array = 0;
}

char manageInput(int loggedInUsers[], int userLogins[], int * p_position) {

	char operation;

	//read the next operation
	int result = scanf(" %c", &operation);

	if (result == -1)
		return inputEnd;
	else if (result != 1)
		return inputError;

	switch (operation) {
		case '+':
			return readNewLogin(loggedInUsers, userLogins, p_position);
		case '?':
			return readFromTo(loggedInUsers, p_position);
		default:
			return inputError;
	}

	return inputError;
}

char readNewLogin(int loggedInUsers[], int userLogins[], int * p_position) {

	int id;
	int result = scanf(" %d", &id);
	int position = *p_position;

	if (result != 1 || id < 0 || id > maxId)
		return inputError;

	//check for an owerflow
	if (position >= maxAccessNumber)
		return inputError;

	loggedInUsers[position] = id;

	userLogins[id] += 1;

	printNthLogin(userLogins[id]);

	*p_position += 1;

	return inputSucces;
}

void printNthLogin(int n) {
	if (n == 1)
		printf("> prvni navsteva\n");
	else
		printf("> navsteva #%d\n", n);
}


char readFromTo(int loggedInUsers[], const int * p_position) {

	int from, to;
	int result = scanf(" %d %d", &from, &to);

	if (result != 2 || from < 0 || to < 0 || from > to || to >= *p_position) {
		return inputError;
	}

	int size = to - from + 1;
	int * interval = (int*) malloc(size * sizeof(*interval));

	//copy interval searched into new array
	for (int i = 0; i < size; i++)
		interval[i] = loggedInUsers[from + i];

	qsort(interval, size, sizeof(int), compareInts);

	//same items are now in a sequence
	int unique = 1;
	int last = interval[0];

	for (int i = 1; i < size; i++) {

		int item = interval[i];

		if (item != last) {
			last = item;
			unique++;
		}
	}

	free(interval);

	printFromTo(unique, size);

	return inputSucces;
}


void printFromTo(int number, int total) {
	printf("> %d / %d\n", number, total);
}

void printError() {
	printf("Nespravny vstup.\n");
}

//https://en.cppreference.com/w/c/algorithm/qsort
int compareInts(const void* a, const void* b) {
    int arg1 = *(const int*)a;
    int arg2 = *(const int*)b;

    return (arg1 > arg2) - (arg1 < arg2);
}




