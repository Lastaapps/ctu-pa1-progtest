#ifndef __PROGTEST__
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#endif /* __PROGTEST__ */

//number of joules required to switch from x to y in format of _x_y
#define _0_1 4
#define _1_2 5
#define _2_3 2
#define _3_4 3
#define _4_5 3
#define _5_6 1
#define _6_7 5
#define _7_8 4
#define _8_9 1
#define _9_0 2
#define _2_0 3
#define _3_0 3
#define _5_0 3

/**
 * The main file data input
 * Gets the numbur of joules required to run a clock for the time perion given
 * @param[in] y1 start year
 * @param[in] m1 start month
 * @param[in] d1 start day
 * @param[in] h1 start hour
 * @param[in] i1 start minute
 * @param[in] y2 end year
 * @param[in] m2 end month
 * @param[in] d2 end day
 * @param[in] h2 end hour
 * @param[in] i2 end minute
 * @param[out] consumption used to return back the number of joules
 * @return 1 if data could be processed, 0 for invalid input
 */
int energyConsumption ( int y1, int m1, int d1, int h1, int i1,
		int y2, int m2, int d2, int h2, int i2, long long int * consumption );

/**
 * Get the number of joules consumed between the 1st January startYear 00:00 and the moment in the future
 * @param[in] startYear year from witchs 1st January 00:00 consuption is computed
 * @param[in] endYear the year of the end of the interval
 * @param[in] month the month of the end of the interval
 * @param[in] day the day of the end of the interval
 * @param[in] hour the hour of the end of the interval
 * @param[in] minute the minute of the end of the interval
 * @return the number of joules consumed
 */
long long int getJoulesInInterval(int startYear, int endYear, int month, int day, int hour, int minute);
/**
 * Gets the number of days from 1st January startYear to 31 December (endYear - 1) including, works with leap years
 * @param[in] start the starting year
 * @param[in] end the ending year, no days from it are actually counted
 * @return the number of days between the years
 */
long long int daysBetweenYears(int start, int end);
/**
 * Gets the number of days from 1st January till the date given excluding the date itself
 * @param[in] year the year of the date
 * @param[in] montht the month of the date
 * @param[in] day the day of month of the date
 * @return the number of days form 1st January
 */
short daysInYear(int year, int month, int day);

/**
 * Computes how many joules where consumed from a midnight to the time given that day
 * @param[in] hour - hour of day in 24 format
 * @param[in] minute - minut of hour
 * @return number of joules consumed from a midnight
 */
int joulesInDay(int hour, int minute);
/**
 * Same as calling countJules(ticks, 10), see doc there
 */
int in10(char ticks);
/**
 * Same as calling countJules(ticks, 6), see doc there
 */
int in6(char ticks);
/**
 * Same as calling countJules(ticks, 4), see doc there
 */
int in4(char ticks);
/**
 * Same as calling countJules(ticks, 3), see doc there
 */
int in3(char ticks);
/**
 * Computes the number of joules consumed by a digit from 0 state to the number given
 * @param ticks - the digit for which we want to know the consuption, cannot be greater than overflow
 * @param overflow - when number falls back to zero, valid inputs are 3, 4, 6 and 10
 * @return energy required to get to the digit in ticks param
 */
int countJoules(char ticks, char oveflow);

//--- VALIDATION -----------------------------------------
/**
 * Checks if the main file input from energyConsuption function() is valid
 * Params are the same as energyConsumption()
 * @return 1 if input is valid, 0 if it is non valid
 */
char validateInput( int y1, int m1, int d1, int h1, int i1,
		int y2, int m2, int d2, int h2, int i2);
/**
 * Checks if the date given actually exists
 * @return 1 if it does, 0 otherwise
 */
char checkDayValidity(int year, int month, int day);

//--- LEAP YEARS ------------------------------------------
/**
 * @param[in] start of the years interval, can be counted as leap
 * @param[in] end of the years interval, even if leap it is not considered in the value returned
 * @return number of leap years between the two years given including the starting one and
 * excluding the ending one
 */
int leapYearsInInterval(int start, int end);
/**
 * Checks if year is leap or not
 * @return 1 if the year is leap, 0 if not
 */
char isLeapYear(int year);



//--- PROGRAM ---------------------------------------------

//number of joules in one ...
const int oneMinute = in6(6) + 6 * in10(10);
const int oneHour = in6(6) + 6 * in10(10) + oneMinute * 60;
const int oneDay = in3(3) + in4(4) + 2 * in10(10) + 24 * oneHour;

int energyConsumption ( int y1, int m1, int d1, int h1, int i1,
		int y2, int m2, int d2, int h2, int i2, long long int * consumption ) {

	if (validateInput(y1, m1, d1, h1, i1, y2, m2, d2, h2, i2) == 0)
		return 0;

	*consumption = getJoulesInInterval(y1, y2, m2, d2, h2, i2)
		- getJoulesInInterval(y1, y1, m1, d1, h1, i1);

	return 1;
}

