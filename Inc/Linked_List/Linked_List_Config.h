/*
 * Linked_List_Config.h
 *
 *  Created on: Feb 19, 2023
 *      Author: ali20
 */

#ifndef INC_LINKED_LIST_LINKED_LIST_CONFIG_H_
#define INC_LINKED_LIST_LINKED_LIST_CONFIG_H_


/*
 * type of the data that is to be listed in the linked list.
 */
#define LINKED_LIST_DATA_TYPE		s32

typedef LINKED_LIST_DATA_TYPE	LinkedList_Data_t;

/*
 * pointer to a function that takes pointer to data object and prints info of it.
 * (could be externed)
 */
extern void printData	(const s32* dataPtr);

#define LINKED_LIST_PRINT_DATA		printData

#endif /* INC_LINKED_LIST_LINKED_LIST_CONFIG_H_ */
