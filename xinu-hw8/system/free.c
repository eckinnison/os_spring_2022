/**
 * @file free.c
 */
/* Embedded Xinu, Copyright (C) 2009, 2020.  All rights reserved. */

#include <xinu.h>

/**
 * Attempt to free a block of memory based on malloc() accounting information
 * stored in preceding two words.
 *
 * @param ptr
 *      A pointer to the memory block to free.
 */
syscall free(void *ptr)
{
    struct memblock *block;

    //block -> head; //1?

    block = (struct memblock *)ptr;

    //kprintf("here %08x\r\n", block->length);
   // block--;
    if(block->next != block)//sanity check
	{
		return SYSERR;
	}
//        kprintf("here2 %08x\r\n", block->length-8);

    freemem(block, block->length);
    /* TODO:
     *      1) set block to point to memblock to be free'd (ptr)
     *      2) find accounting information of the memblock
     *      3) call freemem syscall on the block with its length
     */

    return OK;
}
