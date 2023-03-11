#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//#define DEBUG
#ifdef DEBUG
#define D_MATCH
#define D_NEW
#define D_READ
#define D_INTER
#define D_INDEX
#endif

/**
 * Holds info about the lines - content, number, lineLength and lineBuffer size
 */
typedef struct LineList LineList;

/**
 * Holds found words and memory allocation info
 */
typedef struct WordList WordList;
/**
 * Holds char array and memory allocation info
 * String inside is without '\0' character!
 */
typedef struct String String;



/**
 * Adds the line to LineList
 * @param[out] l LineList to place new line in
 * @param[in] line line to place
 */
void addLine(LineList * l, char * line);
/**
 * Frees all lines from memory
 * @param[in] l LineList to free
 */
void freeLines(LineList * l);

/**
 * Reads and validates lines from stdin
 * @param[out] l LineList to place data in
 * @return 1 for the succes, 0 for an error
 */
char readLines(LineList * l);
/**
 * Reads first line from stdin, sets lineLength in LineList
 * @param[out] l LineList to place line in
 * @return 1 for the succes, 0 for an error
 */
char readFirstLine(LineList * l);
/**
 * Reads non-first line from stdin
 * @param[out] l LineList to place line in
 * @return 1 for the succes, 0 for an error
 */
char readLine(LineList * l);



/**
 * Finds the longest words in the line list given
 * @param[in] l the list of lines to search through
 * @param[out] words list to place found words in
 */
void findWords(const LineList * l, WordList * words);
/**
 * Fill array with indexes of the next same character
 * @param[in] l the LineList of lines to create idex from
 * @param[out] index array of indexes to the next same character
 */
void createCharIndex(const LineList * l, size_t index[]);
/**
 * Finds next same character in the foloving lines
 * @param[in] l lines to search
 * @param[out] words place for found words
 * @param[in] startRow row of the checked character
 * @param[in] startColumn column of the checked character
 */
void findNextChars(const LineList * l, WordList * words, size_t index[], const size_t startRow, const size_t startColumn);
/**
 * Search aroud characters given to find same words
 * @param[in] l lines to search
 * @param[out] words place for found words
 * @param[in] r1 x coordinate of the first char
 * @param[in] c1 y coordinate of the first char
 * @param[in] r2 x coordinate of the second char
 * @param[in] c2 y coordinate of the second char
 */
void searchAt(const LineList * l, WordList * words, const size_t r1, const size_t c1, const size_t r2, const size_t c2);
/**
 * Moves coordivates according to current direction
 * @param[in] d direction number
 * @param[out] x starting x coordinate
 * @param[out] y starting y coordinate
 */
void moveCoordinates(const char d, size_t * x, size_t * y);
/**
 * Adds a char to string structure, increases string size if needed
 * @param[out] s string to add char to
 * @param[in] c char to add
 */
void addToString(String * s, char c);
/**
 * Adds a word to a WordList, increases list size if needed and clears shorted words if a longer one was found
 * @param[out] w wordlist to add word to / to clear from shorter words
 * @param[in] word string with word to add
 * @return 1 if word was added or 0 if it was to short
 */
char addWord(WordList * w, String * word);
/**
 * Releases word in list from memory and sets size to 0
 * @param[in] w list to clear
 */
void clearWords(WordList * w);
/**
 * Same as clearWords(), but now everything is list is freed from memory
 * @param[in] w list to free
 */
void destroyWordList(WordList * w);
/**
 * Converts a string to char array with '\0' at the end
 * @param[in] string string to get array from
 * @return array from string with '\0' added
 */
char * stringToArray(String * string);
/**
 * Remove duplicit words from a WordList, free redundant memory
 * @param[out] words words to be uniqed
 */
void removeDuplicates(WordList * words);
/**
 * Compares two strings using strcmp(). Used for quicksort
 */
int compareLines(const void* a, const void* b);
/**
 * Prints all the found words
 * @param[in] w WordList to print
 */
void printWords(const WordList * w);



struct LineList {
	char ** lines = NULL;
	size_t size = 0;
	size_t allocated = 0;
	size_t lineLength = 0;
};

struct WordList {
	char ** words = NULL;
	size_t size = 0;
	size_t allocated = 0;
	size_t wordLen = 0;
};

struct String {
	char * data = NULL;
	size_t size = 0;
	size_t allocated = 0;
};



