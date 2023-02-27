/*
 * try.c
 *
 *  Created on: Feb 26, 2023
 *      Author: ali20
 */

#define TRY_QUEUE			0

#if TRY_QUEUE

#include "Std_Types.h"
#include "Bit_Math.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "Print.h"

#include "Queue_Interface.h"

void copyData (s32** distPP, const s32* srcPtr);

void deleteData (s32* dPtr);

void printData (s32* dPtr);

#define INITIAL_NUMBER_OF_DATA				5
#define MAX_DATA							1000

int main (void)
{
	PRINTF("Program started\n");
	/*	Init emulated random number generation	*/
	time_t tStart;
	srand(time(&tStart));

	/*	init queue object	*/
	Queue_t q;
	Queue_voidInit(&q);

	/*	Push random data to queue	*/
	for (u32 i = 0; i < INITIAL_NUMBER_OF_DATA; i++)
	{
		s32 data = rand() % MAX_DATA;
		b8 pushSuccess = Queue_b8Push(&q, &data);

		PRINTF("%u: Pushed: %d\n", i, data);

		if (!pushSuccess)
		{
			PRINTF("Stack full!\n");
			while(1);
		}
	}

	s32 *dPtr;

	Queue_b8Pop(&q, &dPtr);
	Queue_b8Pop(&q, &dPtr);

	Queue_b8Push(&q, dPtr);

	/*	Print queue	*/
	Queue_voidPrint(&q);

	while(1);

	return 0;
}


void copyData (s32** distPP, const s32* srcPtr)
{
	*distPP = malloc(sizeof(s32));

	**distPP = *srcPtr;
}

void deleteData (s32* dPtr)
{
	free(dPtr);
}

void printData (s32* dPtr)
{
	PRINTF("%d", *dPtr);
}

#endif	/*	TRY_QUEUE	*/

