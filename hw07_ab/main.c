#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <ctype.h>

#define DEBUG
#ifdef DEBUG
#endif
#define D_LIST if (0)
#define D_LIMIT if (0)
#define D_PRINT if (0)

/**
 * Reads the first words, skips spaces
 * @param[out] abbrev place to save abbrevation into
 * @return 1 for success, 0 for an error
 */
uint8_t readAbbrevation(char ** abbrev);
/**
 * Read a phrase from stdin
 * @param[out] mode mode to perform, modeList or modeCnt
 * @param[out] cnt the number of letter in each word
 * @param[out] phrase the phare read withnout ""
 * @param[out] phraseAlloc how many bytes are allocated for phrases (to prevent allocating over and over again)
 * @return inputError for error, inputSuccess for valid read and inputEOF for the end of stream before any valid reads
 */
uint8_t readInput(uint8_t * mode, size_t * cnt, char ** phrase, size_t * phraseAlloc);
/**
 * Adds a char into char array
 * @param[out] str string to add char to
 * @param[out] allocated how long is the string in memory
 * @param[out] size the length of the string withnout \0
 * @param[in] c the char to add
 */
void addChar(char ** str, size_t * allocated, size_t * size, const char c);

/**
 * Prints an error message
 */
void printError();



/**
 * Holds state common to whole recursion
 */
typedef struct RecursionState RecursionState;
/**
 * Holds constants durring whole recursion
 */
typedef struct RecursionConst RecursionConst;
/**
 * Holds data for this tree branch only
 */
typedef struct RecursionArgs RecursionArgs;

/**
 * Starts recursive search for abbrevation and prints them in the end
 * @param abbrev abbrevation to find
 * @param phrase text to seach in
 * @param maxInWord maximum of chars found in one word
 */
void searchPhrase(const char * abbrev, const char * phrase, const size_t maxInWord);
/**
 * Implementation of recursive calls
 */
void searchPhraseImpl(RecursionState * state, const RecursionConst * constants, const RecursionArgs args);
/**
 * Prints found abbrevation in the phrase given base on the indexes stored in state
 */
void printFoundPhrase(const RecursionState * state, const RecursionConst * constatns);



/**
 * Holds state common to whole recursion
 */
typedef struct LimitState LimitState;
/**
 * Holds constants durring whole recursion
 */
typedef struct LimitConst LimitConst;
/**
 * Holds data for this tree branch only
 */
typedef struct LimitArgs LimitArgs;

/**
 * Starts recursive search for abbrevation and prints limits in the end
 * @param abbrev abbrevation to find
 * @param phrase text to seach in
 * @param maxInWord maximum of chars found in one word
 */
void searchLimits(const char * abbrev, const char * phrase, const size_t maxInWord);
/**
 * Implementation of recursive calls
 */
void searchLimitsImpl(LimitState * state, const LimitConst * constants, const LimitArgs args);
/**
 * Print limits from a recursion
 */
void printLimits(const LimitState * state, const LimitConst * constants);


/**
 * Copy data from one char array to anorher and make all the char uppercase
 * @param src array with data to copy from
 * @param dst array to copy data to
 * @param len length of data to coly excludeing '\0'
 */
void stringCopyAndLower(const char * src, char * dst, const size_t len);
/**
 * Fills an array with data given
 * @param arr array to fill
 * @param size size of the array
 * @param with the item to fill the array with
 */
void fillArray(size_t * arr, const size_t size, const size_t wiht);



const uint8_t modeList = 1, modeCnt = 2;
const uint8_t inputError = 0, inputSucces = 1, inputEOF = 2;



int main (void) {

	char * abbrev = NULL;

	if (readAbbrevation(&abbrev) != 1) {
		free(abbrev);
		printError();
		return 1;
	}

	printf("Problemy:\n");

	char * phrase = NULL;
	size_t phraseAlloc = 0;
	uint8_t hadData = 0;

	while (true) {

		uint8_t mode;
		size_t cnt;

		const uint8_t code = readInput(&mode, &cnt, &phrase, &phraseAlloc);
		if (code == inputEOF) {
			break;
		}

		hadData = 1;

		if (!code) {
			free(phrase);
			free(abbrev);
			printError();
			return 2;
		}

		//printf("Read: '%s'\n", phrase);

		if (mode == modeList) {
			searchPhrase(abbrev, phrase, cnt);
		} else {
			searchLimits(abbrev, phrase, cnt);
		}
	}

	free(phrase);
	free(abbrev);

	if (!hadData) {
		printError();
		return 3;
	}

	return 0;
}

