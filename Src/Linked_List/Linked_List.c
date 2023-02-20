/*
 * Linked_List.c
 *
 *  Created on: Feb 19, 2023
 *      Author: ali20
 */

/*	LIB	*/
#include "Std_Types.h"
#include <stdlib.h>
#include "diag/trace.h"

/*	SELF	*/
#include "Linked_List_Config.h"
#include "Linked_List.h"
#include "Linked_List_Private.h"

/******************************************************************************
 * List initializing:
 *****************************************************************************/
void LinkedList_voidInit(
	LinkedList_t* l,
	LinkedList_Link_t* first,
	b8 (*is1Smaller)	(const LinkedList_Data_t*, const LinkedList_Data_t*),
	b8 (*is1Larger)		(const LinkedList_Data_t*, const LinkedList_Data_t*),
	b8 (*areEqual)		(const LinkedList_Data_t*, const LinkedList_Data_t*),
	void (*copyData) 	(LinkedList_Data_t*, const LinkedList_Data_t*)
)
{
	l->first = first;

	l->is1Smaller = is1Smaller;

	l->is1Larger = is1Larger;

	l->areEqual = areEqual;

	l->copyData = copyData;
}

/******************************************************************************
 * List printing (uses trace_printf (for STM32 MCU's)):
 *****************************************************************************/
void LinkedList_voidPrintList(LinkedList_t* l)
{
	trace_printf("Printing linkedList @ %u:\n", (u32)l);

	LinkedList_Link_t* current = l->first;

	while(current != NULL)
	{
		LinkedList_voidPrintLink(current);

		current = current->next;
	}
}

/******************************************************************************
 * Data adding:
 *****************************************************************************/
void LinkedList_voidAddLast(LinkedList_t* l, LinkedList_Data_t* newDataPtr)
{
	/*	allocate new link in memory	*/
	LinkedList_Link_t* newLink = malloc(sizeof(LinkedList_Link_t));

	/*	copy new data to the new link	*/
	l->copyData(&newLink->data, newDataPtr);

	/*	as it will be added at the end of the list, its next is NULL	*/
	newLink->next = NULL;

	/*	if list is empty, new link is the first	*/
	if (LINKED_LIST_IS_LIST_EMPTY(l))
	{
		l->first = newLink;
	}

	/*	Otherwise:	*/
	else
	{
		/*	get pointer to the last link in the list	*/
		LinkedList_Link_t* lastLink = LinkedList_ptrGetLastLink(l);

		/*	next of the last link, is now the new link	*/
		lastLink->next = newLink;
	}
}

void LinkedList_voidAddFirst(LinkedList_t* l, LinkedList_Data_t* newDataPtr)
{
	/*	allocate new link in memory	*/
	LinkedList_Link_t* newLink = malloc(sizeof(LinkedList_Link_t));

	/*	copy new data to the new link	*/
	l->copyData(&newLink->data, newDataPtr);

	/*	as it is going to be the first, its next is now the previous first	*/
	newLink->next = l->first;

	/*	make it first	*/
	l->first = newLink;
}

b8 LinkedList_b8AddAt(LinkedList_t* l, s32 i, LinkedList_Data_t* newDataPtr)
{
	/*	if first of list (special case):	*/
	if (i == 0)
	{
		LinkedList_voidAddFirst(l, newDataPtr);
		return true;
	}

	/*	otherwise, get pointer to the link of index = i - 1	*/
	LinkedList_Link_t* iPrevLink;
	b8 isIndexValid = LinkedList_b8GetLinkAt(l, i - 1, &iPrevLink);

	/*	if index is not in range	*/
	if (!isIndexValid)
		return false;

	/*	otherwise, allocate new link in memory	*/
	LinkedList_Link_t* newLink = malloc(sizeof(LinkedList_Link_t));

	/*	copy new data to the new link	*/
	l->copyData(&newLink->data, newDataPtr);

	/*	new link's next is link[i]	*/
	newLink->next = iPrevLink->next;

	/*	next of the previous to i, is now the new link	*/
	iPrevLink->next = newLink;

	return true;
}

/******************************************************************************
 * Data deleting:
 *****************************************************************************/