long long int getJoulesInInterval(int startYear, int endYear, int month, int day, int hour, int minute) {

	long long int days = daysBetweenYears(startYear, endYear);
	days += daysInYear(endYear, month, day);

	long long int daysJoules = days * oneDay;
	long long int inDayJoules = joulesInDay(hour, minute);

	return daysJoules + inDayJoules;
}

long long int daysBetweenYears(int start, int end) {
	int leapYears = leapYearsInInterval(start, end);

	return (end - start - leapYears) * 365LL + leapYears * 366LL;
}

short daysInYear(int year, int month, int day) {

	//to work with an index of the day
	short days = day - 1;

	switch (month - 1) {
		case 11: days += 30;
		case 10: days += 31;
		case 9: days += 30;
		case 8: days += 31;
		case 7: days += 31;
		case 6: days += 30;
		case 5: days += 31;
		case 4: days += 30;
		case 3: days += 31;
		case 2: days += isLeapYear(year) ? 29 : 28;
		case 1: days += 31;
	}

	return days;
}

int joulesInDay(int hour, int minute) {

	int forMinutes = in6(minute / 10) + (minute / 10) * in10(10) + in10(minute % 10) + minute * oneMinute;
	int forHours = in3(hour / 10) + (hour / 10) * in10(10) + in10(hour % 10) + hour * oneHour;

	return forHours + forMinutes;
}

int in10(char ticks) { return countJoules(ticks, 10); }
int in6(char ticks) { return countJoules(ticks, 6); }
int in4(char ticks) { return countJoules(ticks, 4); }
int in3(char ticks) { return countJoules(ticks, 3); }

int countJoules(char ticks, char overflow) {

	int e = 0;

	switch(ticks) {
		case 10:
			e += _9_0;
		case 9:
			e += _8_9;
		case 8:
			e += _7_8;
		case 7:
			e += _6_7;
		case 6:
			if (overflow == 6)
				e += _5_0;
			else
				e += _5_6;
		case 5:
			e += _4_5;
		case 4:
			if (overflow == 4)
				e += _3_0;
			else
				e += _3_4;
		case 3:
			if (overflow == 3)
				e += _2_0;
			else
				e += _2_3;
		case 2:
			e += _1_2;
		case 1:
			e += _0_1;
		case 0:
			e += 0;
	}

	return e;
}


// --- INPUT VALIDATION -----------------------------------
char validateInput( int y1, int m1, int d1, int h1, int i1,
		int y2, int m2, int d2, int h2, int i2) {

	if (1 > m1 || m1 > 12 || 1 > m2 || m2 > 12)
	   return 0;
	if (0 > h1 || h1 > 23 || 0 > h2 || h2 > 23)
	   return 0;
	if (0 > i1 || i1 > 59 || 0 > i2 || i2 > 59)
	   return 0;

	if (checkDayValidity(y1, m1, d1) == 0 || checkDayValidity(y2, m2, d2) == 0)
		return 0;

	if (y1 < 1600) {
		return 0;

	} else if (y1 > y2) {
		return 0;

	} else if (y1 == y2) {

		if (m1 > m2) {
			return 0;

		} else if (m1 == m2) {

			if (d1 > d2) {
				return 0;

			} else if (d1 == d2) {

				if (h1 > h2) {
					return 0;

				} else if (h1 == h2) {

					if (i1 > i2) {
						return 0;
					}
				}
			}
		}
	}

	return 1;
}

char checkDayValidity(int year, int month, int day) {

	char isLeap = isLeapYear(year);
	char febDays = isLeap ? 29 : 28;

	switch(month) {
		case 1:
		case 3:
		case 5:
		case 7:
		case 8:
		case 10:
		case 12:
			return !(1 > day || day > 31);
		case 4:
		case 6:
		case 9:
		case 11:
			return !(1 > day || day > 30);
		case 2:
			return !(1 > day || day > febDays);
	}

	return 1;
}

//--- TIME -------------------------------------------
int leapYearsInInterval(int start, int end) {

	start -= 1;
	end -= 1;

	return 0
		- (end / 4000 - start / 4000)
		+ (end / 400 - start / 400)
		- (end / 100 - start / 100)
		+ (end / 4 - start / 4);
}

char isLeapYear(int year) {
	return year % 4000 != 0
		&& (year % 400 == 0 || year % 100 != 0)
		&& year % 4 == 0;
}


#ifndef __PROGTEST__
//--- TESTS -------------------------------------------------------------------------------------------------------

//Tests declaration
void testWrongInput();
void testCalendar();
void testDifferences();
void testConsumption();

