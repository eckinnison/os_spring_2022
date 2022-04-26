/**
 * @file kill.c
 * Provides: kill
 *
 * COSC 3250 Assignment 4
 */

/* Embedded XINU, Copyright (C) 2008.  All rights reserved. */

#include <xinu.h>

/*
 * kill  --  kill a process and remove it from the system
 */
syscall kill(int pid)
{
    pcb *ppcb;                  /* points to process control block for pid */

    if (isbadpid(pid) || (0 == pid)
        || (PRFREE == (ppcb = &proctab[pid])->state))
    {
        return SYSERR;
    }
    freemem(ppcb, ppcb->stklen);
    ppcb = &proctab[pid];

    --numproc;

    switch (ppcb->state)
    {
    case PRCURR:
        ppcb->state = PRFREE;   /* suicide */
        resched();

    case PRREADY:
        remove(pid);
    
    case PRJOIN:
        remove(pid);
    default:
        ppcb->state = PRFREE;
    }

    //dequeue(currpid); // TODO: just an unfinished reminder to implement dequeue

    return OK;
}