void LinkedList_voidDeleteLast(LinkedList_t* l)
{
	/*	get pointer to the before last link	*/
	LinkedList_Link_t* beforeLastLink;
	u8 status = LinkedList_b8GetBeforeLastLink(l, &beforeLastLink);

	/*	if list was empty, no deletion needed	*/
	if (status == false)
		return;

	/*	otherwise	*/
	/*	if list was of one link only (special case)	*/
	if (beforeLastLink == NULL)
	{
		/*	free list's only link	*/
		free(l->first);
		l->first = NULL;
	}

	/*	otherwise	*/
	else
	{
		/*	free allocated memory of the last link	*/
		free(beforeLastLink->next);

		/*	next of the before last link is now NULL	*/
		beforeLastLink->next = NULL;
	}
}

void LinkedList_voidDeleteFirst(LinkedList_t* l)
{
	/*	if list was empty, no deletion needed	*/
	if (l->first == NULL)
		return;

	/*	otherwise	*/
	/*	Temporarily store pointer to the first link	*/
	LinkedList_Link_t* firstTemp = l->first;

	/*	first of the list is now previously first's next	*/
	l->first = (l->first)->next;

	/*	free allocated memory of the previously first link	*/
	free(firstTemp);
}

b8 LinkedList_b8DeleteFrom(LinkedList_t* l, s32 i);

/******************************************************************************
 * Data getting:
 *****************************************************************************/
b8 LinkedList_b8GetAt(LinkedList_t* l, u32 index, LinkedList_Data_t** iPP)
{
	u32 i = 0;
	LinkedList_Link_t* current = l->first;

	while(1)
	{
		if (current == NULL)
			return false;

		if (i == index)
		{
			*iPP = &(current->data);
			return true;
		}

		i++;
		current = current->next;
	}
}

b8 LinkedList_b8GetMin(LinkedList_t* l, LinkedList_Data_t** minPP)
{
	/*	check empty list	*/
	if (LINKED_LIST_IS_LIST_EMPTY(l))
		return false;

	/*	min is initially assumed to be first of the list	*/
	*minPP = &((l->first)->data);

	for (
		LinkedList_Link_t* current = (l->first)->next;
		current != NULL;
		current = current->next
	)
	{
		if (l->is1Smaller(&current->data, *minPP))
		{
			*minPP = &(current->data);
		}
	}

	return true;
}

b8 LinkedList_b8GetMax(LinkedList_t* l, LinkedList_Data_t** maxPP)
{
	/*	check empty list	*/
	if (LINKED_LIST_IS_LIST_EMPTY(l))
		return false;

	/*	max is initially assumed to be first of the list	*/
	*maxPP = &((l->first)->data);

	for (
		LinkedList_Link_t* current = (l->first)->next;
		current != NULL;
		current = current->next
	)
	{
		if (l->is1Larger(&current->data, *maxPP))
		{
			*maxPP = &(current->data);
		}
	}

	return true;
}

b8 LinkedList_b8Search(LinkedList_t* l, LinkedList_Data_t* data, s32* i)
{
	LinkedList_Link_t* current = l->first;

	*i = 0;

	while(1)
	{
		/*	if current is end of the list and data is not yet found	*/
		if (current == NULL)
			return false;

		/*	Otherwise	*/
		/*	check current's data	*/
		if (l->areEqual(&current->data, data))
		{
			return true;
		}

		/*	if data is not yet found	*/
		(*i)++;
		current = current->next;
	}
}

/******************************************************************************
 * List sorting:
 *****************************************************************************/
void LinkedList_voidSortAscending(LinkedList_t* l)
{
	/**
	 * Explaining used algorithm:
	 *
	 * 	-	Starting from first of the list, search for the link of minimum
	 * 		data, and swap it with "first".
	 *
	 * 	-	Pass again on the list, this time form the 2nd link, searching for
	 * 		link of minimum data, and swap them with each other.
	 *
	 * 	-	Loop, following the previously mentioned pattern, till the first
	 * 		link in the pass is now the last link, then, sorting would've been
	 * 		done.
	 **/

	/*
	 * Since:	"firstInPass"		= "l->first"
	 * Then:	"prevToFirstInPass"	= "NULL"
	 * (Remember: "NULL" is used in referring to the link previous to "first")
	 */
	LinkedList_Link_t* prevToFirstInPass = NULL;

	while(1)
	{
		prevToFirstInPass =
			LinkedList_ptrSwapWithMinAfter(l, prevToFirstInPass);

		if (prevToFirstInPass == NULL)
			break;
	}
}

void LinkedList_voidSortDescending(LinkedList_t* l);