int main (void) {

	printf("Hlavolam:\n");

	LineList lines = {};

	char res = readLines(&lines);

	if (!res) {
		printf("Nespravny vstup.\n");
		freeLines(&lines);
		return 1;
	}

#ifdef D_READ
	printf("Data read: %3.zu -----------------------------\n", lines.size);
	for (char ** line = lines.lines; line < lines.lines + lines.size; line++) {
		printf("%s\n", *line);
	}
	printf("---------------------------------------------\n");
#endif

	WordList words = WordList{};
	findWords(&lines, &words);

#ifdef DEBUG
	printf("Words found (non unique): %zu\n", words.size);
#endif

	removeDuplicates(&words);

#ifdef DEBUG
	printf("Words found (unique):     %zu\n", words.size);
#endif

	printWords(&words);

	destroyWordList(&words);
	freeLines(&lines);

	return 0;
}

void findWords(const LineList * l, WordList * words) {

	const size_t size = l->size;

	size_t * index = (size_t*) malloc(size * size * sizeof(*index));
	createCharIndex(l, index);

#ifdef D_INDEX
	for(size_t i = 0; i < size; i++) {
		for (size_t j = 0; j < size; j++) {
			printf("%zu ", index[i * size + j]);
		}
		printf("\n");
	}
#endif

	for (size_t row = 0; row < size; row++) {
		for (size_t column = 0; column < size; column++) {
			findNextChars(l, words, index, row, column);
		}
	}

	free(index);
}

void createCharIndex(const LineList * l, size_t index[]) {

	const char characterNumber = 128 - ' ';
	size_t chars[characterNumber];

	size_t size = l->size;
	size_t length = size * size;

	for (size_t i = 0; i < characterNumber; i++)
		chars[i] = length;

	for (ssize_t i = length - 1; i >= 0; i--) {
		int8_t character = l->lines[i / size][i % size] - ' ';
		index[i] = chars[character];
		chars[character] = i;
	}
}

void findNextChars(const LineList * l, WordList * words, size_t index[], const size_t startRow, const size_t startColumn) {

	const size_t size = l->size;
	size_t lastIndex = index[size * startRow + startColumn];

	while (lastIndex < size * size) {
		searchAt(l, words, startRow, startColumn, lastIndex / size, lastIndex % size);
#ifdef D_MATCH
		char ** lines = l->lines;
		printf("Match found for '%c' - [%zu, %zu] [%zu, %zu]\n", lines[startRow][startColumn], startRow, startColumn, lastIndex / size, lastIndex % size);
#endif
		lastIndex = index[lastIndex];
	}
}

void searchAt(const LineList * l, WordList * words, const size_t r1, const size_t c1, const size_t r2, const size_t c2) {

	const size_t size = l->size;
	char ** lines = l->lines;

	char current = lines[r1][c1];

	String word = {};

	/*
	 * dx: 0d 1v 2b 3> 4P 5^ 6\ 7<
	 */

	for (char d1 = 0; d1 < 8; d1++) {

		for (char d2 = 0; d2 < 8; d2++) {

			word.size = 0;
			addToString(&word, current);

			size_t x1 = r1, x2 = r2, y1 = c1, y2 = c2;
			char intersection = 0;

			while (true) {

				intersection = x1 == x2 && y1 == y2;

				//moves to the next cell
				moveCoordinates(d1, &x1, &y1);
				moveCoordinates(d2, &x2, &y2);

				if (false
						//border reached
						|| x1 >= size || x1 < 0 || x2 >= size || x2 < 0
						|| y1 >= size || y1 < 0 || y2 >= size || y2 < 0
						//char mismatch
						|| lines[x1][y1] != lines[x2][y2]
				   ) {

					if (addWord(words, &word)) {

						//add words backward if there is no other way to find and get them again
						if (intersection) {

							String reversed = String{};

							char d = (d1 + 4) % 8;
#ifdef D_INTER
							printf("Loc: [%zu, %zu] -> [%zu, %zu]\n", r1, c1, x1, y1);
							printf("Dir: %d -> %d\n", d1, d);
#endif

							while (x1 != r1 || y1 != c1) {

								moveCoordinates(d, &x1, &y1);
#ifdef D_INTER
								printf("Loc: [%zu, %zu] -> [%zu, %zu]\n", r1, c1, x1, y1);
								printf("Char: %c\n", lines[x1][y1]);
#endif

								addToString(&reversed, lines[x1][y1]);
							}

#ifdef D_INTER
							printf("Size: %zu\n", reversed.size);
#endif

							addWord(words, &reversed);

						}

						word = String{};
					}

					break;
				}

				addToString(&word, lines[x1][y1]);
			}
		}
	}

	free(word.data);
}

/*
 * d1: 0d 1v 2b 3> 4P 5^ 6\ 7<
 */
void moveCoordinates(const char d, size_t * x, size_t * y) {
	if (d <= 2)
		*x += 1;
	else if (4 <= d && d <= 6)
		*x -= 1;

	if (2 <= d && d <= 4)
		*y += 1;
	else if (d == 0 || 6 <= d)
		*y -= 1;
}

