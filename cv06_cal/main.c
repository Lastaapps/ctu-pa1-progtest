#ifndef __PROGTEST__
#include <stdio.h>
#include <assert.h>
#endif /* __PROGTEST__ */

/**
 * Gets the index of the date given in the year given
 * @param[in] day - day of month
 * @param[in] month - month of year
 * @param[in] year
 * @param[out] idx - index of the date in year
 * @return 1 for succes, 0 for failure in form of invalid data
 */
int dateToIndex(int day, int month, int year, int *idx);
/**
 * Validates the date if it really exists
 * @param[in] day - day of month
 * @param[in] month - month of year
 * @param[in] year
 * @return 1 for succes, 0 for failure in form of invalid data
 */
char validate(int day, int month, int year);
/**
 * Checks if an year is leap or not
 * @param[in] year - the year to check
 * @return 1 if the year is leap, otherwise 0
 */
char isLeapYear(int year);


int dateToIndex(int day, int month, int year, int *idx) {

	//check for input validity
	if (!validate(day, month, year))
		return 0;

	//sets init days
	*idx = day;

	//days days from months below
	switch(month - 1) {
		case 11: *idx += 30;
		case 10: *idx += 31;
		case 9: *idx += 30;
		case 8: *idx += 31;
		case 7: *idx += 31;
		case 6: *idx += 30;
		case 5: *idx += 31;
		case 4: *idx += 30;
		case 3: *idx += 31;
		case 2: *idx += isLeapYear(year) ? 29 : 28;
		case 1: *idx += 31;
	}

	return 1;	
}

char validate(int day, int month, int year) {

	if (year < 2000)
		return 0;

	if (day < 1)
		return 0;

	char daysInFeb = isLeapYear(year) ? 29 : 28;

	//checkts date ranges
	switch(month) {
		case 1: if (day > 31) return 0; break;
		case 2: 
					if (day > daysInFeb)
						return 0; 
					break;

		case 3: if (day > 31) return 0; break;
		case 4: if (day > 30) return 0; break;
		case 5: if (day > 31) return 0; break;
		case 6: if (day > 30) return 0; break;
		case 7: if (day > 31) return 0; break;
		case 8: if (day > 31) return 0; break;
		case 9: if (day > 30) return 0; break;
		case 10: if (day > 31) return 0; break;
		case 11: if (day > 30) return 0; break;
		case 12: if (day > 31) return 0; break;
		
		//for invalid month input default branch is used
		default: return 0;
	}
	return 1;
}

char isLeapYear(int year) {
	return year % 4000 != 0
		&& (year % 400 == 0 || year % 100 != 0)
		&& year % 4 == 0;
}


#ifndef __PROGTEST__
int main (int argc, char * argv []) {
    int idx = 0;

	assert(isLeapYear(2000) != 0);
	assert(isLeapYear(2001) == 0);
	assert(isLeapYear(2004) != 0);
	assert(isLeapYear(2100) == 0);
	assert(isLeapYear(2400) != 0);
	assert(isLeapYear(4000) == 0);

    assert(dateToIndex( 1,  1, 2000, &idx) == 1 && idx == 1);
    assert(dateToIndex( 1,  2, 2000, &idx) == 1 && idx == 32);
    assert(dateToIndex(29,  2, 2000, &idx) == 1 && idx == 60);
    assert(dateToIndex(29,  2, 2001, &idx) == 0);
    assert(dateToIndex( 1, 12, 2000, &idx) == 1 && idx == 336);
    assert(dateToIndex(31, 12, 2000, &idx) == 1 && idx == 366);
    assert(dateToIndex( 1,  1, 1999, &idx) == 0);
    assert(dateToIndex( 6,  7, 3600, &idx) == 1 && idx == 188);
    assert(dateToIndex(29,  2, 3600, &idx) == 1 && idx == 60);
    assert(dateToIndex(29,  2, 4000, &idx) == 0);

    return 0;
}
#endif /* __PROGTEST__ */

