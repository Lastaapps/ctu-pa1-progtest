#ifndef __PROGTEST__
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>



// ---- STRUCTURES -----------------------------------

/**
 * Used in LinkedLists as Result to Láďa + hold info about a person
 * m_Next pointer to the next item in the sequence
 * m_ID id of the person
 * m_Name name of the person
 */
typedef struct TResult {
  struct TResult * m_Next;
  int              m_ID;
  char           * m_Name;
} TRESULT;

#endif /* __PROGTEST__ */

typedef struct TableItem TableItem;
typedef struct Person Person;

/**
 * How large are tables in HashMap in Database
 */
const unsigned int tableSize = 16;

/**
 * Database holding info about users
 * HashMap under the hood
 * table the array of binary trees
 */
typedef struct TDatabase {
	TableItem ** table;
} TDATABASE;

// To make Láďa's structure TNames usable
typedef int ID;
typedef TRESULT Result;
typedef TDATABASE DB;

/**
 * Represents binary tree item in Database (= HashMap)
 * person held structure with hash (person id)
 * lower next item wiht lower hash
 * greater next item with greater hash
 */
struct TableItem {
	Person * person;
	TableItem * lower;
	TableItem * greater;
};

/**
 * Holds info about a person
 * name name of the person, dynamicly allocated
 * id id of the prerson
 * p1 the first parent of the person
 * p2 the second parent of the person
 */
struct Person {
	char * name;
	ID id;
	ID p1;
	ID p2;
};




// ---- TESTING -----------------
#ifndef __PROGTEST__
typedef struct TestPerson TestPerson;


/**
 * Gets the length of an array
 */
#define arrLen(arr) sizeof((arr))/sizeof(*(arr))

/**
 * Holds basic data about a person, used in tests
 * name the name of the person
 * id the id of the person
 */
struct TestPerson {
	const char * name;
	const ID id;
};

/**
 * Prints content of the whole database
 * @param db database to print
 */
void printDB(DB * db);
/**
 * Used in printDB(), should'n be used elsewhere
 */
void printDBRecursive(int offset, TableItem * item);
/**
 * Runs basic db test
 */
void testDB();
/**
 * Tests ancestor base functions
 */
void testAncestors();
/**
 * Prints whole linked list
 * @param res the first element of the list to print
 */
void printLinkedList(Result * res);
#endif /* __PROGTEST__ */






// ---- PROGTEST PREDEFINED -------------------------
#ifndef __PROGTEST__
/**
 * Initializes database, allocates array for binary trees
 * @param db database to init
 */
void initAll (DB * db);
/**
 * Clear all the data from database (frees them from memory)
 * @param db database to free
 */
void doneAll(DB  * db );
/**
 * Adds a new person into database
 * @param db database to add the item in
 * @param id the id of the user
 * @param name the name of the user
 * @param p1 the id of the first parent
 * @param p2 the id of the second parent
 * @return if the user was actually added
 */
int addPerson( DB * db, ID id, const char * name, ID p1, ID p2 );
/**
 * Gets all the ancestors of a person
 * @param a db database to get the data from
 * @param the id of the person
 * @return the LinkedList of persons ancestors
 */
Result * ancestors (DB * db, ID id);
/**
 * Gets all the common ancestors for 2 persons
 * @param db database to search in
 * @param id1 the id of the first person
 * @param id2 the id of the second person
 * @return the LinkedList of the common ancestors of the 2 persons
 */
Result * commonAncestors(DB * db, ID id1, ID id2);

#endif /* __PROGTEST__ */






/**
 * Adds a person to a database, but do not realocate memory for it
 * db the database to place the person in
 * person the person to place into the database
 * @return if the person was added or it was already in the database
 */
int addExistingPerson( DB * db, Person * person);
/**
 * Adds a new item to the correct place in Hashmaps binary tree
 * @param item the current tree node
 * @param person a person to be placed in the tree
 */
int addRecursive(TableItem ** item, Person * person);
/**
 * Creates tree node for HashMap, allocated dynamically
 * @param person contained in the new node
 * @return pointer to the new node
 */
TableItem * createTableItem(Person * person);
/**
 * Fits a person into corect section in a hashtable in a database
 * @param id hashcode of an item to add
 * @return index in HashMap table
 */
