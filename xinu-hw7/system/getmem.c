/**
 * @file getmem.c
 *
 */
/* Embedded Xinu, Copyright (C) 2009, 2020.  All rights reserved. */

#include <xinu.h>

/**
 * Allocate heap memory.
 *
 * @param nbytes
 *      Number of bytes requested.
 *
 * @return
 *      ::SYSERR if @p nbytes was 0 or there is no memory to satisfy the
 *      request; otherwise returns a pointer to the allocated memory region.
 *      The returned pointer is guaranteed to be 8-byte aligned.  Free the block
 *      with memfree() when done with it.
 */
void *getmem(ulong nbytes)
{
    irqmask pc;     // NEW, disable interrupts while a line is being printed
    pc = disable(); // NEW

    register memblk *prev, *curr, *leftover;
    
    prev = &freelist;
    curr = freelist.head;    

    if (0 == nbytes)
    {
        return (void *)SYSERR;
    }    

    /* round to multiple of memblock size   */
    nbytes = (ulong)roundmb(nbytes);

    /* TODO:
     *      - Disable interrupts(DONE?)
     *      - Traverse through the freelist
     *        to find a block that's suitable 
     *        (Use First Fit with remainder splitting)
     *      - Restore interrupts(DONE?)
     *      - return memory address if successful
     */

    while(curr != NULL){
       if(curr->length == nbytes){
           prev->next =curr->next;
           freelist.size = freelist.size - nbytes;
           restore(pc);
	       return (void *)curr;
       }
       else if(curr->length>nbytes){
           leftover = (struct memblock *)((ulong)curr+nbytes);
           leftover->length = curr->length -nbytes;
           leftover->next = curr->next;
           prev->next = leftover;
           freelist.size = freelist.size - nbytes;
           restore(pc);
	       return (void *)curr;
       }

        curr = curr->next;
        prev = prev->next;

    }


    restore(pc);    // NEW enable interupts

    return (void *)SYSERR;
}