void testWrongInput() {

	long long int consumption = -1;
	assert ( energyConsumption (2021, 11,  1, 12,  0,
				2021, 10,  1, 12,  0, &consumption ) == 0 );
	assert ( energyConsumption (2021, 10, 32, 12,  0,
				2021, 11, 10, 12,  0, &consumption ) == 0 );
	assert ( energyConsumption (2100,  2, 29, 12,  0,
				2100,  2, 29, 12,  0, &consumption ) == 0 );
	//stolen help from progtest
	assert ( energyConsumption ( 2037, 1, 23, 23, 45, 2037, 1, 23, 23, 30, &consumption ) == 0);

	assert( validateInput(2001, 1, 1, 0, 0, 2000, 1, 1, 0, 0) == 0);
	assert( validateInput(0, 1, 1, 0, 0, 2000, 1, 1, 0, 0) == 0);
	assert( validateInput(1599, 1, 1, 0, 0, 2000, 1, 1, 0, 0) == 0);
	assert( validateInput(1600, 1, 1, 0, 0, 2000, 1, 1, 0, 0) == 1);

	printf("PASSED: Invalid input\n");
}

void testCalendar() {

	assert(leapYearsInInterval(1999, 2011) == 3);
	assert(leapYearsInInterval(2000, 2011) == 3);
	assert(leapYearsInInterval(2001, 2011) == 2);
	assert(leapYearsInInterval(2000, 2012) == 3);
	assert(leapYearsInInterval(2000, 2013) == 4);
	assert(leapYearsInInterval(2000, 2013) == 4);
	assert(leapYearsInInterval(2099, 2101) == 0);
	assert(leapYearsInInterval(2399, 2401) == 1);
	assert(leapYearsInInterval(3999, 4001) == 0);
	assert(leapYearsInInterval(1818, 6969) == 1249);

	assert(isLeapYear(2001) == 0);
	assert(isLeapYear(2004) == 1);
	assert(isLeapYear(2100) == 0);
	assert(isLeapYear(2400) == 1);
	assert(isLeapYear(4000) == 0);

	printf("PASSED: Time\n");
}

void testDifferences() {

	printf("PASSED: Differencess\n");

	//printf("Debug: %d\n", oneDay);
	//printf("00:00 %d\n", joulesInDay(0, 0));

	assert(in10(10) == 30);
	assert(in6(6) == 20);
	assert(in4(4) == 14);
	assert(in3(3) == 12);

	assert(oneMinute == 200);
	assert(oneHour == 12200);
	assert(oneDay == 292886);

	assert(joulesInDay(0, 1) == 204);
	assert(joulesInDay(0, 2) == 409);
	assert(joulesInDay(1, 0) == 12204);
	assert(joulesInDay(2, 0) == 24409);

}

void testConsumption() {

	long long int consumption = -1;

	assert ( energyConsumption ( 2021, 10,  1, 13, 15,
				2021, 10,  1, 18, 45, &consumption ) == 1
			&& consumption == 67116LL );
	assert ( energyConsumption ( 2021, 10,  1, 13, 15,
				2021, 10,  2, 11, 20, &consumption ) == 1
			&& consumption == 269497LL );
	assert ( energyConsumption ( 2021,  1,  1, 13, 15,
				2021, 10,  5, 11, 20, &consumption ) == 1
			&& consumption == 81106033LL );
	assert ( energyConsumption ( 2024,  1,  1, 13, 15,
				2024, 10,  5, 11, 20, &consumption ) == 1
			&& consumption == 81398919LL );
	assert ( energyConsumption ( 1900,  1,  1, 13, 15,
				1900, 10,  5, 11, 20, &consumption ) == 1
			&& consumption == 81106033LL );
	assert ( energyConsumption ( 2021, 10,  1,  0,  0,
				2021, 10,  1, 12,  0, &consumption ) == 1
			&& consumption == 146443LL );
	assert ( energyConsumption ( 2021, 10,  1,  0, 15,
				2021, 10,  1,  0, 25, &consumption ) == 1
			&& consumption == 2035LL );
	assert ( energyConsumption ( 2021, 10,  1, 12,  0,
				2021, 10,  1, 12,  0, &consumption ) == 1
			&& consumption == 0LL );
	assert ( energyConsumption ( 2021, 10,  1, 12,  0,
				2021, 10,  1, 12,  1, &consumption ) == 1
			&& consumption == 204LL );
	assert ( energyConsumption ( 2400,  2, 29, 12,  0,
				2400,  2, 29, 12,  0, &consumption ) == 1
			&& consumption == 0LL );

	//stolen from progrest help
	assert ( energyConsumption ( 2189, 3, 19, 13, 54,
				205728032, 10, 19, 12, 55, &consumption ) == 1 && consumption == 22007386674450685LL);

	printf("PASSED: Consumption\n");
}

int main ( int argc, char * argv [] ) {

	printf("RUNNING TESTS\n");

	testWrongInput();
	testCalendar();
	testDifferences();
	testConsumption();

	printf("DONE \nCongratulations!\n");

	return 0;
}
#endif /* __PROGTEST__ */
