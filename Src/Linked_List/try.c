#define TRY_LINKED_LIST		0

#if TRY_LINKED_LIST

#include "Std_Types.h"
#include <stdio.h>
#include <stdlib.h>
#include "print.h"
#include <time.h>

#include "Linked_List.h"
#include "Linked_List_Private.h"

#define INITIAL_NUMBER_OF_LINKS		10
#define MAX_DATA					1000
//#define RND_INIT					571468


b8 is1Smaller	(const s32* n1Ptr, const s32* n2Ptr);
b8 is1Larger	(const s32* n1Ptr, const s32* n2Ptr);
b8 areEqual		(const s32* n1Ptr, const s32* n2Ptr);
void copyData	(s32* distPtr, const s32* srcPtr);

void printData	(const s32* dataPtr);

void init_list(LinkedList_t* l);

int main(void) {
	/*	Init emulated random number generation	*/
	time_t tStart;
	srand(time(&tStart));

	/*	Init linked list	*/
	LinkedList_t l;
	init_list(&l);

	/*	add random data to list	*/
	for (u8 i = 0; i < INITIAL_NUMBER_OF_LINKS; i++)
	{
		s32 newData = rand() % MAX_DATA;
		LinkedList_voidAddFirst(&l, &newData);
	}

	LinkedList_voidPrintList(&l);

	LinkedList_voidSortDescending(&l);

	LinkedList_voidPrintList(&l);

	while(1);

	return 0;
}



b8 is1Smaller	(const s32* n1Ptr, const s32* n2Ptr)
{
	return (*n1Ptr < *n2Ptr);
}

b8 is1Larger	(const s32* n1Ptr, const s32* n2Ptr)
{
	return (*n1Ptr > *n2Ptr);
}

b8 areEqual		(const s32* n1Ptr, const s32* n2Ptr)
{
	return (*n1Ptr == *n2Ptr);
}

void copyData	(s32* distPtr, const s32* srcPtr)
{
	*distPtr = *srcPtr;
}

void printData	(const s32* dataPtr)
{
	PRINTF("%d", *dataPtr);
}

void init_list(LinkedList_t* l)
{
	LinkedList_voidInit(
		l,
		NULL,
		is1Smaller, is1Larger, areEqual, copyData
	);
}

#endif	/*	TRY_LINKED_LIST	*/
