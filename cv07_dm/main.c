#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <float.h>

void fillArray(int arr[], int length, int value);
char isEqualsOrGreater(double bigger, double smaller);
char isEquals(double x, double y);
void printError();
void printUnsolvable();


const int undefined = -1;
const int size = 'Z' - 'A' + 1;

int main (void) {


	printf("Pocet stran:\n");

	int partyNumber;

	if (scanf(" %d", &partyNumber) != 1
			|| partyNumber < 2
			|| partyNumber > size) {
		printError();
		return EXIT_FAILURE;
	}




	printf("Strany a pocet hlasu:\n");

	int votesPerParty[size];
	fillArray(votesPerParty, size, undefined);

	//readvores per party
	for (int i = 0; i < partyNumber; i++) {

		char party;
		int votes;

		if (scanf(" %c %d", &party, &votes) != 2
				|| party < 'A' || party > 'A' + partyNumber - 1
				|| votesPerParty[party - 'A'] != undefined
				|| votes <= 0) {

			printError();
			return EXIT_FAILURE;
		}

		votesPerParty[party - 'A'] = votes;
	}



	printf("Pocet horniku:\n");

	int totalWorkers;

	if (scanf(" %d", &totalWorkers) != 1
			|| totalWorkers <= 0) {
		printError();
		return EXIT_FAILURE;
	}

	double scorePerParty[size];

	//init score
	for (int i = 0; i < partyNumber; i++) {
		scorePerParty[i] = votesPerParty[i] / 1.42;
	}

	int workersPerParty[size];
	fillArray(workersPerParty, size, 0);

	int issuedWorkers = 0;
	while (issuedWorkers < totalWorkers) {

		int max = 0;
		//find max score
		for (int j = 1; j < partyNumber; j++) {

			double maxScore = scorePerParty[max], partyScore = scorePerParty[j];


			if ( isEquals(maxScore, partyScore)) {

				int maxVotes = votesPerParty[max], partyVotes = votesPerParty[j];

				if (maxVotes < partyVotes) {
					max = j;

				} else if (maxVotes == partyVotes) {

					printUnsolvable();
					return EXIT_FAILURE;
				}
			} else if ( !isEqualsOrGreater(scorePerParty[max], scorePerParty[j])) {
				max = j;
			}
		}

		issuedWorkers++;
		workersPerParty[max]++;

		scorePerParty[max] = votesPerParty[max] / (1 + workersPerParty[max]);
	}


	printf("Pridelene pocty:\n");

	for (int i = 0; i < partyNumber; i++) {
		printf("%c: %d\n", i + 'A', workersPerParty[i]);
	}


	return EXIT_SUCCESS;
}

void fillArray(int arr[], int length, int value) {
	for (int i = 0; i < length; i++)
	   arr[i] = value;
}

char isEqualsOrGreater(double bigger, double smaller) {
        return isEquals(bigger, smaller) || bigger > smaller;
}

char isEquals(double x, double y) {
        return fabs(x - y) <= 128 * DBL_EPSILON * (fabs(x) + fabs(y));
}

void printError() {
	printf("Nespravny vstup.\n");
}

void printUnsolvable() {
	printf("Nelze rozdelit.\n");
}





