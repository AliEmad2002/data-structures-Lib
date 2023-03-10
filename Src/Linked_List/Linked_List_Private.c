/*
 * Linked_List_Private.c
 *
 *  Created on: Feb 19, 2023
 *      Author: ali20
 */

/*	LIB	*/
#include "Std_Types.h"
#include <stdlib.h>
#include "print.h"

/*	SELF	*/
#include "Linked_List_Config.h"
#include "Linked_List.h"
#include "Linked_List_Private.h"


LinkedList_Link_t* LinkedList_ptrGetLastLink(LinkedList_t* l)
{
	/*	if list is empty, return NULL	*/
	if (LINKED_LIST_IS_LIST_EMPTY(l))
		return NULL;

	/*	otherwise, trace the list from first to last	*/
	LinkedList_Link_t* current = l->first;

	while(1)
	{
		if (current->next == NULL)
			return current;

		current = current->next;
	}
}

b8 LinkedList_b8GetBeforeLastLink(
	LinkedList_t* l, LinkedList_Link_t** beforeLastPP)
{
	/*	if list is empty, return false	*/
	if (LINKED_LIST_IS_LIST_EMPTY(l))
		return false;

	/*	otherwise, trace the list from first to before last	*/
	LinkedList_Link_t* current = l->first;

	/*	pointer to before first is virtually assumed to be NULL	*/
	LinkedList_Link_t* prevToCurrent = NULL;

	while(1)
	{
		if (current->next == NULL)
		{
			*beforeLastPP = prevToCurrent;
			return true;
		}

		prevToCurrent = current;
		current = current->next;
	}
}

b8 LinkedList_b8GetLinkAt(LinkedList_t* l, s32 index, LinkedList_Link_t** linkPP)
{
	s32 i = 0;
	LinkedList_Link_t* current = l->first;

	while(1)
	{
		if (current == NULL)
			return false;

		if (i == index)
		{
			*linkPP = current;
			return true;
		}

		i++;
		current = current->next;
	}
}

/*
 * Gets address of 'i'th link "next" variable.
 * (That is an address of a pointer ==> pointer to pointer, And therefore to
 * be passed by reference, linkPPP is used).
 *
 * 'index' could be -1. Therefore result is address of list's variable "first".
 *
 * returns "true" if 'index' is valid, "false" otherwise.
 */
b8 LinkedList_b8GetPointerToNextOf(
	LinkedList_t* l, s32 index, LinkedList_Link_t*** linkPPP)
{
	/*
	 * Pointer to the "next" variable of the 'i'th link.
	 * Initially, point at list's first.
	 */
	LinkedList_Link_t** nextToIPtr = &(l->first);

	/*	counter that is to be compared with 'index'	*/
	s32 i = 0;

	/*	while 'i'th link is not the end of the list	*/
	while(*nextToIPtr != NULL)
	{
		/*	if 'i' reaches 'index' - 1, then 'i'th link is found	*/
		if (i > index)
		{
			*linkPPP = nextToIPtr;
			return true;
		}

		/*	otherwise, look at the next link	*/
		else
		{
			nextToIPtr = (LinkedList_Link_t**)&((*nextToIPtr)->next);
			i++;
		}
	}

	/*
	 * If the previous loop ends without a return, the 'index'th link was not
	 * found.
	 */
	return false;
}

void LinkedList_voidPrintLink(LinkedList_Link_t* link)
{
	/*	print link's data	*/
	LINKED_LIST_PRINT_DATA(&link->data);

	/*	print link's next	*/
	PRINTF(", %u", (u32)link->next);

	/*	print link's address	*/
	PRINTF(" @ %u\n", (u32)link);
}

LinkedList_Link_t* LinkedList_ptrGetNextLinkCirc(
	LinkedList_t* l, LinkedList_Link_t* current)
{
	/*	as "NULL" is taken as previous to "first"	*/
	if (current == NULL)
		return l->first;

	else
		return current->next;
}

