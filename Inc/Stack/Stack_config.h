/*
 * Stack_config.h
 *
 *  Created on: Sep 21, 2022
 *      Author: ali20
 */

#ifndef _STACK_CONFIG_H_
#define _STACK_CONFIG_H_

#define STACK_ENABLE	0


#if STACK_ENABLE
/*
 * max len of the stack.
 * exceeding this max len would overwrite the first of
 * the stack, and reset the stack's counter.
 * */
#define STACK_MAX_LEN			2

/*
 * pointer to data-type to be stored in that stack.
 * (user may #include the file that contains this data-type here)
 */
#define STACK_TYPE_PTR			s32*

/*
 * pointer to the function that copies one object of the
 * stack's data-type to another one, the second is to be
 * allocated in it. it should take a pointer to pointer to
 * the object to be copied into, and a pointer to the object
 * to be copied from, and return void.
 * allocation of the object to be copied into is the responsibility
 * of this function.
 */
extern void copyData (s32** distPP, const s32* srcP);
#define STACK_COPY_FUNCTION		copyData

/*
 * pointer to the function that deletes object (frees allocated memory),
 * it takes pointer to pointer to the object.
 */
extern void freeData (s32** dataPP);
#define STACK_FREE_FUNCTION		freeData

#endif

#endif /* _STACK_CONFIG_H_ */