void addToString(String * s, char c) {

	if (s->size >= s->allocated) {
		s->allocated = s->allocated * 2 + 42;
		s->data = (char*) realloc(s->data, s->allocated * sizeof(*(s->data)));
	}

	s->data[s->size] = c;
	s->size	+= 1;
}

char addWord(WordList * w, String * word) {

	if (word->size < w->wordLen) {
		return 0;
	} else if (word->size > w->wordLen) {

#ifdef D_NEW
		printf("New longest word: %zu %.*s\n", word->size, (int)word->size, word->data);
#endif

		clearWords(w);
		w->wordLen = word->size;

	} else {
#ifdef D_NEW
		printf("New word found:   %zu %.*s\n", word->size, (int)word->size, word->data);
#endif
	}

	if (w->size >= w->allocated) {
		w->allocated = w->allocated * 2 + 42;
		w->words = (char**) realloc(w->words, w->allocated * sizeof(*(w->words)));
	}

	w->words[w->size] = stringToArray(word);
	w->size	+= 1;

	return 1;
}

void clearWords(WordList * w) {
	for (size_t i = 0; i < w->size; i++)
		free(w->words[i]);

	w->size = 0;
}

void destroyWordList(WordList * w) {
	clearWords(w);
	free(w->words);
}

char * stringToArray(String * string) {
	addToString(string, '\0');
	return string->data;
}

void removeDuplicates(WordList * words) {

	if (words->size <= 1) {
		return;
	}

	qsort(words->words, words->size, sizeof(*(words->words)), compareLines);

	char ** dest = words->words;

	for (char ** src = words->words; src < words->words + words->size - 1; src++) {

		//printf("%p - %s - %s\n", (void*)src, *src, *(src + 1));

		if (strcmp(*src, *(src + 1)) == 0) {
			free(*dest);
		} else {
			dest++;
		}

		*dest = *(src + 1);
	}

	words->size = dest - words->words + 1;
}

int compareLines(const void* a, const void* b) {
    const char * arg1 = *(const char**)a;
    const char * arg2 = *(const char**)b;

	return strcmp(arg1, arg2);
}

void printWords(const WordList * w) {

	if (w->size == 0) {
		printf("Zadne opakujici se slovo.\n");
		return;
	}

	printf("Nejdelsi opakujici se slova:\n");

	for (size_t i = 0; i < w->size; i++) {
		printf("%s\n", w->words[i]);
	}
}

char readLines(LineList * l) {

	if (!readFirstLine(l)) {
		return 0;
	}

	while (true) {

		char res = readLine(l);
		//printf("Data: %ld %ld\n", l->size, l->lineLength);

		if (res == 2) {
			return l->size == l->lineLength;
		}

		if (res == 0) {
			return 0;
		}

		if (l->size > l->lineLength) {
			//printf("to big\n");
			return 0;
		}
	}

	return 1;
}

char readFirstLine(LineList * l) {

	char * line = NULL;
	size_t bufferLen = 0;

	ssize_t nread = getline(&line, &bufferLen, stdin);
	size_t read = nread;

	//printf("Read: %ld - %s\n", nread - 1, line);
	//printf("Bools: %d %d %d\n", nread == -1, read - 1 <= 0, line[read - 1] != '\n');

	if (nread == -1 || read - 1 <= 0 || line[read - 1] != '\n') {
		free(line);
		return 0;
	}

	//replace '\n'
	line[nread - 1] = '\0';

	addLine(l, line);
	l->lineLength = read - 1;

	return 1;
}

char readLine(LineList * l) {

	char * line = NULL;
	size_t bufferLen = 0;

	ssize_t nread = getline(&line, &bufferLen, stdin);
	size_t read = nread;

	//EOF
	if (nread == -1) {
		//printf("EOF\n");
		free(line);
		return 2;
	}

	//printf("Read: %ld - %s\n", nread - 1, line);
	//printf("Bools: %d %d %d\n", read - 1 <= 0, line[read - 1] != '\n', read - 1 != l->lineLength);

	if (read - 1 <= 0 || line[read - 1] != '\n' || read - 1 != l->lineLength) {
		free(line);
		return 0;
	}

	//replace '\n'
	line[nread - 1] = '\0';

	addLine(l, line);

	return 1;
}

void addLine(LineList * l, char * line) {

	if (l->allocated <= l->size) {
		l->allocated = l->allocated * 2 + 42;
		l->lines = (char **) realloc(l->lines, l->allocated * sizeof(*(l->lines)));
	}

	l->lines[l->size] = line;
	l->size += 1;
}

void freeLines(LineList * l) {

	for (char ** line = l->lines; line < l->lines + l->size; line++) {
		free(*line);
	}

	free(l->lines);
}