int getIndex(ID id);


/**
 * Clears everything in and under this node of a tree
 * @param item tree node to clear
 */
void clearRecursive(TableItem * item);
/**
 * Clears database nodes, but not their contents
 * @param db a databse to clear
 */
void doneTemp(DB * db );
/**
 * Clears a node of a tree and all the subnodes, content remains in memory
 * @param item node to cleaer
 */
void clearTempRecursive(TableItem * item);



/**
 * Tries to find the person given by it's id in a database
 * @param db the database to search in
 * @param id id (= hash) to look for
 */
Person * findPerson(DB * db, ID id);
/**
 * Called from findPerson(), searches tree node and it's subnodes for id
 */
Person * findRecursive(TableItem * item, ID id);
/**
 * Checks HashMap table if there are any items linked to it
 */
int isEmpty(DB * db);




/**
 * Goes thoŕough database and finds all the ancestors of a person
 * @param isFirst if this is the initial call, used to ignore person itself
 * @param db the database to search in
 * @param id the id to look for
 * @param dst database to save found items to
 */
void searchAncestors(char isFirst, DB * db, ID id, DB * dst);
/**
 * Convers database into a LinkedList
 * @param db the database to convert
 * @return LinkedList of all the items in the database
 */
Result * dbToLinkedList(DB * db);
/**
 * Implementation of dbToLinkedList, add all the items under a node
 * @param item the tree node to add items from
 * @param toAdd pointer to the last item of forming LinkedList
 */
void dbToLinkedListRecursive(TableItem * item, Result ** toAdd);


/**
 * Creates the LinkedList of the items if both databases
 * @param db1 one database
 * @param db2 the other database
 * @param toAdd pointer to the last item of forming LinkedList
 */
void databaseIntersect(DB * db1, DB * db2, Result ** toAdd);
/**
 * Implementation of databaseIntersect() for each tree node
 * @param item tree item to add intersected items for from one database
 * @param db2 the other database to look for items
 * @param toAdd pointer to the last item of forming LinkedList
 */
void databaseIntersectRecursive(TableItem * item, DB * db2, Result ** toAdd);

/**
 * Adds a person into a LinkedList
 * @param toAdd pointer to the last item of forming LinkedList
 * @param person the person to add
 */
void addToLinkedList(Result ** toAdd, Person * person);
/**
 * Create a new dynamically allocated LinkedList node containing person pointer
 * @param person the person to point to
 * @return pointer to the created item
 */
Result * createResult(Person * person);





//
// ---- DATABASE ------------------------------------------------
//

// ---- DATABASE - INIT, CLEAN ----------------------------------
void initAll (DB * db) {
	db->table = (TableItem**) malloc(tableSize * sizeof(*(db->table)));
	for (unsigned int i = 0; i < tableSize; i++)
		db->table[i] = NULL;
}

void doneAll(DB  * db ) {
	for (unsigned int i = 0; i < tableSize; i++) {
		clearRecursive(db->table[i]);
	}

	free(db->table);
}

void clearRecursive(TableItem * item) {
	if (item == NULL) return;

	clearRecursive(item->lower);
	clearRecursive(item->greater);

	free(item->person->name);
	free(item->person);
	free(item);
}

void doneTemp(DB  * db ) {
	for (unsigned int i = 0; i < tableSize; i++) {
		clearTempRecursive(db->table[i]);
	}

	free(db->table);
}

void clearTempRecursive(TableItem * item) {
	if (item == NULL) return;

	clearTempRecursive(item->lower);
	clearTempRecursive(item->greater);

	free(item);
}

// ---- DABABASE - ADDING ITEMS -------------------------------------
int addPerson( DB * db, ID id, const char * name, ID p1, ID p2 ) {

	if (p1 == p2 && p1 != 0)
		return 0;

	if (id == 0) return 0;

	if (p1 != 0 && findPerson(db, p1) == NULL)
		return 0;
	if (p2 != 0 && findPerson(db, p2) == NULL)
		return 0;

	size_t nameLen = strlen(name);
	//if (nameLen == 0) return 0;
	char * newName = (char*) malloc((nameLen + 1) * sizeof(*name));

	Person * person = (Person*) malloc(sizeof(*person));
	*person = {newName, id, p1, p2};

	if (addExistingPerson(db, person)) {

		for (unsigned int i = 0; i < nameLen + 1; i++)
			newName[i] = name[i];

		return 1;

	} else {

		free(person);
		free(newName);

		return 0;
	}
}

