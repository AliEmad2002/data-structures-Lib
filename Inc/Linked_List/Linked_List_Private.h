/*
 * Linked_List_Private.h
 *
 *  Created on: Feb 19, 2023
 *      Author: ali20
 */

#ifndef INCLUDE_DATA_STRUCTURES_LINKED_LIST_LINKED_LIST_PRIVATE_H_
#define INCLUDE_DATA_STRUCTURES_LINKED_LIST_LINKED_LIST_PRIVATE_H_


/*	checks if a list is empty	*/
#define LINKED_LIST_IS_LIST_EMPTY(listPtr)	\
	(listPtr->first == NULL)


/*	returns pointer to the last link in list	*/
LinkedList_Link_t* LinkedList_ptrGetLastLink(LinkedList_t* l);

/*
 * gets pointer to the link before last in list.
 *
 * Note:
 * 	-	If list is empty, function returns "false".
 * 	-	Otherwise, pointer to the before last link is copied to "*beforeLastPP",
 * 		and function returns "true".
 */
b8 LinkedList_b8GetBeforeLastLink(
		LinkedList_t* l, LinkedList_Link_t** beforeLastPP);

/*
 * get pointer to link of a certain index in list
 *
 * Note:
 * 	-	If index is not in range, function returns "false".
 * 	-	Otherwise, it copies link's pointer to "*linkPP" and return "true".
 */
b8 LinkedList_b8GetLinkAt(LinkedList_t* l, s32 index, LinkedList_Link_t** linkPP);

/*	prints link info on console (uses trace_printf)	*/
void LinkedList_voidPrintLink(LinkedList_Link_t* link);

/*	returns pointer to the next link in list (circularly)	*/
LinkedList_Link_t* LinkedList_ptrGetNextLinkCirc(
	LinkedList_t* l, LinkedList_Link_t* current);

/*
 * This function:
 * 	-	Starting from selected link (that is next to "prevToStart"), it searches
 * 		for the link of minimum value.
 *
 * 	-	If found, it swaps both, minimum link and starting link.
 *
 * 	-	Returns pointer to the minimum link.
 *
 * 	-	Is Used in list sorting.
 */
LinkedList_Link_t* LinkedList_ptrSwapWithMinAfter(
	LinkedList_t* l, LinkedList_Link_t* prevToStart);

/*
 * Swaps two links in list, given pointers to the links previous to these two.
 *
 * Remember: previous to "first" is taken to be "NULL"
 */
void LinkedList_voidSwapTwo(
	LinkedList_t* l, LinkedList_Link_t* prev1, LinkedList_Link_t* prev2);

#endif /* INCLUDE_DATA_STRUCTURES_LINKED_LIST_LINKED_LIST_PRIVATE_H_ */
