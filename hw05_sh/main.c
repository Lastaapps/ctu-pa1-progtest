#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * A structure holding item name and the number of sells
 * @param name the name of the item
 * @param count the number of items sold
 */
typedef struct Item Item;

/**
 * Read the number of items to monitor
 * @param[out] monitored number of items to print out
 * @return 1 for succes, 0 otherwise
 */
char readMonitored(int * p_monitored);
/**
 * Does all the work of monitoring stdin and responding to questions
 * @param[int] monitored number of items to print out
 * @return 1 for succes, 0 otherwise
 */
char manageInput(int monitored);
/**
 * Free all 3 arrays
 */
void freeAll(Item items[], int sortedName[], int sortedCount[]);
/**
 * Reads a new item from stdin
 * @param[out] item item read
 * @return 1 for succes, 0 otherwise
 */
char readNewItem(Item * p_item);
/**
 * Adds a new item to an array and expands it if needed
 * @param[out] items array to add an item to
 * @param[out] itemsSortedName array to add an item to sorted by name
 * @param[out] itemsSortedCount array to add an item to sorted by count
 * @param[in] newItem item to add
 * @param[out] allocated the size of the array in memory
 * @param[out] length number of items already in the array
 */
void handleNewItem(Item * p_items[], int * p_sortedName[], int * p_sortedCount[], const Item newItem, int * p_allocated, int * p_length);

/**
 * Sort items by count
 * @param[out] items items to sort
 * @param[in] size the number of items in the array
 */
void sort(int itemIndexes[], int size);
/**
 * Prints monitored items
 * @param[in] items items to get data from, gonna be sorted
 * @param[in] size the number of items
 * @param[in] monitored number of items to print out
 */
void printItemList(const Item items[], const int itemIndexes[], const int size, const int monitored);
/**
 * Prints monitored items
 * @param[in] items items to get data from, gonna be sorted
 * @param[in] size the number of items
 * @param[in] monitored number of items to print out
 */
void printItemListTotalOnly(const Item items[], const int itemIndexes[], const int size, const int monitored);
/**
 * Print item name, count and in witch positions it belongs to
 * @param[in] items items to show
 * @param[in] start starting position
 * @param[in] end the last position
 */
void printItemGroups(const Item items[], const int itemsIndexes[], const int start, const int end);
/**
 * Print the total number of items in the monitored cathegory
 * @param[in] items the number of items
 */
void printMostSold(const int items);
/**
 * Item struct comparison for qsort() by name
 */
int compareItemsByName(const void* a, const void* b);
/**
 * Item struct comparison for qsort() by count
 */
int compareItemsByCount(const void* a, const void* b);

/**
 * Prints an error message
 */
void printError(void);




const char errorMonitored = 10;

struct Item {
	char name[100] = "";
	int count = 1;
};


/**
 * Global reference to items array
 * used for better items sorting
 */
Item ** g_items = NULL;


int main (void ) {

	int monitored;

	if (!readMonitored(&monitored)) {
		printError();
		return errorMonitored;
	}

	printf("Pozadavky:\n");

	if (!manageInput(monitored)) {
		printError();
		return 1;
	}

	return 0;
}

char readMonitored(int * p_monitored) {

	printf("Pocet sledovanych:\n");

	if (scanf(" %d", p_monitored) != 1 || *p_monitored <= 0) {
		return 0;
	}

	return 1;
}

char manageInput(const int monitored) {

	int allocated = 128;
	int itemsLength = 0;
	char sorted = 1;

	Item * items = (Item*) malloc(allocated * sizeof(*items));
	int * itemsSortedName = NULL;//(int*) malloc(allocated * sizeof(*items));
	int * itemsSortedCount = (int*) malloc(allocated * sizeof(*items));

	g_items = &items;

	Item newItem = Item{};

	while (true) {

		char type;
		int result = scanf(" %c", &type);

		if (result == -1) {

			freeAll(items, itemsSortedName, itemsSortedCount);
			return 1;

		} else if (result != 1) {

			freeAll(items, itemsSortedName, itemsSortedCount);
			return 0;
		}

		switch (type) {
			case '+':

				if (!readNewItem(&newItem)) {
					freeAll(items, itemsSortedName, itemsSortedCount);

					return 0;
				}

				handleNewItem(&items, &itemsSortedName, &itemsSortedCount, newItem, &allocated, &itemsLength);
				sorted = 0;

				/*
				for (int i = 0; i < itemsLength; i++) {
					Item item = items[i];
					printf("Item check: %s - %d\n", item.name, item.count);
				}
				for (int i = 0; i < itemsLength; i++) {
					Item * item = itemsSortedCount[i];
					printf("Memory printing: %s - %d\n", item->name, item->count);
				}
				*/

				break;

			case '#':

				if (sorted == 0) {
					sort(itemsSortedCount, itemsLength);
					sorted = 1;
				}

				printItemList(items, itemsSortedCount, itemsLength, monitored);
				break;

			case '?':

				if (sorted == 0) {
					sort(itemsSortedCount, itemsLength);
					sorted = 1;
				}

				printItemListTotalOnly(items, itemsSortedCount, itemsLength, monitored);
				break;

			default:
				freeAll(items, itemsSortedName, itemsSortedCount);
				return 0;
		}
	}

	freeAll(items, itemsSortedName, itemsSortedCount);

	return 0;
}

