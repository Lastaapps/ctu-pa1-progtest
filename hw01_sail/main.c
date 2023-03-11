
#include <stdio.h>
#include <math.h>
#include <float.h>

//#define DEBUG

char readValidNumber(double *toRead);

char isSailSmaller(double clothWidth, double clothHeight, double sailWidth, double sailHeight);
char isPossible(double clothWidth, double clothHeight, double sailWidth, double sailHeight, double overlay);
int getClothsForSail(double clothWidth, double clothHeight, double sailWidth, double sailHeight, double overlay);

double safeCeil(double number);
char doubleSafeEquals(double x, double y);
char doubleSafeEqualsOrGreater(double bigger, double smaller);

void printInvalidInput();
void printNumberOfPieces(int number);


int main(int argCount, char **args) {

	//input fields initialization
	double clothWidth, clothHeight;
	double sailWidth, sailHeight;
	double overlay; 


	//read cloth sizes
	printf("Velikost latky:\n");

	if (!(readValidNumber(&clothWidth) && readValidNumber(&clothHeight))) {
		printInvalidInput();
		return 11;
	}

	//read sail sizes
	printf("Velikost plachty:\n");

	if (!(readValidNumber(&sailWidth) && readValidNumber(&sailHeight))) {
		printInvalidInput();
		return 21;
	}



	//exit when the sail is smaller than the cloth
	if (isSailSmaller(clothWidth, clothHeight, sailWidth, sailHeight) == 1) {
		printNumberOfPieces(1);
		return 0;
	}


	//read overlay input
	printf("Prekryv:\n");


	if (!(scanf(" %lf", &overlay) == 1 && overlay >= 0.0)) {
		printInvalidInput();
		return 31;
	}



	int normal = -1;
	int rotated = -1;

	if (isPossible(clothWidth, clothHeight, sailWidth, sailHeight, overlay)) {
		normal = getClothsForSail(clothWidth, clothHeight, sailWidth, sailHeight, overlay);
	}

	if (isPossible(clothWidth, clothHeight, sailHeight, sailWidth, overlay)) {
		rotated = getClothsForSail(clothWidth, clothHeight, sailHeight, sailWidth, overlay);
	}

	if (normal < 0 && rotated < 0) {
		printf("Nelze vyrobit.\n");
		return 32;
	}

	int clothNumber = (normal < rotated && normal > 0)
		|| (rotated < normal && 0 >= rotated)
		? normal : rotated;

	printNumberOfPieces(clothNumber);

	return 0;
}


//read double greater than 0
char readValidNumber(double *toRead) {
	return (scanf(" %lf", toRead) == 1 && *toRead > 0.0) ? 1 : 0;
}


char isSailSmaller(double clothWidth, double clothHeight, double sailWidth, double sailHeight) {
	return (doubleSafeEqualsOrGreater(clothWidth, sailWidth) 
			&& doubleSafeEqualsOrGreater(clothHeight, sailHeight))
	   	|| (doubleSafeEqualsOrGreater(clothWidth, sailHeight) 
			&& doubleSafeEqualsOrGreater(clothHeight, sailWidth));
}

char isPossible(double clothWidth, double clothHeight, double sailWidth, double sailHeight, double overlay) {
	return ((doubleSafeEqualsOrGreater(clothWidth, overlay)
				|| doubleSafeEqualsOrGreater(clothWidth, sailWidth))
			&& (doubleSafeEqualsOrGreater(clothHeight, overlay)
				|| doubleSafeEqualsOrGreater(clothHeight, sailHeight)));
}

int getClothsForSail(double clothWidth, double clothHeight, double sailWidth, double sailHeight, double overlay) {

	int width, height;

	if (doubleSafeEqualsOrGreater(clothWidth, sailWidth))
	   	width = 1; 
	else
		width = safeCeil((sailWidth - overlay)/(clothWidth - overlay));

	if (doubleSafeEqualsOrGreater(clothHeight, sailHeight)) 
		height = 1; 
	else
		height = safeCeil((sailHeight - overlay)/(clothHeight - overlay));

#ifdef DEBUG
	printf("Test it: %d\n", doubleSafeEqualsOrGreater(clothHeight, sailHeight));
	printf("Data: %lf, %lf\n", clothHeight, sailHeight);
	printf("Results: %d, %d\n", width, height);
#endif

	return width * height;
}



//safe operatoins on doubles ---------------------------------------------------
double safeCeil(double number) {
	if (doubleSafeEquals(number, round(number))) {
		return round(number); //to prevent errors with an inaccuary
	} else {
		return ceil(number);
	}	
}

char doubleSafeEqualsOrGreater(double bigger, double smaller) {
	return doubleSafeEquals(bigger, smaller) || bigger > smaller;
}

//inspired form https://stackoverflow.com/questions/17333/what-is-the-most-effective-way-for-float-and-double-comparison
char doubleSafeEquals(double x, double y) {
	return fabs(x - y) <= DBL_EPSILON * (fabs(x) < fabs(y) ? fabs(y) : fabs(x));
}



//output printing ---------------------------------------------------------------
void printNumberOfPieces(int number) {
	printf("Pocet kusu latky: %d\n", number);
}

void printInvalidInput() {
	printf("Nespravny vstup.\n");
}


