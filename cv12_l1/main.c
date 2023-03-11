#ifndef __PROGTEST__
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef struct TItem {
  struct TItem * m_Next;
  int      m_Val;
} TITEM;

typedef struct TData {
  TITEM * m_First;
  TITEM * m_Last;
} TDATA;

#endif /* __PROGTEST__ */

typedef TITEM Item;
typedef TDATA Data;

Item * createItem(int x);
void removeItem(Data * l, Item * item, Item * prev);
int findMax (Data * l);

void insertStart ( Data * l, int x ) {

	Item * oldFirst = l->m_First;
	Item * newItem = createItem(x);

	l -> m_First = newItem;
	newItem -> m_Next = oldFirst;

	if (l -> m_Last == NULL) {
		l -> m_Last = newItem;
	}
}

void insertEnd( Data * l, int x ) {

	Item * oldLast = l -> m_Last;
	Item * newItem = createItem(x);
	newItem -> m_Next = NULL;

	if (oldLast != NULL) {
		oldLast -> m_Next = newItem;
	} else {
		l -> m_First = newItem;
	}
	l -> m_Last = newItem;
}

Item * createItem(int x) {
	Item * item = (Item*) malloc(sizeof(*item));
	item -> m_Val = x;
	return item;
}

int removeMax( Data * l ) {

	 if (l -> m_First == NULL)
		return 0;

	int max = findMax(l);
	int removed = 0;

	Item * prev = NULL;
	Item * item = l -> m_First;

	while (item != NULL) {

		Item * current = item;

		if (item -> m_Val >= max) {

			removeItem(l, item, prev);
			removed++;

			item = prev != NULL ? prev -> m_Next : l -> m_First;

		} else {
			item = item -> m_Next;
			prev = current;
		}
	}

	return removed;
}

int findMax (Data * l) {

	Item * item = l -> m_First;
	int max = item -> m_Val;

	while (item != NULL) {
		int val = item -> m_Val;
		if (val > max)
			max = val;

		item = item -> m_Next;
	}

	return max;
}

void removeItem(Data * l, Item * item, Item * prev) {

	if (l -> m_Last == item)
		l -> m_Last = prev;

	if (prev == NULL) {
		l -> m_First = item -> m_Next;

	} else {
		prev -> m_Next = item -> m_Next;
	}

	free(item);
}

void destroyAll  ( Data * l ) {

	Item * item = l -> m_First;

	while ( item != NULL) {
		Item * toFree = item;
		item = item->m_Next;
		free (toFree);
	}

	//free(l);
}

#ifndef __PROGTEST__

void printLinkedList( const Data * data) {
	Item * item = data->m_First;

	if (item == NULL) {
		printf("EMPTY\n");
		return;
	}

	while (item != NULL) {
		printf("%d -> ", item->m_Val);
		item = item -> m_Next;
	}

	printf("NULL\n");
}

int checkLinkedList(Data * l, int * arr, size_t size) {

	Item * item = l->m_First;

	for (size_t i = 0; i < size; i++) {
		if (item == NULL) {
			printf("To short!\n");
			return 0;
		}

		int val = item->m_Val;

		if (val != arr[i]) {
			printf("Value mismatch!\n");
			return 0;
		}

		item = item -> m_Next;
	}

	if (item->m_Next != NULL) {
		printf("To long!, %d\n", item -> m_Next -> m_Val);
		return 0;
	}

	return 1;
}