int addExistingPerson( DB * db, Person * person ) {
	return addRecursive(&(db->table[getIndex(person->id)]), person);
}

int addRecursive(TableItem ** item, Person * person) {

	if (*item == NULL) {
		*item = createTableItem(person);
		return 1;
	}

	if ((*item)->person->id > person->id) {
		return addRecursive(&((*item)->lower), person);

	} else if ((*item)->person->id < person->id) {
		return addRecursive(&((*item)->greater), person);

	} else {
		return 0;
	}
}

TableItem * createTableItem(Person * person) {

	TableItem * item = (TableItem*) malloc(sizeof(TableItem));
	item->person = person;
	item->lower = NULL;
	item->greater = NULL;

	return item;
}

int getIndex(ID id) {
	return id & (tableSize - 1);
}


// ---- DATABASE - FIND --------------------------------------------
Person * findPerson(DB * db, ID id) {
	return findRecursive(db->table[getIndex(id)], id);
}

Person * findRecursive(TableItem * item, ID id) {
	if (item == NULL)
		return NULL;

	if (item->person->id > id) {
		return findRecursive(item->lower, id);

	} else if (item->person->id < id) {
		return findRecursive(item->greater, id);

	} else {
		return item->person;
	}
}

int isEmpty(DB * db) {
	for (unsigned int i = 0; i < tableSize; i++) {
		if(db->table[i] != NULL) {
			return 0;
		}
	}
	return 1;
}

//
// ---- ANCESTORS -----------------------------------------------
//
Result * ancestors (DB * db, ID id) {

	DB dst = {};
	initAll(&dst);

	searchAncestors(true, db, id, &dst);

	Result * list =  dbToLinkedList(&dst);

	doneTemp(&dst);

	return list;
}

void searchAncestors(char isFirst, DB * db, ID id, DB * dst) {

	if (id == 0) return;

	Person * p = findPerson(db, id);
	if (p == NULL)
		return;

	if (!isFirst)
		addExistingPerson(dst, p);

	searchAncestors(false, db, p->p1, dst);
	searchAncestors(false, db, p->p2, dst);
}

// ---- SEARCHING ------------------------------------------------
Result * dbToLinkedList(DB * db) {

	Result start = {NULL, 0, 0};
	Result * current = &start;

	for (unsigned int i = 0; i < tableSize; i++) {
		dbToLinkedListRecursive(db->table[i], &current);
	}

	return start.m_Next;
}

void dbToLinkedListRecursive(TableItem * item, Result ** toAdd) {

	if (item == NULL) return;

	Person * person = item->person;
	addToLinkedList(toAdd, person);

	dbToLinkedListRecursive(item->lower, toAdd);
	dbToLinkedListRecursive(item->greater, toAdd);
}

//
// ---- COMMON ANCESTORS -----------------------------------------
//
Result * commonAncestors(DB * db, ID id1, ID id2) {

	if (id1 == id2)
		return ancestors(db, id1);

	DB db1 = {};
	DB db2 = {};
	initAll(&db1);
	initAll(&db2);

	searchAncestors(true, db, id1, &db1);
	searchAncestors(true, db, id2, &db2);

	if (isEmpty(&db1) || isEmpty(&db2)) {
		doneTemp(&db1);
		doneTemp(&db2);
		return NULL;
	}

	Result start = {NULL, 0, 0};
	Result * current = &start;

	databaseIntersect(&db1, &db2, &current);

	doneTemp(&db1);
	doneTemp(&db2);

	return start.m_Next;
}

void databaseIntersect(DB * db1, DB * db2, Result ** toAdd) {
	for (unsigned int i = 0; i < tableSize; i++) {
		databaseIntersectRecursive(db1->table[i], db2, toAdd);
	}
}

