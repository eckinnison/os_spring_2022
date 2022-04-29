/**
 * @file getmem.c
 *
 */
/* Embedded Xinu, Copyright (C) 2009, 2020.  All rights reserved. */

#include <xinu.h>
#define SCARG(type, args) (type)(*args++)

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



void *sc_getmem(ulong nbytes)
{
    irqmask pc;     // NEW, disable interrupts while a line is being printed
    pc = disable(); // NEW
  //  ulong nbytes = SCARG(ulong, args); 

    register memblk *prev, *curr, *leftover;
    
    prev = &freelist;
    curr = freelist.head;    

    if (0 == nbytes)
    {
        return (void *)SYSERR;
    }    

    /* round to multiple of memblock size   */
    /*if((nbytes & (nbytes - 1)) == 0){
        nbytes = (ulong)roundmb(nbytes);
    }
    else{
        nbytes = (ulong)roundmb(nbytes+1);
    }*/
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
       else if(curr->length > nbytes){
           leftover = (struct memblock *)((ulong)curr+nbytes);
           leftover->length = curr->length -nbytes;
           leftover->next = curr->next;
            //kprintf("leftover length: %d\r\n", &leftover->length); //also freelist is probably wrong variable
            //kprintf("leftover next: %d\r\n", &leftover->next); //also freelist is probably wrong variable
           prev->next = leftover;
           freelist.size = freelist.size - nbytes;
           // kprintf("freelist size: %d\r\n", freelist.size); //also freelist is probably wrong variable
           restore(pc);
	       return (void *)curr; 
       }
//       else if(curr->length < nbytes){
//            restore(pc);
//	        return (void *)SYSERR;
//      }
        curr = curr->next;
        prev = prev->next;

    }


    restore(pc);    // NEW enable interupts

    return (void *)SYSERR;
}