int main ( void ) {

  TDATA a;
  a.m_First = a.m_Last = NULL;

  insertEnd ( &a, 1 );
  insertEnd ( &a, 2 );
  insertEnd ( &a, 1 );
  insertEnd ( &a, 3 );
  insertEnd ( &a, 4 );
  insertEnd ( &a, 2 );
  insertEnd ( &a, 5 );
  printLinkedList(&a);

  assert ( a . m_First != NULL
           && a . m_First -> m_Val == 1
           && a . m_First -> m_Next != NULL
           && a . m_First -> m_Next -> m_Val == 2
           && a . m_First -> m_Next -> m_Next != NULL
           && a . m_First -> m_Next -> m_Next -> m_Val == 1
           && a . m_First -> m_Next -> m_Next -> m_Next != NULL
           && a . m_First -> m_Next -> m_Next -> m_Next -> m_Val == 3
           && a . m_First -> m_Next -> m_Next -> m_Next -> m_Next != NULL
           && a . m_First -> m_Next -> m_Next -> m_Next -> m_Next -> m_Val == 4
           && a . m_First -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next != NULL
           && a . m_First -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Val == 2
           && a . m_First -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next != NULL
           && a . m_First -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Val == 5
           && a . m_First -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next == NULL
           && a . m_Last == a . m_First -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next );
  assert ( removeMax ( &a ) == 1 );
  printLinkedList(&a);
  assert ( a . m_First != NULL
           && a . m_First -> m_Val == 1
           && a . m_First -> m_Next != NULL
           && a . m_First -> m_Next -> m_Val == 2
           && a . m_First -> m_Next -> m_Next != NULL
           && a . m_First -> m_Next -> m_Next -> m_Val == 1
           && a . m_First -> m_Next -> m_Next -> m_Next != NULL
           && a . m_First -> m_Next -> m_Next -> m_Next -> m_Val == 3
           && a . m_First -> m_Next -> m_Next -> m_Next -> m_Next != NULL
           && a . m_First -> m_Next -> m_Next -> m_Next -> m_Next -> m_Val == 4
           && a . m_First -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next != NULL
           && a . m_First -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Val == 2
           && a . m_First -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next == NULL
           && a . m_Last == a . m_First -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next 
		   );
  destroyAll ( &a );

  a . m_First = a . m_Last = NULL;
  insertEnd ( &a, 1 );
  insertEnd ( &a, 2 );
  insertEnd ( &a, 3 );
  insertEnd ( &a, 0 );
  insertEnd ( &a, 2 );
  insertEnd ( &a, 3 );
  insertStart ( &a, 1 );
  insertStart ( &a, 2 );
  insertStart ( &a, 3 );
  printLinkedList(&a);

  assert ( a . m_First != NULL
           && a . m_First -> m_Val == 3
           && a . m_First -> m_Next != NULL
           && a . m_First -> m_Next -> m_Val == 2
           && a . m_First -> m_Next -> m_Next != NULL
           && a . m_First -> m_Next -> m_Next -> m_Val == 1
           && a . m_First -> m_Next -> m_Next -> m_Next != NULL
           && a . m_First -> m_Next -> m_Next -> m_Next -> m_Val == 1
           && a . m_First -> m_Next -> m_Next -> m_Next -> m_Next != NULL
           && a . m_First -> m_Next -> m_Next -> m_Next -> m_Next -> m_Val == 2
           && a . m_First -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next != NULL
           && a . m_First -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Val == 3
           && a . m_First -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next != NULL
           && a . m_First -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Val == 0
           && a . m_First -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next != NULL
           && a . m_First -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Val == 2
           && a . m_First -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next != NULL
           && a . m_First -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Val == 3
           && a . m_First -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next == NULL
           && a . m_Last == a . m_First -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next );

  assert ( removeMax ( &a ) == 3 );
  printLinkedList(&a);

  assert ( a . m_First != NULL
           && a . m_First -> m_Val == 2
           && a . m_First -> m_Next != NULL
           && a . m_First -> m_Next -> m_Val == 1
           && a . m_First -> m_Next -> m_Next != NULL
           && a . m_First -> m_Next -> m_Next -> m_Val == 1
           && a . m_First -> m_Next -> m_Next -> m_Next != NULL
           && a . m_First -> m_Next -> m_Next -> m_Next -> m_Val == 2
           && a . m_First -> m_Next -> m_Next -> m_Next -> m_Next != NULL
           && a . m_First -> m_Next -> m_Next -> m_Next -> m_Next -> m_Val == 0
           && a . m_First -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next != NULL
           && a . m_First -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Val == 2
           && a . m_First -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next == NULL
           && a . m_Last == a . m_First -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next );

  assert ( removeMax ( &a ) == 3 );
  printLinkedList(&a);

  assert ( a . m_First != NULL
           && a . m_First -> m_Val == 1
           && a . m_First -> m_Next != NULL
           && a . m_First -> m_Next -> m_Val == 1
           && a . m_First -> m_Next -> m_Next != NULL
           && a . m_First -> m_Next -> m_Next -> m_Val == 0
           && a . m_First -> m_Next -> m_Next -> m_Next == NULL
           && a . m_Last == a . m_First -> m_Next -> m_Next );

  assert ( removeMax ( &a ) == 2 );
  printLinkedList(&a);

  assert ( a . m_First != NULL
           && a . m_First -> m_Val == 0
           && a . m_First -> m_Next == NULL
           && a . m_Last == a . m_First );
  destroyAll ( &a );

  a . m_First = a . m_Last = NULL;
  insertEnd ( &a, -1 );
  insertEnd ( &a, -2 );
  insertEnd ( &a, -10000 );
  insertEnd ( &a, -1 );
  insertEnd ( &a, -300 );
  assert ( removeMax ( &a ) == 2 );
  assert ( a . m_First != NULL
           && a . m_First -> m_Val == -2
           && a . m_First -> m_Next != NULL
           && a . m_First -> m_Next -> m_Val == -10000
           && a . m_First -> m_Next -> m_Next != NULL
           && a . m_First -> m_Next -> m_Next -> m_Val == -300
           && a . m_First -> m_Next -> m_Next -> m_Next == NULL
           && a . m_Last == a . m_First -> m_Next -> m_Next );
  destroyAll ( &a );

  return 0;
}
#endif /* __PROGTEST__ */
