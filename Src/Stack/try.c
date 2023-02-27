#define TRY_STACK		1

#if TRY_STACK

#include "Std_Types.h"
#include <stdio.h>
#include <stdlib.h>
#include "print.h"
#include <time.h>

#include "Stack_interface.h"

#define INITIAL_NUMBER_OF_DATA		5
#define MAX_DATA					1000
//#define RND_INIT					571468

void copyData (s32** distPP, const s32* srcP);

void freeData (s32* dataPtr);

void printData	(s32* dataPtr);

int main(void) {
	PRINTF("Program started\n");
	/*	Init emulated random number generation	*/
	time_t tStart;
	srand(time(&tStart));

	/*	init stack	*/
	Stack_t stack;
	Stack_voidInit(&stack);

	/*	Push random data to stack	*/
	for (u32 i = 0; i < INITIAL_NUMBER_OF_DATA; i++)
	{
		s32 data = rand() % MAX_DATA;
		b8 pushSuccess = Stack_b8Push(&stack, &data);

		PRINTF("%u: Pushed: %d\n", i, data);

		if (!pushSuccess)
		{
			PRINTF("Stack full!\n");
			while(1);
		}
	}

	/*	Print stack	*/
	Stack_voidPrint(&stack);

	while(1);

	return 0;
}

void copyData (s32** distPP, const s32* srcP)
{
	*distPP = malloc(sizeof(s32));
	**distPP = *srcP;
}

void freeData (s32* dataPtr)
{
	free(dataPtr);
}

void printData	(s32* dataPtr)
{
	PRINTF("%d", *dataPtr);
}

#endif	/*	TRY_STACK	*/