uint8_t readAbbrevation(char ** abbrev) {

	printf("Zkratka:\n");

	size_t size = 0;
	size_t allocated = 0;

	int c;

	//skip spaces
	while (isspace(c = fgetc(stdin)));

	do {

		if ('A' <= c && c <= 'Z') {
			addChar(abbrev, &size, &allocated, c);

		} else if (c == '\n' || c == EOF) {
			break;
		} else {
			return 0;
		}

		c = fgetc(stdin);

	} while(true);

	if (size <= 0)
		return 0;

	addChar(abbrev, &size, &allocated, '\0');

	return 1;
}

uint8_t readInput(uint8_t * mode, size_t * cnt, char ** phrase, size_t * phraseAlloc) {

	//read mode
	char modeChar;
	const int modeCode = scanf(" %c", &modeChar);

	if (modeCode == -1) return inputEOF;
	if (modeCode != 1 || (modeChar != '?' && modeChar != '#')) return inputError;

	*mode = modeChar == '?' ? modeList : modeCnt;

	ssize_t tmpCnt;
	//read the number of letters
	if (scanf(" %zd", &tmpCnt) != 1 || tmpCnt <= 0)
		return inputError;

	*cnt = tmpCnt;

	//skip spaces
	int quat;
	while (isspace(quat = fgetc(stdin)));

	if (quat != '"')
		return inputError;

	//read quotes
	size_t size = 0;

	while (true) {

		int c = fgetc(stdin);

		if (c == '"') {
			break;
		} else if (c == EOF) {
			return inputError;
		}

		if ('A' <= c && c <= 'Z')
			c += 'a' - 'A';

		addChar(phrase, phraseAlloc, &size, c);
	}

	//somehow Láďa thinks this is valid input...
	//if (size == 0) return 0;

	addChar(phrase, phraseAlloc, &size, '\0');

	return inputSucces;
}

void addChar(char ** str, size_t * allocated, size_t * size, const char c) {

	if (*size >= *allocated) {
		*allocated = *allocated * 3 / 2 + 42;
		*str = (char*) realloc(*str, sizeof(char) * *allocated);
	}

	(*str)[*size] = c;
	*size += 1;
}

void printError() { printf("Nespravny vstup.\n"); }



struct RecursionState {
	size_t * indexes;
	size_t found;
	size_t maxInWord;
};
struct RecursionConst {
	const char * phrase;
	const size_t maxInWord;
	const size_t abbrevLen;
	const size_t phraseLen;
};
struct RecursionArgs {
	const char * abbrev;
	const char * phrase;
	const size_t abbrevLen;
	const size_t phraseLen;
	const size_t leftInWord;
};

void searchPhrase(const char * abbrev, const char * phrase, size_t maxInWord) {

	const size_t abbrevLen = strlen(abbrev);
	const size_t phraseLen = strlen(phrase);

	char * lowerAbbrev = (char *) malloc((abbrevLen + 1) * sizeof(char));
	stringCopyAndLower(abbrev, lowerAbbrev, abbrevLen);

	RecursionState state = {
		(size_t*) malloc(sizeof(size_t) * abbrevLen), 0, 0
	};

	const RecursionConst constants = {phrase, maxInWord, abbrevLen, phraseLen};
	const RecursionArgs args = {lowerAbbrev, phrase, abbrevLen, phraseLen, maxInWord};

	searchPhraseImpl(&state, &constants, args);

	printf("> %zu\n", state.found);

	free(state.indexes);
	free(lowerAbbrev);
}

void searchPhraseImpl(RecursionState * state, const RecursionConst * constants, const RecursionArgs args) {

	if (args.abbrevLen <= 0) {

		D_LIST printf("Found!\n");

		state->found += 1;
		printFoundPhrase(state, constants);
		return;
	}

	size_t leftInWord = args.leftInWord;

	const char toFind = args.abbrev[0];
	D_LIST printf("Searching for %c\n", toFind);

	for (const char * current = args.phrase; current < args.phrase + args.phraseLen - args.abbrevLen + 1; current++) {
		const char c = *current;

		if (isspace(c)) {

			leftInWord = constants->maxInWord;

		} else if (leftInWord > 0 && c == toFind) {

			const size_t abbrevIndex = constants->abbrevLen - args.abbrevLen;
			const size_t currentIndex = current - constants->phrase;
			state->indexes[abbrevIndex] = currentIndex;

			D_LIST printf("Adding index: %zu, %zu\n", abbrevIndex, currentIndex);

			RecursionArgs newArgs = {
				&(args.abbrev[1]),
				&(current[1]),
				args.abbrevLen - 1,
				constants->phraseLen - currentIndex - 1,
				leftInWord - 1
			};

			searchPhraseImpl(state, constants, newArgs);
		}
	}
}

