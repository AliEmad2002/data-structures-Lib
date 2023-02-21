#define TRY_STACK		1

#if TRY_STACK

#include "Std_Types.h"
#include <stdio.h>
#include <stdlib.h>
#include "print.h"
#include <time.h>

#include "Stack_config.h"
#include "Stack_interface.h"

#define INITIAL_NUMBER_OF_DATA		5
#define MAX_DATA					1000
//#define RND_INIT					571468

void copyData (s32** distPP, const s32* srcP);

void freeData (s32** dataPP);

void printData	(const s32* dataPtr);

void print_stack(void);

int main(void) {
	PRINTF("Program started\n");
	/*	Init emulated random number generation	*/
	time_t tStart;
	srand(time(&tStart));

	/*	init stack	*/
	Stack_voidInit();

	/*	Push random data to stack	*/
	for (u32 i = 0; i < INITIAL_NUMBER_OF_DATA; i++)
	{
		u32 data = rand() % MAX_DATA;
		b8 pushSuccess = Stack_b8Push(&data);

		if (!pushSuccess)
		{
			PRINTF("Stack full!\n");
			while(1);
		}
	}

	/*	Print stack	*/
	print_stack();

	while(1);

	return 0;
}

void copyData (s32** distPP, const s32* srcP)
{
	*distPP = malloc(sizeof(s32));
	**distPP = *srcP;
}

void freeData (s32** dataPP)
{
	free(*dataPP);
}

void printData	(const s32* dataPtr)
{
	PRINTF("%d", *dataPtr);
}

void print_stack(void)
{
	PRINTF("Printing stack:\n");

	while(Stack_u16GetUsedLen() != 0)
	{
		s32* dataPtr;

		Stack_ptrPop((void**)&dataPtr);

		PRINTF("%d\n", *dataPtr);
	}

	PRINTF("===================\n");
}

#endif	/*	TRY_STACK	*/
