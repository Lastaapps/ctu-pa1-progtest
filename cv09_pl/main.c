#include <stdio.h>
#include <stdlib.h>
#include <string.h>




/**
 * Processed data from stdin
 * @param str one line of text from stdin
 * @return 1 if input was valid, 0 otherwise
 */
char handleInput(char * str);
/**
 * Prints output to stdout
 * @param[in] match if the string is palingrom (ignoring case)
 * @param[in] caseMatch if the strings are the same (not ignorintg case)
 */
void printOut(const char match, const char caseMatch);
/**
 * Checks if chars are the same or of different case
 * @param[in] c1 one cha to check
 * @param[in] c2 the other one
 * @return charDiff if they differ, charSame if they are the same and
 * charCase if they differ only by theyr case
 */
char isSame(const char c1, const char c2);
/**
 * Removes all the whitespaces from the sting given excepnt \n
 * str[out] string to remove whitespaces from
 */
void removeSpaces(char * str);
/**
 * Checks if a char is white space excluding \n
 * @return 0 if char is now whitespace or is \n, 1 otherwise
 */
char isSpace(const char c);





const char charDiff = 0, charSame = 1, charCase = 2;






#ifndef __PROGTEST__

#include <assert.h>

void testRemoveSpaces() {

	char str0[] = "";
	removeSpaces(str0);
	assert(strcmp(str0, "") == 0);

	char str1[] = "\n";
	removeSpaces(str1);
	assert(strcmp(str1, "\n") == 0);

	char str2[] = "ahoj";
	removeSpaces(str2);
	assert(strcmp(str2, "ahoj") == 0);

	char str3[] = "   ahoj   kamo   ";
	removeSpaces(str3);
	assert(strcmp(str3, "ahojkamo") == 0);
}

void testIsSame() {

	assert(isSame('a', 'B') == charDiff);
	assert(isSame('A', 'A') == charSame);
	assert(isSame('a', 'A') == charCase);
	assert(isSame('A', 'a') == charCase);
	assert(isSame('/', '/' + ('A' - 'a')) == charDiff);
	assert(isSame('/' + ('A' - 'a'), '/') == charDiff);
}

void test() {
	testRemoveSpaces();
	testIsSame();
}
#endif


int main(void) {

#ifndef __PROGTEST__
	test();
#endif

	printf("Zadejte retezec:\n");

	char * line = NULL;
	size_t len = 0;
	ssize_t nread;

	while ((nread = getline(&line, &len, stdin)) != -1) {

		if (!handleInput(line)) {

			printf("Nespravny vstup.\n");

			free(line);
			return 1;
		}
	}

	free(line);

	return 0;
}

char handleInput(char * str) {

	removeSpaces(str);

	size_t len = strlen(str);

	if (len <= 1 || str[len - 1] != '\n') {
		return 0;
	}

	char match = 1;
	char caseMatch = 1;

	for (char * i1 = str, * i2 = str + len - 2; i1 < i2; i1++, i2--) {

		const char res = isSame(*i1, *i2);

		if (res == charSame) {
		} else if (res == charCase) {
			caseMatch = 0;
		} else {
			match = 0;
			break;
		}
	}

	printOut(match, caseMatch);

	return 1;
}

void printOut(const char match, const char caseMatch) {
	if (match) {
		if (caseMatch) {
			printf("Retezec je palindrom (case-sensitive).\n");
		} else {
			printf("Retezec je palindrom (case-insensitive).\n");
		}
	} else {
		printf("Retezec neni palindrom.\n");
	}
}

char isSame(const char c1, const char c2) {

	if (c1 == c2)
		return charSame;

	if (('a' <= c1 && c1 <= 'z') || ('a' <= c2 && c2 <= 'z')) {
		if ((c1 - c2) * (c1 < c2 ? 1 : -1) == 'A' - 'a') {
			return charCase;
		}
	}

	return charDiff;
}


void removeSpaces(char * str) {

	if (*str == '\0')
		return;

	char * dst = str;

	for (; *str != '\0'; str++) {

		if (!isSpace(*str)) {
			*dst = *str;
			dst++;
		}
	}

	*dst = '\0';
}

char isSpace(const char c) {
	return c <= ' ' && c != '\n';
}

