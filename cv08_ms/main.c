#include <stdio.h>
#include <stdlib.h>

/**
 * Reads the firts line and sets line number, increases array size
 * @param[out] p_array pointer to array
 * @param[out] p_lineLength return line length for the future use
 * @return inputSomething
 */
char readFirstLine(char ** p_array, int * p_lineLength);
/**
 * Reads non-first line, need an array large enough
 * @param[out] array to save input in
 * @param[in] lineLength how many chars should be in the next line
 * @param[in] lineLindex index of the line
 * @return inputSomething
 */
char readLine(char array[], int lineLength, int lineIndex);
/**
 * Reads the next character
 * @param[out] p_value if read succeds return value - 0 or mine - is placed there
 * @return charSomething code
 */
char readChar(char * p_value);
/**
 * Increeses the array size to the number of lines given
 * @return new array
 */
char * addLines(char * p_array, int totalLines, int lineLength);


/**
 * Numbers fields in an array acording to mine positions
 * @param[out] array array to number in
 * @param[in] rows number of rows of 2D array
 * @param[in] columns number of columns of 2D array
 */
void numberMines(char array[], int rows, int columns);
/**
 * Increases number of mines nearby by one if the field is not a mine
 * @param[out] position to place mine nearby info in
 */
void placeMine(char * p_position);

/**
 * Printf the array
 * @param[in] array array to print
 * @param[in] rows number of rows of 2D array
 * @param[in] columns number of columns of 2D array
 */
void printField(char array[], int rows, int columns);
/**
 * Replacement for normal array call arr[][]
 * @param[in] array array to search in
 * @param[in] total number of columns
 * @param[in] row y coordinate
 * @param[in] column x coordinate
 * @return pointer to the position requested
 */
char * getPosition(char array[], int totalColumns, int row, int column);




/**
 * mine is there, used in an array
 */
const char mine = -1;

//codes returned by readFirstLine() and readLine()
const char inputEOF = 1;
const char inputLineRead = 2;
const char inputError = 10;
const char inputErrorInvalidChar = 11;
const char inputErrorToSmall = 12;
const char inputErrorNonRect = 13;

const char errorFirstLine = 20;
const char errorOtherLine = 30;

//codes returned by readChar()
const char charUnknow = 0;
const char charInvalid = 1;
const char charValid = 2;
const char charEOF = 3;
const char charNewLine = 4;
const char charIgnored = 5;


int main ( void ) {

	char * array = NULL;
	int linesAllocated = 0;
	int lineLength = 0;
	int lineIndex = 0;

	printf("Zadejte hraci plochu:\n");

	//reads the first line
	char firstLineResult = readFirstLine(&array, &lineLength);
	//printf("Returned %d\n", firstLineResult);

	linesAllocated++;
	lineIndex++;

	//an error on the first line
	if (firstLineResult >= inputError) {

		free(array);

		printf("Nespravny vstup.\n");
		return firstLineResult + errorFirstLine;

		//only one line input
	} else if (firstLineResult == inputEOF) {
		//more line expected
	} else if (firstLineResult == inputLineRead) {

		while (true) {

			while (true) {
				int nextChar = fgetc(stdin);

				if (nextChar == '\n' || nextChar == EOF)
					goto inputDone;

				//to skip DLE and other nonprintable chars
				if (nextChar >= ' ') {
					ungetc(nextChar, stdin);
					break;
				}
			}

			//printf("Reading line %d\n", lineIndex);

			//increases the array size
			//printf("Alocation check: %d <= %d\n", linesAllocated, lineIndex);
			if (linesAllocated <= lineIndex) {
				linesAllocated *= 2;
				//printf("Alocating %d lines\n", linesAllocated);
				array = addLines(array, linesAllocated, lineLength);
			}

			//reading line
			char result = readLine(array, lineLength, lineIndex);
			lineIndex++;

			//invalid input
			if (result >= inputError) {

				free(array);

				printf("Nespravny vstup.\n");
				return result + errorOtherLine;

				//input ended
			} else if (result == inputEOF) {
				break;
			}
		}
	}

	inputDone:

	numberMines(array, lineIndex, lineLength);

	printf("Vyplnena hraci plocha:\n");

	printField(array, lineIndex, lineLength);

	free(array);

	return EXIT_SUCCESS;
}

