/**
 * COSC 3250 - Project 4
 * Explain briefly the functionality of the program.
 * @author Emma Claire Kinnison Erin Cahil
 * Instructor Dr. Brylow
 * TA-BOT:MAILTO emma.kinnison@marquette.edu erin.cahill@marquette.edu
 * Collaborators: Gabbie Rohde and Jacob Deighton
 */
 /**
 * @file create.c
 * @provides create, newpid, userret
 *
 * COSC 3250 Assignment 4
 */
/* Embedded XINU, Copyright (C) 2008.  All rights reserved. */

#include <xinu.h>
#include<stdarg.h>
#include<stdio.h>
#include <arm.h>


static pid_typ newpid(void);
void userret(void);
void *getstk(ulong);

/**
 * Create a new process to start running a function.
 * @param funcaddr address of function that will begin in new process
 * @param ssize    stack size in bytes
 * @param name     name of the process, used for debugging
 * @param nargs    number of arguments that follow
 * @return the new process id
 */
syscall create(void *funcaddr, ulong ssize, unsigned int priority, char *name, ulong nargs, ...)
{
    ulong *saddr;               /* stack address                */
    ulong pid;                  /* stores new process id        */
    pcb *ppcb;                  /* pointer to proc control blk  */
    ulong i;
    va_list ap;                 /* points to list of var args   */
    ulong pads = 0;             /* padding entries in record.   */
    void INITRET(void);     //IDK what this is

    if (ssize < MINSTK)
        ssize = MINSTK;
    ssize = (ulong)(ssize + 3) & 0xFFFFFFFC;
    /* round up to even boundary    */
    saddr = (ulong *)getstk(ssize);     /* allocate new stack and pid   */
    pid = newpid();
    /* a little error checking      */
    if ((((ulong *)SYSERR) == saddr) || (SYSERR == pid))
    {
        return SYSERR;
    }

    numproc++;
    ppcb = &proctab[pid];
	
	// TODO: Setup PCB entry for new process.
    ppcb->stkbase = (ulong*)(((ulong)saddr) - ssize);   //given from class
    ppcb->state = PRSUSP; //set to suspend
    ppcb->stkptr = saddr; //strores the pointer
    ppcb->stklen = ssize; //stores the size
    ppcb->tickets = priority; //TODO set value(DONE?)
    strncpy(ppcb->name, name, PNMLEN);

    /* Initialize stack with accounting block. */
    *saddr = STACKMAGIC;
    *--saddr = pid;
    *--saddr = ppcb->stklen;
    *--saddr = (ulong)ppcb->stkbase;

    /* Handle variable number of arguments passed to starting function   */
    if (nargs)
    {
        pads = ((nargs - 1) / 4) * 4;
    }
    /* If more than 4 args, pad record size to multiple of native memory */
    /*  transfer size.  Reserve space for extra args                     */

    for (i = 0; i <= pads; i++)
    {
        *--saddr = 0;
    }
    int *Record = saddr;


 
   

    for (i = 0; i < 16; i++)
        {
            *--saddr = 0;
        }
        saddr[CTX_LR]=&userret; //assigned to LR
        saddr[CTX_PC]=funcaddr; //assigned to PC

        	// TODO: Initialize process context.
        saddr[CTX_R2] = ARM_MODE_SYS | ARM_F_BIT;    //Sets specific spot in stack to enable interrupts


    ppcb->stkptr = saddr; //strores the pointer
    
    va_start(ap, nargs);

    // goes through amount of arguments to add to stack
    for (int i = 0; i < nargs; i++) {
        if (i < 4) { // iterates through the args
            saddr[i]= va_arg(ap, int);
           // kprintf("here 0x%08X\r\n", saddr[i]);
        }
        else { // puts in stack where the buffer is
            Record[i-4] = va_arg(ap, int);
           // kprintf("here2 0x%08X==0x%08X\r\n", Record[i-4], &Record[i-4]);

        }
    }
    va_end(ap);

 
    return pid;
}

/**
 * Obtain a new (free) process id.
 * @return a free process id, SYSERR if all ids are used
 */
static pid_typ newpid(void)
{
    pid_typ pid;                /* process id to return     */
    static pid_typ nextpid = 0;

    for (pid = 0; pid < NPROC; pid++)
    {                           /* check all NPROC slots    */
        nextpid = (nextpid + 1) % NPROC;
        if (PRFREE == proctab[nextpid].state)
        {
            return nextpid;
        }
    }
    return SYSERR;
}

/**
 * Entered when a process exits by return.
 */
void userret(void)
{
    kill(currpid);
}
