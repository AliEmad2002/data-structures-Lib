/*
 * Linked_List.h
 *
 *  Created on: Feb 19, 2023
 *      Author: Ali Emad
 *
 * Goal of this structure is to give user flexibility of creating, manipulating
 * data lists, all dynamically.
 */

#ifndef INC_LINKED_LIST_LINKED_LIST_H_
#define INC_LINKED_LIST_LINKED_LIST_H_

#include "Linked_List_Config.h"

/******************************************************************************
 * Link:
 ******************************************************************************/
typedef struct{
	/*	Data of the link	*/
	LinkedList_Data_t data;

	/*	Pointer to next link in list	*/
	void* next;
}LinkedList_Link_t;

/******************************************************************************
 * Linked list (i.e.: list of links):
 ******************************************************************************/
typedef struct{
	/*	Pointer to first link in list	*/
	LinkedList_Link_t* first;

	/*
	 * Pointer to a user defined function that:
	 * 	- 	Takes two pointers to two objects of type
	 * 		"LinkedList_Data_t" that is user-configured in "Linked_List_Config.h"
	 * 	-	Returns b8 value (boolean). That is the comparison result between
	 * 		the two data objects previously mentioned.
	 *
	 * For the sake of convenience, this function return "true" when first object
	 * is smaller than second object. Whatever "smaller" may mean, it depends
	 * on nature of the link data type, which is user defined.
	 *
	 * For example: if the "LinkedList_Data_t" is "int", this function would be:
	 * b8 funcName(int* n1, int* n2)
	 * {
	 * 		return (*n1 < *n2) ? true : false;
	 * }
	 */
	b8 (*is1Smaller) (const LinkedList_Data_t* d1Ptr, const LinkedList_Data_t* d2Ptr);

	/*
	 * Like the previous function (read its comment), this function returns
	 * "true" if first object is larger that the second. Whatever "larger" may
	 * mean.
	 */
	b8 (*is1Larger) (const LinkedList_Data_t* d1Ptr, const LinkedList_Data_t* d2Ptr);

	/*
	 * Like the previous two functions (read comment of "is1Smaller"), this
	 * function returns true if first object is equal to the second. Whatever
	 * "equal" may mean.
	 */
	b8 (*areEqual) (const LinkedList_Data_t* d1Ptr, const LinkedList_Data_t* d2Ptr);

	/*
	 * pointer to a user defined function that copies data object from inside
	 * a pointer to the inside of another.
	 */
	void (*copyData) (LinkedList_Data_t* distPtr, const LinkedList_Data_t* srcPtr);
}LinkedList_t;

/**
 * Note: To avoid mis-using the following functions, please read the
 * "LinkedList_t" comments clearly first.
 **/

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
);

/******************************************************************************
 * List printing (uses trace_printf (for STM32 MCU's)):
 *****************************************************************************/
void LinkedList_voidPrintList(LinkedList_t* l);										//	checked

/******************************************************************************
 * Data adding:
 *****************************************************************************/
/*	adds data to end of the list. (makes copy of "newDataPtr")	*/
void LinkedList_voidAddLast(LinkedList_t* l, LinkedList_Data_t* newDataPtr);		//	checked

/*	adds data at the beginning of the list. (makes copy of "newDataPtr")	*/
void LinkedList_voidAddFirst(LinkedList_t* l, LinkedList_Data_t* newDataPtr);		//	checked

/*
 * adds data at selected index (if in range). (makes copy of "newDataPtr")
 *
 * Note:
 * 	-	Returns "true" if 'i' is in range and data was added.
 * 	-	Returns "false" otherwise.
 */
b8 LinkedList_b8AddAt(LinkedList_t* l, s32 i, LinkedList_Data_t* newDataPtr);		//	checked

/******************************************************************************
 * Data deleting:
 *****************************************************************************/
/*	deletes data form end of the list. (frees allocated memory)	*/
void LinkedList_voidDeleteLast(LinkedList_t* l);									//	checked

/*	deletes data form the beginning of the list. (frees allocated memory)	*/
void LinkedList_voidDeleteFirst(LinkedList_t* l);									//	checked

/*
 * deletes data form selected index (if in range). (frees allocated memory)
 *
 * Note:
 * 	-	Returns "true" if 'i' is in range and data was deleted.
 * 	-	Returns "false" otherwise.
 */
b8 LinkedList_b8DeleteFrom(LinkedList_t* l, s32 i);

/******************************************************************************
 * Data getting:
 *****************************************************************************/
/*
 * Gets pointer to data object of certain index in the linked list.
 *
 * Function returns "true" if 'i' is valid (i.e.: 'i'th link already exists).
 * Otherwise, it returns "false", and value of 'lPP' is not guaranteed.
 *
 * 'iPP' is a pointer passed by reference (i.e.: pointer to pointer).
 */
b8 LinkedList_b8GetAt(LinkedList_t* l, u32 index, LinkedList_Data_t** iPP);			//	checked

/*
 * Gets pointer to data object that is of minimum value in the linked list.
 *
 * Note: if list is empty, "false" is returned. Otherwise, "true".
 *
 * 'minPP' is a pointer passed by reference (i.e.: pointer to pointer).
 */
b8 LinkedList_b8GetMin(LinkedList_t* l, LinkedList_Data_t** minPP);					//	checked

/*
 * Gets pointer to data object that is of maximum value in the linked list.
 *
 * Note: if list is empty, "false" is returned. Otherwise, "true".
 *
 * 'maxPP' is a pointer passed by reference (i.e.: pointer to pointer).
 */
b8 LinkedList_b8GetMax(LinkedList_t* l, LinkedList_Data_t** maxPP);					//	checked

/*
 * Searches for data in list (first match).
 *
 * Notes:
 * 	-	If data was found in list, index of data is copied to 'i' and "true"
 * 		is returned.
 *
 * 	-	Otherwise, "false" is returned.
 */
b8 LinkedList_b8Search(LinkedList_t* l, LinkedList_Data_t* data, s32* i);			//	checked

/******************************************************************************
 * List sorting:
 *****************************************************************************/
/*	sorts the linked list in an ascending order	*/

/*	sorts the linked list in a descending order	*/

#endif /* INC_LINKED_LIST_LINKED_LIST_H_ */










