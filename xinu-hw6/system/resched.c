/**
 * @file resched.c
 * @provides resched
 *
 * COSC 3250 Assignment 4
 */
/* Embedded XINU, Copyright (C) 2008.  All rights reserved. */

#include <xinu.h>

extern void ctxsw(void *, void *);
/**
 * Reschedule processor to next ready process.
 * Upon entry, currpid gives current process id.  Proctab[currpid].pstate 
 * gives correct NEXT state for current process if other than PRREADY.
 * @return OK when the process is context switched back
 */
syscall resched(void)
{
    pcb *oldproc;               /* pointer to old process entry */
    pcb *newproc;               /* pointer to new process entry */

    oldproc = &proctab[currpid];

    /* place current process at end of ready queue */
    if (PRCURR == oldproc->state)
    {
        oldproc->state = PRREADY;
        enqueue(currpid, readylist);
    }

        //******************************************************
        //function given by brylow to people in class on friday only below
        //******************************************************

    for(i=0; i< NPROC; i++){

        if((PRCURR == proctab[i].state) || (PRREADY == proctab[i].state)){
            totaltickets += proctab[i].ticket
        }

    }

// TEXTBOOK 9.1 CODE (editted based on our functions):

    // counter: used to track if we’ve found the winner yet
        int counter = 0;

    // winner: use some call to a random number generator to
    // get a value, between 0 and the total # of tickets
        int winner = random(totaltickets);

    // current: use this to walk through the list of jobs
        node_t *current = head;
        while (current) {
            counter = counter + current->tickets;
            if (counter > winner)
                break; // found the winner
            current = current->next;
        }
    // ’current’ is the winner: schedule it...

    /**
     * We recommend you use a helper function for the following:
     * TODO: Get the total number of tickets from all processes that are in current and ready states.
     * Utilize the random() function to pick a random ticket. 
     * Traverse through the process table to identify which proccess has the random ticket value.
     * Remove process from queue.
     * Set currpid to the new process.
        currpid = newproc
     */

    currpid = dequeue(readylist);
    newproc=&proctab[currpid];
    newproc->state = PRCURR;    /* mark it currently running    */
    remove(currpid);

    currpid = newproc; // currpid set to new process, given above, should go here or above in textbook code?
    

#if PREEMPT
    preempt = QUANTUM;
#endif

    ctxsw(&oldproc->stkptr, &newproc->stkptr);

    /* The OLD process returns here when resumed. */
    return OK;
}
