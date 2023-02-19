/*
 * Linked_List_Private.c
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

void LinkedList_voidPrintLink(LinkedList_Link_t* link)
{
	/*	print link's data	*/
	LINKED_LIST_PRINT_DATA(&link->data);

	/*	print link's next	*/
	trace_printf(", %u", (u32)link->next);

	/*	print link's address	*/
	trace_printf(" @ %u\n", (u32)link);
}
