/*
 * Queue_Private.h
 *
 *  Created on: Feb 26, 2023
 *      Author: ali20
 */

#ifndef INC_DATA_STRUCTURES_QUEUE_QUEUE_PRIVATE_H_
#define INC_DATA_STRUCTURES_QUEUE_QUEUE_PRIVATE_H_

#if ENABLE_QUEUE

/*******************************************************************************
 * Index manipulation:
 ******************************************************************************/
void Queue_voidIncrementTailIndex(Queue_t* q);

void Queue_voidIncrementHeadIndex(Queue_t* q);

#endif	/*	ENABLE_QUEUE	*/

#endif /* INC_DATA_STRUCTURES_QUEUE_QUEUE_PRIVATE_H_ */