void databaseIntersectRecursive(TableItem * item, DB * db2, Result ** toAdd) {

	if (item == NULL)
		return;
	Person * person = findPerson(db2, item->person->id);
	if (person != NULL) {
		addToLinkedList(toAdd, person);
	}

	databaseIntersectRecursive(item->lower, db2, toAdd);
	databaseIntersectRecursive(item->greater, db2, toAdd);
}

// ---- LINKED LIST
void addToLinkedList(Result ** toAdd, Person * person) {
	Result * newListItem = createResult(person);

	(*toAdd)->m_Next = newListItem;
	*toAdd = newListItem;
}

Result * createResult(Person * person) {
	Result * res = (Result*) malloc(sizeof(Result));

	res->m_Next = NULL;
	res->m_ID = person->id;
	res->m_Name = person->name;

	return res;
}

void freeResult(Result * res) {
  if (res == NULL)
	  return;

  freeResult(res->m_Next);
  free(res);
}

#ifndef __PROGTEST__

void printDB(DB * db) {

	for (unsigned int i = 0; i < tableSize; i++) {
		printf("Printing cell %u\n", i);
		printDBRecursive(1, db->table[i]);
	}
	printf("\n");
}

void printDBRecursive(int offset, TableItem * item) {
	if (item == NULL) return;

	for (int i = 0; i < offset; i++) printf(" ");
	Person p = *(item->person);
	printf("Item: ID: %d Name: %10s ", p.id, p.name);

	if (item->lower == NULL)
		printf("ch1: NULL ");
	else
		printf("ch1: %4d ", item->lower->person->id);

	if (item->greater == NULL)
		printf("ch2: NULL ");
	else
		printf("ch2: %4d ", item->greater->person->id);

	printf("\n");

	offset++;
	printDBRecursive(offset, item->lower);
	printDBRecursive(offset, item->greater);
}

void testDB() {

	//for (unsigned int i = 0; i < tableSize; i++)
		//printf("Index: %d - %d\n", i, getIndex(i));

	DB db = {};

	initAll(&db);

	assert(addPerson(&db, 1, "1", 0, 0 ) == 1);
	assert(addPerson(&db, 4, "4", 1, 0 ) == 1);
	assert(addPerson(&db, 36, "36", 4, 0 ) == 1);
	assert(addPerson(&db, 20, "20", 1, 0 ) == 1);
	assert(addPerson(&db, 52, "52", 4, 0 ) == 1);
	assert(addPerson(&db, 4, "4", 0, 0 ) == 0);
	//printDB(&db);
	assert(findPerson(&db, 4)->p1 == 1);
	assert(findPerson(&db, 36)->p1 == 4);
	assert(findPerson(&db, 20)->p1 == 1);
	assert(findPerson(&db, 52)->p1 == 4);
	assert(findPerson(&db, 69) == NULL);

	doneAll(&db);
}

void printLinkedList(Result * res) {

	printf("Printing linked list\n");
	while (res != NULL) {
		printf("%4d - %s\n", res->m_ID, res->m_Name);
		res = res->m_Next;
	}
	printf("\n");
}

int areTheSame(Result * res, TestPerson arr[], size_t size) {

	Result * start = res;

	size_t listLen = 0;
	while (res != NULL) {
		listLen++;
		res = res->m_Next;
	}

	//printf("%zd - %zd\n", size, listLen);
	if (size != listLen)
		return 0;

	for (unsigned int i = 0; i < size; i++) {

		TestPerson item = arr[i];

		char found = 0;
		res = start;
		while (res != NULL) {
			//printf("Cmp1: %d %s\n", item.id, item.name);
			//printf("Cmp2: %d %s\n", res->m_ID, res->m_Name);
			if (item.id == res->m_ID && strcmp(item.name, res->m_Name) == 0) {
				found = 1;
				break;
			}

			res = res->m_Next;
		}

		if (found == 0) {
			//printf("%d %s NOT Found\n", item.id, item.name);
			return 0;
		}
	}

	return 1;
}