char readFirstLine(char ** p_array, int * p_lineLength) {

	int allocated = 32;
	*p_array = (char*) realloc(*p_array, sizeof(**p_array) * allocated);

	for (char * p_position = *p_array; true; p_position++) {

		if (*p_lineLength >= allocated) {

			allocated *= 2;

			*p_array = (char*) realloc(*p_array, sizeof(**p_array) * allocated);

			p_position = *p_array + *p_lineLength;
		}


		char result = readChar(p_position);
		//printf("Result: %d\n", result);

		if (result == charEOF || result == charNewLine) {

			if (*p_lineLength < 1)
				return inputErrorToSmall;
			else
				return result == charEOF ? inputEOF : inputLineRead;
		}

		if (result == charUnknow || result == charInvalid)
			return inputErrorInvalidChar;

		if (result == charIgnored) {
			*p_lineLength -= 1;
		}

		*p_lineLength += 1;
	}

	return inputLineRead;
}

char readLine(char array[], int lineLength, int lineIndex) {

	char * start = array + lineLength * lineIndex;

	for (char * p_position = start; p_position < start + lineLength; p_position++) {

		char result = readChar(p_position);

		if (result != charValid) {

			if (result == charNewLine)
				return inputErrorNonRect;

			if (result == charUnknow)
				return inputErrorInvalidChar;

			if (result == charIgnored) {
				p_position--;
				continue;
			}

			return inputError;
		}
	}


	char newLine;
	int newLineResult = readChar(&newLine);

	if (newLineResult == charEOF)
		return inputEOF;

	if (newLineResult == charNewLine)
		return inputLineRead;

	return inputError;
}

char readChar(char * p_value) {
	char c;
	int result = scanf("%c", &c);

	//printf("Char read: %c %d\n", c, c);

	if (result == -1) {
		return charEOF;

	} else if (result != 1) {
		return charInvalid;
	}

	if (c == '\n')
		return charNewLine;

	if (c < ' ')
		return charIgnored;

	switch (c) {
		case '.':
			*p_value = 0;
			break;
		case '*':
			*p_value = mine;
			break;
		default:
			return charUnknow;
	}

	return charValid;
}

char * addLines(char * p_array, int totalLines, int lineLength) {
	return (char*) realloc(p_array, sizeof(*p_array) * lineLength * totalLines);
}

void numberMines(char array[], int rows, int columns) {

	//printf("Working data %d %d\n", columns, rows);

	for (int row = 0; row < rows; row++) {
		for (int column = 0; column < columns; column++) {

			if (*getPosition(array, columns, row, column) != mine)
				continue;

			//printf("Mine: %d x %d\n", column, row);

			if (row != 0) {
				placeMine(getPosition(array, columns, row - 1, column));

				if (column != 0)
					placeMine(getPosition(array, columns, row - 1, column - 1));

				if (column != columns - 1)
					placeMine(getPosition(array, columns, row - 1, column + 1));
			}

			if (row != rows - 1) {
				placeMine(getPosition(array, columns, row + 1, column));

				if (column != 0)
					placeMine(getPosition(array, columns, row + 1, column - 1));

				if (column != columns - 1)
					placeMine(getPosition(array, columns, row + 1, column + 1));
			}

			if (column != 0)
					placeMine(getPosition(array, columns, row, column - 1));

			if (column != columns - 1)
					placeMine(getPosition(array, columns, row, column + 1));
		}
	}
}

void placeMine(char * p_position) {
	if (*p_position != mine)
		*p_position += 1;
}


void printField(char array[], int rows, int columns) {

	for (int row = 0; row < rows; row++) {
		for (int column = 0; column < columns; column++) {

			char field = *getPosition(array, columns, row, column);

			if (field == mine)
				printf("*");
			else if (field == 0)
				printf(".");
			else
				printf("%hhd", field);

		}
		printf("\n");
	}
}

char * getPosition(char array[], int totalColumns, int row, int column) {
	return array + totalColumns * row + column;
}