void freeAll(Item items[], int sortedName[], int sortedCount[]) {
	free(items);
	free(sortedName);
	free(sortedCount);
}

char readNewItem(Item * p_item) {

	char nextChar;

	int result = scanf(" %99s%c", p_item->name, &nextChar);

	if (result < 1 || strlen(p_item->name) == 0) {
		return 0;
	}
	if (result == 2 && nextChar > ' ') {
		return 0;
	}

	return 1;
}

void handleNewItem(Item * p_items[], int * p_sortedName[], int * p_sortedCount[], const Item newItem, int * p_allocated, int * p_length) {

	for (Item * p_item = *p_items; p_item < *p_items + *p_length; p_item ++) {
		if (strcmp(newItem.name, p_item->name) == 0) {
			p_item->count += 1;
			return;
		}
	}

	if (*p_allocated <= *p_length) {
		*p_allocated += 42 + *p_allocated / 2;
		*p_items = (Item*) realloc(*p_items, *p_allocated * sizeof(**p_items));
		//*p_sortedName = (int*) realloc(*p_sortedName, *p_allocated * sizeof(*p_sortedName));
		*p_sortedCount = (int*) realloc(*p_sortedCount, *p_allocated * sizeof(*p_sortedName));
	}

	(*p_items)[*p_length] = newItem;
	//(*p_sortedName)[*p_length] = *p_length;
	(*p_sortedCount)[*p_length] = *p_length;

	*p_length += 1;
}

void sort(int itemIndexes[], const int size) {
	qsort(itemIndexes, size, sizeof(*itemIndexes), compareItemsByCount);
}

void printItemList(const Item items[], const int itemIndexes[], const int size, const int monitored) {

	if (size <= 0) {
		printMostSold(0);
		return;
	}

	/*
	   for (int i = 0; i < size; i++) {
	   Item item = items[i];
	   printf("Item check: %s - %d\n", item.name, item.count);
	   }
	   */

	int totalSold = 0;

	int itemIndex = 0;
	int startIndex = 0;
	int latestCount = (items + itemIndexes[0])->count;

	while (true) {

		const Item * item = items + itemIndexes[itemIndex];
		const int itemCount = item->count;

		/*
		   printf("Current item: %s - %d\n", items[itemIndex].name, items[itemIndex].count);
		   printf("ItemIndex: %d\n", itemIndex);
		   printf("LatestCount: %d\n", latestCount);
		   printf("StartIndex: %d\n", startIndex);
		   */

		if (latestCount > itemCount) {

			//print
			printItemGroups(items, itemIndexes + startIndex, startIndex + 1, itemIndex);

			if (itemIndex >= monitored) {
				break;
			}

			//reset
			startIndex = itemIndex;
			latestCount = itemCount;
		}

		totalSold += itemCount;


		itemIndex++;

		//end size
		if (itemIndex >= size) {

			//print
			printItemGroups(items, itemIndexes + startIndex, startIndex + 1, itemIndex);

			break;
		}

		/*
		   for (int i = 0; i < itemIndex - startIndex; i++) {
		   printf("Items presented: %s - %d\n", currentItems[i] -> name, currentItems[i] -> count);
		   }
		   */
	}

	printMostSold(totalSold);
}

void printItemListTotalOnly(const Item items[], const int itemIndexes[], const int size, const int monitored) {

	if (size <= 0) {
		printMostSold(0);
		return;
	}

	int totalSold = 0;

	int itemIndex = 0;
	int latestCount = (items + itemIndexes[0])->count;

	while (true) {

		const Item * item = items + itemIndexes[itemIndex];
		const int itemCount = item->count;

		if (latestCount > itemCount) {

			if (itemIndex >= monitored) {
				break;
			}

			latestCount = itemCount;
		}

		totalSold += itemCount;

		itemIndex++;

		if (itemIndex >= size) {
			break;
		}
	}

	printMostSold(totalSold);
}

void printItemGroups(const Item items[], const int itemsIndexes[], const int start, const int end) {

	if (start == end) {
		printf("%d. %s, %dx\n", start, (items + itemsIndexes[0])->name, (items + itemsIndexes[0])->count);
		return;
	}

	for (int i = 0; i < end - start + 1; i++) {
		printf("%d.-%d. %s, %dx\n", start, end, (items + itemsIndexes[i])->name, (items + itemsIndexes[i])->count);
	}
}

void printMostSold(const int items) {
	printf("Nejprodavanejsi zbozi: prodano %d kusu\n", items);
}

int compareItemsByName(const void* a, const void* b) {
	const int index1 = *(const int*)a;
	const int index2 = *(const int*)b;
	const Item * arg1 = *g_items + index1;
	const Item * arg2 = *g_items + index2;

	return strcmp(arg1->name, arg2->name);
}

int compareItemsByCount(const void* a, const void* b) {
	const int index1 = *(const int*)a;
	const int index2 = *(const int*)b;
	const Item * arg1 = *g_items + index1;
	const Item * arg2 = *g_items + index2;

	return (arg1->count < arg2->count) - (arg1->count > arg2->count);
}

void printError(void) {
	printf("Nespravny vstup.\n");
}