void testAncestors() {

	DB db = {};
	Result * l = NULL;
	initAll(&db);

	assert(addPerson(&db,  1, "01", 0, 0) == 1);
	assert(addPerson(&db,  5, "05", 0, 1) == 1);
	assert(addPerson(&db,  2, "02", 0, 0) == 1);
	assert(addPerson(&db,  4, "04", 5, 0) == 1);
	assert(addPerson(&db,  3, "03", 4, 2) == 1);
	assert(addPerson(&db,  7, "07", 0, 1) == 1);
	assert(addPerson(&db,  6, "06", 4, 7) == 1);
	assert(addPerson(&db,  8, "08", 0, 0) == 1);
	assert(addPerson(&db,  9, "09", 0, 0) == 1);
	assert(addPerson(&db, 10, "10", 0, 0) == 1);
	printDB(&db);

	/*
	TestPerson arr0[] = {
		{"01",  1},
		{"02",  2},
		{"03",  3},
		{"04",  4},
		{"05",  5},
		{"06",  6},
		{"07",  7},
		{"08",  8},
		{"09",  9},
		{"10", 10}
	};
	*/

	TestPerson arr1[] = {
		{"01",  1},
		{"02",  2},
		{"04",  4},
		{"05",  5}
	};
	l = ancestors(&db, 3);
	printLinkedList(l);
	assert(areTheSame(l, arr1, arrLen(arr1)));
	freeResult ( l );
	l = commonAncestors(&db, 3, 3);
	printLinkedList(l);
	assert(areTheSame(l, arr1, arrLen(arr1)));
	freeResult ( l );

	TestPerson arr2[] = {
		{"01",  1},
		{"04",  4},
		{"05",  5}
	};
	l = commonAncestors(&db, 6, 3);
	printLinkedList(l);
	assert(areTheSame(l, arr2, arrLen(arr2)));
	freeResult ( l );
	l = commonAncestors(&db, 3, 6);
	printLinkedList(l);
	assert(areTheSame(l, arr2, arrLen(arr2)));
	freeResult ( l );

	l = ancestors(&db, 1);
	printLinkedList(l);
	assert(l == NULL);
	freeResult ( l );

	l = commonAncestors(&db, 1, 2);
	printLinkedList(l);
	assert(l == NULL);
	freeResult ( l );

	l = commonAncestors(&db, 1, 1);
	printLinkedList(l);
	assert(l == NULL);
	freeResult ( l );

	l = commonAncestors(&db, 69, 420);
	printLinkedList(l);
	assert(l == NULL);
	freeResult ( l );

	l = commonAncestors(&db, 68, 2);
	printLinkedList(l);
	assert(l == NULL);
	freeResult ( l );

	l = commonAncestors(&db, 68, 3);
	printLinkedList(l);
	assert(l == NULL);
	freeResult ( l );

	l = commonAncestors(&db, 0, 420);
	printLinkedList(l);
	assert(l == NULL);
	freeResult ( l );

	l = commonAncestors(&db, 0, 2);
	printLinkedList(l);
	assert(l == NULL);
	freeResult ( l );

	l = commonAncestors(&db, 0, 3);
	printLinkedList(l);
	assert(l == NULL);
	freeResult ( l );


	doneAll(&db);
}

