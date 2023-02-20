/*
 * Print.h
 *
 *  Created on: Feb 21, 2023
 *      Author: ali20
 */

#ifndef INC_PRINT_H_
#define INC_PRINT_H_


#define PC		0

#define SMT32	1

#define SYSTEM	PC

#if SYSTEM == PC
	#include <stdio.h>
	#define PRINTF	printf

#elif SYSTEM == SMT32
	#include "diag/trace.h"
	#define PRINTF	trace_printf

#endif


#endif /* INC_PRINT_H_ */