LinkedList_Link_t* LinkedList_ptrSwapWithMinAfter(
	LinkedList_t* l, LinkedList_Link_t* prevToStart)
{
	/**
	 * Assume virtual pointers "current" and "min", which point to the current
	 * link and minimum link (link of minimum data).
	 *
	 * As the nature of swapping requires pointers to previous link to each of
	 * the two, "prevTo..." is used in addition.
	 **/

	/**	get pointer to the starting link.	**/
	LinkedList_Link_t* start = LinkedList_ptrGetNextLinkCirc(l, prevToStart);

	/*	if starting link is the terminator, return	*/
	if (start == NULL)
		return NULL;

	/**	initially, minimum is the starting	**/
	LinkedList_Link_t* min			= start;
	LinkedList_Link_t* prevToMin	= prevToStart;

	/**
	 * "current" is pointer to the link being currently (in iteration) compared
	 * with "min". This starts from the link next to starting link.
	 **/
	LinkedList_Link_t* current			= start->next;
	LinkedList_Link_t* prevToCurrent	= start;

	/**	search	**/

	/*	while "current" is not the terminator	*/
	while(current != NULL)
	{
		/*	if "current"'s data is smaller than that of "min"'s	*/
		if (l->is1Smaller(&(current->data), &(min->data)))
		{
			/*	update "min" with "current"	*/
			min = current;
			prevToMin = prevToCurrent;
		}

		/*	update "current" with "current->next"	*/
		prevToCurrent = current;
		current = current->next;
	}

	/**	Having now found "min", swap it with "start".	**/
	LinkedList_voidSwapTwo(l, prevToMin, prevToStart);

	/**	Return pointer to the search result's link 	**/
	return min;
}

LinkedList_Link_t* LinkedList_ptrSwapWithMaxAfter(
	LinkedList_t* l, LinkedList_Link_t* prevToStart)
{
	/**
	 * Assume virtual pointers "current" and "max", which point to the current
	 * link and maximum link (link of maximum data).
	 *
	 * As the nature of swapping requires pointers to previous link to each of
	 * the two, "prevTo..." is used in addition.
	 **/

	/**	get pointer to the starting link.	**/
	LinkedList_Link_t* start = LinkedList_ptrGetNextLinkCirc(l, prevToStart);

	/*	if starting link is the terminator, return	*/
	if (start == NULL)
		return NULL;

	/**	initially, maximum is the starting	**/
	LinkedList_Link_t* max			= start;
	LinkedList_Link_t* prevToMax	= prevToStart;

	/**
	 * "current" is pointer to the link being currently (in iteration) compared
	 * with "max". This starts from the link next to starting link.
	 **/
	LinkedList_Link_t* current			= start->next;
	LinkedList_Link_t* prevToCurrent	= start;

	/**	search	**/

	/*	while "current" is not the terminator	*/
	while(current != NULL)
	{
		/*	if "current"'s data is smaller than that of "min"'s	*/
		if (l->is1Larger(&(current->data), &(max->data)))
		{
			/*	update "min" with "current"	*/
			max = current;
			prevToMax = prevToCurrent;
		}

		/*	update "current" with "current->next"	*/
		prevToCurrent = current;
		current = current->next;
	}

	/**	Having now found "min", swap it with "start".	**/
	LinkedList_voidSwapTwo(l, prevToMax, prevToStart);

	/**	Return pointer to the search result's link 	**/
	return max;
}

void LinkedList_voidSwapTwo(
	LinkedList_t* l, LinkedList_Link_t* prev1, LinkedList_Link_t* prev2)
{
	/**	Extract pointers to the actual links to be swapped	**/
	LinkedList_Link_t* link1 = LinkedList_ptrGetNextLinkCirc(l, prev1);
	LinkedList_Link_t* link2 = LinkedList_ptrGetNextLinkCirc(l, prev2);

	/**	Make "prev1->next" = "link2"	**/
	if (prev1 == NULL)
	{
		/*	"prev1->next" is "l->first"	*/
		l->first = link2;
	}
	else
	{
		prev1->next = link2;
	}

	/**	Make "prev2->next" = "link1"	**/
	if (prev2 == NULL)
	{
		/*	"prev2->next" is "l->first"	*/
		l->first = link1;
	}
	else
	{
		prev2->next = link1;
	}

	/**	Temporarily store "link1->next". To be used later	**/
	LinkedList_Link_t* link1Next = link1->next;

	/**
	 * Make "link1->next" = "link2->next".
	 * This has one special case, if "link1" is the "link2->next".
	 **/
	if (link1 == link2->next)
	{
		link1->next = link2;
	}
	else
	{
		link1->next = link2->next;
	}

	/**
	 * Make "link2->next" = "link1Next".
	 * This has one special case, if "link2" is the "link1Next".
	 **/
	if (link2 == link1Next)
	{
		link2->next = link1;
	}
	else
	{
		link2->next = link1Next;
	}
}


