int main (int argc, char * argv [] ) {

	testDB();
	testAncestors();

	char name[100];
	DB a, b;
	Result * l;

	// ---- A -----------------
	initAll ( &a );

	assert ( addPerson ( &a, 1, "John", 0, 0 ) == 1 );

	strncpy ( name, "Jane", sizeof ( name ) );
	assert ( addPerson ( &a, 2, name, 0, 0 ) == 1 );

	assert ( addPerson ( &a, 3, "Caroline", 0, 0 ) == 1 );
	assert ( addPerson ( &a, 4, "Peter", 0, 0 ) == 1 );
	assert ( addPerson ( &a, 5, "George", 1, 2 ) == 1 );
	assert ( addPerson ( &a, 6, "Martin", 1, 2 ) == 1 );
	assert ( addPerson ( &a, 7, "John", 3, 4 ) == 1 );
	assert ( addPerson ( &a, 8, "Sandra", 3, 4 ) == 1 );
	assert ( addPerson ( &a, 9, "Eve", 1, 2 ) == 1 );
	assert ( addPerson ( &a, 10, "Douglas", 1, 4 ) == 1 );

	strncpy ( name, "Phillipe", sizeof ( name ) );
	assert ( addPerson ( &a, 11, name, 6, 8 ) == 1 );

	strncpy ( name, "Maria", sizeof ( name ) );
	assert ( addPerson ( &a, 12, name, 5, 8 ) == 1 );

	printDB(&a);



	l = ancestors ( &a, 11 );
	printLinkedList(l);
	TestPerson arr0[] = {
		{"John",     	1},
		{"Jane",     	2},
		{"Caroline", 	3},
		{"Peter", 		4},
		{"Martin", 		6},
		{"Sandra", 		8}
	};
	assert(areTheSame(l, arr0, arrLen(arr0)));
	freeResult ( l );


	assert ( ancestors ( &a, 3 ) == NULL );
	assert ( ancestors ( &a, 13 ) == NULL );



	l = commonAncestors ( &a, 11, 12 );
	printLinkedList(l);
	TestPerson arr1[] = {
		{"John",     	1},
		{"Jane",     	2},
		{"Caroline", 	3},
		{"Peter", 		4},
		{"Sandra", 		8}
	};
	assert(areTheSame(l, arr1, arrLen(arr1)));
	freeResult ( l );


	l = commonAncestors ( &a, 10, 9 );
	printLinkedList(l);
	TestPerson arr2[] = {
		{"John",     	1},
	};
	assert(areTheSame(l, arr2, arrLen(arr2)));
	freeResult ( l );


	assert ( commonAncestors ( &a, 7, 6 ) == NULL );


	l = commonAncestors ( &a, 7, 10 );
	printLinkedList(l);
	TestPerson arr3[] = {
		{"Peter",     	4}
	};
	assert(areTheSame(l, arr3, arrLen(arr3)));
	freeResult ( l );

	assert ( addPerson ( &a, 13, "Quido", 12, 11 ) == 1 );

	l = ancestors ( &a, 13 );
	printLinkedList(l);
	TestPerson arr4[] = {
		{"John",     	1},
		{"Jane",     	2},
		{"Caroline", 	3},
		{"Peter", 		4},
		{"George",      5},
		{"Martin", 		6},
		{"Sandra", 		8},
		{"Phillipe",   11},
		{"Maria",      12}
	};
	assert(areTheSame(l, arr4, arrLen(arr4)));
	freeResult ( l );




	l = commonAncestors ( &a, 9, 12 );
	printLinkedList(l);
	TestPerson arr5[] = {
		{"John",     	1},
		{"Jane",     	2}
	};
	assert(areTheSame(l, arr5, arrLen(arr5)));
	freeResult ( l );

	assert ( addPerson ( &a, 1, "Francois", 0, 0 ) == 0 );


	l = ancestors ( &a, 12 );
	printLinkedList(l);
	TestPerson arr6[] = {
		{"John",     	1},
		{"Jane",     	2},
		{"Caroline", 	3},
		{"Peter", 		4},
		{"George",      5},
		{"Sandra", 		8}
	};
	assert(areTheSame(l, arr6, arrLen(arr6)));
	freeResult ( l );




	// ---- B ----------------------
	initAll ( &b );
	assert ( addPerson ( &b, 10000, "John", 0, 0 ) == 1 );
	assert ( addPerson ( &b, 10000, "Peter", 0, 0 ) == 0 );
	assert ( addPerson ( &b, 20000, "Jane", 10000, 0 ) == 1 );
	assert ( addPerson ( &b, 30000, "Maria", 10000, 10000 ) == 0 );
	assert ( addPerson ( &b, 40000, "Joe", 10000, 30000 ) == 0 );
	assert ( addPerson ( &b, 50000, "Carol", 50000, 20000 ) == 0 );
	assert ( addPerson ( &b, 12, "Maria", 20000, 10000 ) == 1 );

	printDB(&b);



	l = ancestors ( &b, 12 );
	printLinkedList(l);
	TestPerson arr7[] = {
		{"John",     	10000},
		{"Jane",     	20000}
	};
	assert(areTheSame(l, arr7, arrLen(arr7)));
	freeResult ( l );

	assert ( ancestors ( &a, 20000 ) == NULL );
	assert ( commonAncestors ( &b, 7, 10 ) == NULL );




	// ---- Cleanup -----------------
	doneAll ( &a );
	doneAll ( &b );

	return 0;
}
#endif /* __PROGTEST__ */
