/**
 * @file freemem.c
 *
 */
/* Embedded Xinu, Copyright (C) 2009, 2020.  All rights reserved. */

#include <xinu.h>

/**
 * Frees a block of heap-allocated memory.
 *
 * @param memptr
 *      Pointer to memory block allocated with memget().
 *
 * @param nbytes
 *      Length of memory block, in bytes.  (Same value passed to memget().)
 *
 * @return
 *      ::OK on success; ::SYSERR on failure.  This function can only fail
 *      because of memory corruption or specifying an invalid memory block.
 */
syscall freemem(void *memptr, ulong nbytes)
{
    irqmask pc;     // NEW, disable interrupts while a line is being printed
    pc = disable(); // NEW
    
    register struct memblock *block, *next, *prev;
    ulong top;

    /* make sure block is in heap */
    if ((0 == nbytes)
        || ((ulong)memptr < freelist.base)
        || ((ulong)memptr > freelist.base + freelist.bound))
    {
        return SYSERR;
    }

    block = (struct memblock *)memptr;
    nbytes = (ulong)roundmb(nbytes);
    prev =(struct memblock *)&freelist;
	next = freelist.head;
    /* TODO:
     *      - Disable interrupts (DONE?)
     *      - Find where the memory block should
     *        go back onto the freelist (based on address)
     *      - Find top of previous memblock
     *      - Make sure block is not overlapping on prev or next blocks
     *      - Coalesce with previous block if adjacent
     *      - Coalesce with next block if adjacent
     *      - Restore interrupts (DONE?)
     */
    while(next != NULL && (ulong)block > (ulong)next){
        prev = next;
        next = next->next;
    }

    if (prev==(struct memblock *)&freelist){
        top = NULL;
    } 
    else{
        top=(ulong)prev + prev->length;
    }

    if((top>(ulong)block)||((next!=NULL)&&(((ulong)block + nbytes)>(ulong)next))){
        restore(pc);
        return SYSERR;
    }

    freelist.size += nbytes;

    if(((ulong)block + block->length)+(ulong)next){
        block->length=block->length + next->length;
        block->next = next->next;
    }

    if(top == (ulong)block){
        prev->length += block->length;
        block = prev;
        prev->next = block->next;
    }

    memblk *p = freelist.head;
    while (p!= NULL){
        kprintf("{0x%08x; %10x; 0x%08x} \n", p, p->length, p->next);
        p = p->next;
    }
    restore(pc);    // NEW enable interupts
    return OK;
}
