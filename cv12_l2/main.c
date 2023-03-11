#ifndef __PROGTEST__
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef struct TItem {
  struct TItem * m_Next;
  struct TItem * m_Prev;
  int m_Val;
} TITEM;

typedef struct TData {
  TITEM * m_First;
  TITEM * m_Last;
} TDATA;

#endif /* __PROGTEST__ */

typedef TDATA Data;
typedef TITEM Item;

Item * createItem( int x );
void removeItem(Data * l, Item * item);
int findMax( Data * l);

void insertStart ( Data * l, int x ) {

	Item * newItem = createItem(x);

	if (l -> m_First == NULL) {

		l -> m_First = newItem;
		l -> m_Last = newItem;

	} else {

		newItem -> m_Next = l -> m_First;
		newItem -> m_Next -> m_Prev = newItem;
		l -> m_First = newItem;
	}
}

void insertEnd   ( Data * l, int x ) {

	Item * newItem = createItem(x);

	if (l -> m_Last == NULL) {

		l -> m_First = newItem;
		l -> m_Last = newItem;

	} else {

		newItem -> m_Prev = l -> m_Last;
		newItem -> m_Prev -> m_Next = newItem;
		l -> m_Last = newItem;
	}
}

Item * createItem( int x ) {
	Item * item = (Item *) malloc(sizeof (*item));
	item -> m_Val = x;
	item -> m_Next = item -> m_Prev = NULL;
	return item;
}

int  removeMax   ( Data * l ) {

	if (l -> m_First == NULL)
		return 0;

	int removed = 0;
	int max = findMax(l);
	Item * item = l -> m_First;

	while (item != NULL) {
		Item * next = item -> m_Next;

		if (item -> m_Val == max) {
			removeItem(l, item);
			removed++;
		}
		item = next;
	}
	return removed;
}

void removeItem(Data * l, Item * item) {

	if (item -> m_Prev == NULL) {
		l -> m_First = item -> m_Next;
	} else {
		item -> m_Prev -> m_Next = item -> m_Next;
	}

	if (item -> m_Next == NULL) {
		l -> m_Last = item -> m_Prev;
	} else {
		item -> m_Next -> m_Prev = item -> m_Prev;
	}

	free(item);
}

int findMax( Data * l) {

	Item * item = l -> m_First;
	int max = item -> m_Val;
	item = item -> m_Next;

	while (item != NULL) {
		if (item -> m_Val > max)
			max = item -> m_Val;

		item = item -> m_Next;
	}
	return max;
}

void destroyAll  ( Data * l ) {
	Item * item = l -> m_First;

	while (item != NULL) {
		Item * toRemove = item;
		item = item -> m_Next;
		free(toRemove);
	}
	l -> m_First = l -> m_Last = NULL;
}

#ifndef __PROGTEST__

void printLinkedList(Data * l) {

	Item * item = l -> m_First;

	while (item != NULL) {
		printf("%d -> ", item -> m_Val);
		item = item -> m_Next;
	}

	printf("NULL\n");
}