void printFoundPhrase(const RecursionState * state, const RecursionConst * constants) {

	size_t phraseIndex = 0;

	printf("\"");

	for (size_t i = 0; i < constants->abbrevLen; i++) {
		const size_t big = state->indexes[i];

		D_PRINT printf("P index: %zu %zu\n", i, big);

		for (; phraseIndex < big; phraseIndex++) {
			printf("%c", constants->phrase[phraseIndex]);
		}

		printf("%c", toupper(constants->phrase[phraseIndex++]));
	}

	for (; phraseIndex < constants->phraseLen; phraseIndex++) {
		printf("%c", constants->phrase[phraseIndex]);
	}

	printf("\"\n");
}

struct LimitState {
	size_t * limits;
};
struct LimitConst {
	const char * phrase;
	const size_t maxInWord;
	const size_t abbrevLen;
	const size_t phraseLen;
};
struct LimitArgs {
	const char * abbrev;
	const char * phrase;
	const size_t abbrevLen;
	const size_t phraseLen;
	const size_t leftInWord;
	const size_t longest;
};

void searchLimits(const char * abbrev, const char * phrase, size_t maxInWord) {

	const size_t abbrevLen = strlen(abbrev);
	const size_t phraseLen = strlen(phrase);

	char * lowerAbbrev = (char *) malloc((abbrevLen + 1) * sizeof(char));
	stringCopyAndLower(abbrev, lowerAbbrev, abbrevLen);

	LimitState state = {
		(size_t*) malloc(sizeof(size_t) * maxInWord)
	};
	fillArray(state.limits, maxInWord, 0);

	const LimitConst constants = {phrase, maxInWord, abbrevLen, phraseLen};
	const LimitArgs args = {lowerAbbrev, phrase, abbrevLen, phraseLen, maxInWord};

	searchLimitsImpl(&state, &constants, args);

	printLimits(&state, &constants);

	free(state.limits);
	free(lowerAbbrev);
}

void searchLimitsImpl(LimitState * state, const LimitConst * constants, const LimitArgs args) {

	if (args.abbrevLen <= 0) {

		const size_t charsRead = constants->maxInWord - args.leftInWord;
		const size_t longest = charsRead > args.longest ? charsRead : args.longest;

		D_LIMIT printf("Found! %zu\n", args.longest);

		if (longest != 0)
			state->limits[longest - 1] += 1;
		else
			state->limits[constants->abbrevLen - 1] += 1;

		return;
	}

	size_t leftInWord = args.leftInWord;
	size_t longest = args.longest;

	const char toFind = args.abbrev[0];
	D_LIMIT printf("Searching for %c\n", toFind);

	for (const char * current = args.phrase; current < args.phrase + args.phraseLen - args.abbrevLen + 1; current++) {
		const char c = *current;

		if (isspace(c)) {

			const size_t charsRead = constants->maxInWord - leftInWord;
			if (charsRead > args.longest)
				longest = charsRead;

			leftInWord = constants->maxInWord;

		} else if (leftInWord > 0 && c == toFind) {

			const size_t currentIndex = current - constants->phrase;
			D_LIMIT printf("Branch: %zu\n", currentIndex);

			LimitArgs newArgs = {
				&(args.abbrev[1]),
				&(current[1]),
				args.abbrevLen - 1,
				constants->phraseLen - currentIndex - 1,
				leftInWord - 1,
				longest
			};

			searchLimitsImpl(state, constants, newArgs);
		}
	}
}

void printLimits(const LimitState * state, const LimitConst * constants) {

	size_t sum = 0;

	for (size_t i = 0; i < constants->maxInWord; i++) {
		sum += state->limits[i];
		printf("> limit %zu: %zu\n", i + 1, sum);
	}
}



void stringCopyAndLower(const char * src, char * dst, const size_t len) {
	for (size_t i = 0; i < len + 1; i++)
		dst[i] = tolower(src[i]);
}

void fillArray(size_t * arr, const size_t size, const size_t with) {
	for (size_t i = 0; i < size; i++)
		arr[i] = with;
}