int main ( void ) {

  TDATA a;
  a . m_First = a . m_Last = NULL;

  insertEnd ( &a, 1 );
  insertEnd ( &a, 2 );
  insertEnd ( &a, 1 );
  insertEnd ( &a, 3 );
  insertEnd ( &a, 4 );
  insertEnd ( &a, 2 );
  insertEnd ( &a, 5 );

  printf("Added\n");
  printLinkedList(&a);

  assert ( a . m_First != NULL
           && a . m_First -> m_Val == 1
           && a . m_First -> m_Next != NULL
           && a . m_First -> m_Prev == NULL
           && a . m_First -> m_Next -> m_Val == 2
           && a . m_First -> m_Next -> m_Next != NULL
           && a . m_First -> m_Next -> m_Prev == a . m_First
           && a . m_First -> m_Next -> m_Next -> m_Val == 1
           && a . m_First -> m_Next -> m_Next -> m_Next != NULL
           && a . m_First -> m_Next -> m_Next -> m_Prev == a . m_First -> m_Next
           && a . m_First -> m_Next -> m_Next -> m_Next -> m_Val == 3
           && a . m_First -> m_Next -> m_Next -> m_Next -> m_Next != NULL
           && a . m_First -> m_Next -> m_Next -> m_Next -> m_Prev == a . m_First -> m_Next -> m_Next
           && a . m_First -> m_Next -> m_Next -> m_Next -> m_Next -> m_Val == 4
           && a . m_First -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next != NULL
           && a . m_First -> m_Next -> m_Next -> m_Next -> m_Next -> m_Prev == a . m_First -> m_Next -> m_Next -> m_Next
           && a . m_First -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Val == 2
           && a . m_First -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next != NULL
           && a . m_First -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Prev == a . m_First -> m_Next -> m_Next -> m_Next -> m_Next
           && a . m_First -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Val == 5
           && a . m_First -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next == NULL
           && a . m_First -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Prev == a . m_First -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next
           && a . m_Last == a . m_First -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next );

  assert ( removeMax ( &a ) == 1 );

  printf("Removed\n");
  printLinkedList(&a);

  assert ( a . m_First != NULL
           && a . m_First -> m_Val == 1
           && a . m_First -> m_Next != NULL
           && a . m_First -> m_Prev == NULL
           && a . m_First -> m_Next -> m_Val == 2
           && a . m_First -> m_Next -> m_Next != NULL
           && a . m_First -> m_Next -> m_Prev == a . m_First
           && a . m_First -> m_Next -> m_Next -> m_Val == 1
           && a . m_First -> m_Next -> m_Next -> m_Next != NULL
           && a . m_First -> m_Next -> m_Next -> m_Prev == a . m_First -> m_Next
           && a . m_First -> m_Next -> m_Next -> m_Next -> m_Val == 3
           && a . m_First -> m_Next -> m_Next -> m_Next -> m_Next != NULL
           && a . m_First -> m_Next -> m_Next -> m_Next -> m_Prev == a . m_First -> m_Next -> m_Next
           && a . m_First -> m_Next -> m_Next -> m_Next -> m_Next -> m_Val == 4
           && a . m_First -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next != NULL
           && a . m_First -> m_Next -> m_Next -> m_Next -> m_Next -> m_Prev == a . m_First -> m_Next -> m_Next -> m_Next
           && a . m_First -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Val == 2
           && a . m_First -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next == NULL
           && a . m_First -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Prev == a . m_First -> m_Next -> m_Next -> m_Next -> m_Next
           && a . m_Last == a . m_First -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next );

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

  printf("Added\n");
  printLinkedList(&a);

  assert ( a . m_First != NULL
           && a . m_First -> m_Val == 3
           && a . m_First -> m_Next != NULL
           && a . m_First -> m_Prev == NULL
           && a . m_First -> m_Next -> m_Val == 2
           && a . m_First -> m_Next -> m_Next != NULL
           && a . m_First -> m_Next -> m_Prev == a . m_First
           && a . m_First -> m_Next -> m_Next -> m_Val == 1
           && a . m_First -> m_Next -> m_Next -> m_Next != NULL
           && a . m_First -> m_Next -> m_Next -> m_Prev == a . m_First -> m_Next
           && a . m_First -> m_Next -> m_Next -> m_Next -> m_Val == 1
           && a . m_First -> m_Next -> m_Next -> m_Next -> m_Next != NULL
           && a . m_First -> m_Next -> m_Next -> m_Next -> m_Prev == a . m_First -> m_Next -> m_Next
           && a . m_First -> m_Next -> m_Next -> m_Next -> m_Next -> m_Val == 2
           && a . m_First -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next != NULL
           && a . m_First -> m_Next -> m_Next -> m_Next -> m_Next -> m_Prev == a . m_First -> m_Next -> m_Next -> m_Next
           && a . m_First -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Val == 3
           && a . m_First -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next != NULL
           && a . m_First -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Prev == a . m_First -> m_Next -> m_Next -> m_Next -> m_Next
           && a . m_First -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Val == 0
           && a . m_First -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next != NULL
           && a . m_First -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Prev == a . m_First -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next
           && a . m_First -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Val == 2
           && a . m_First -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next != NULL
           && a . m_First -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Prev == a . m_First -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next
           && a . m_First -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Val == 3
           && a . m_First -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next == NULL
           && a . m_First -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Prev == a . m_First -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next
           && a . m_Last == a . m_First -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next );

  assert ( removeMax ( &a ) == 3 );

  printf("Removed\n");
  printLinkedList(&a);

  assert ( a . m_First != NULL
           && a . m_First -> m_Val == 2
           && a . m_First -> m_Next != NULL
           && a . m_First -> m_Prev == NULL
           && a . m_First -> m_Next -> m_Val == 1
           && a . m_First -> m_Next -> m_Next != NULL
           && a . m_First -> m_Next -> m_Prev == a . m_First
           && a . m_First -> m_Next -> m_Next -> m_Val == 1
           && a . m_First -> m_Next -> m_Next -> m_Next != NULL
           && a . m_First -> m_Next -> m_Next -> m_Prev == a . m_First -> m_Next
           && a . m_First -> m_Next -> m_Next -> m_Next -> m_Val == 2
           && a . m_First -> m_Next -> m_Next -> m_Next -> m_Next != NULL
           && a . m_First -> m_Next -> m_Next -> m_Next -> m_Prev == a . m_First -> m_Next -> m_Next
           && a . m_First -> m_Next -> m_Next -> m_Next -> m_Next -> m_Val == 0
           && a . m_First -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next != NULL
           && a . m_First -> m_Next -> m_Next -> m_Next -> m_Next -> m_Prev == a . m_First -> m_Next -> m_Next -> m_Next
           && a . m_First -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Val == 2
           && a . m_First -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next == NULL
           && a . m_First -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Prev == a . m_First -> m_Next -> m_Next -> m_Next -> m_Next
           && a . m_Last == a . m_First -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next );
  assert ( removeMax ( &a ) == 3 );
  assert ( a . m_First != NULL
           && a . m_First -> m_Val == 1
           && a . m_First -> m_Next != NULL
           && a . m_First -> m_Prev == NULL
           && a . m_First -> m_Next -> m_Val == 1
           && a . m_First -> m_Next -> m_Next != NULL
           && a . m_First -> m_Next -> m_Prev == a . m_First
           && a . m_First -> m_Next -> m_Next -> m_Val == 0
           && a . m_First -> m_Next -> m_Next -> m_Next == NULL
           && a . m_First -> m_Next -> m_Next -> m_Prev == a . m_First -> m_Next
           && a . m_Last == a . m_First -> m_Next -> m_Next );

  assert ( removeMax ( &a ) == 2 );

  printf("Removed\n");
  printLinkedList(&a);

  assert ( a . m_First != NULL
           && a . m_First -> m_Val == 0
           && a . m_First -> m_Next == NULL
           && a . m_First -> m_Prev == NULL
           && a . m_Last == a . m_First );

  destroyAll ( &a );

  a . m_First = a . m_Last = NULL;

  insertEnd ( &a, -1 );
  insertEnd ( &a, -2 );
  insertEnd ( &a, -10000 );
  insertEnd ( &a, -1 );
  insertEnd ( &a, -300 );
  
  printf("Added\n");
  printLinkedList(&a);

  assert ( removeMax ( &a ) == 2 );

  printf("Removed\n");
  printLinkedList(&a);

  assert ( a . m_First != NULL
           && a . m_First -> m_Val == -2
           && a . m_First -> m_Next != NULL
           && a . m_First -> m_Prev == NULL
           && a . m_First -> m_Next -> m_Val == -10000
           && a . m_First -> m_Next -> m_Next != NULL
           && a . m_First -> m_Next -> m_Prev == a . m_First
           && a . m_First -> m_Next -> m_Next -> m_Val == -300
           && a . m_First -> m_Next -> m_Next -> m_Next == NULL
           && a . m_First -> m_Next -> m_Next -> m_Prev == a . m_First -> m_Next
           && a . m_Last == a . m_First -> m_Next -> m_Next );

  destroyAll ( &a );

  return 0;
}
#endif /* __PROGTEST__ */
