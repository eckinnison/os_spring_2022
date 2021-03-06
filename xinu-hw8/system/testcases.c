/**
 * COSC 3250 - Project 4
 * Explain briefly the functionality of the program.
 * @author Emma Claire Kinnison Erin Cahil
 * Instructor Dr. Brylow
 * TA-BOT:MAILTO emma.kinnison@marquette.edu erin.cahill@marquette.edu
 * Collaborators: Gabbie Rohde and Jacob Deighton
 */
 /**
 * @file testcases.c
 * @provides testcases
 *
 * TA-BOT:MAILTO
 *
 */
/* Embedded XINU, Copyright (C) 2007.  All rights reserved. */

#include <xinu.h>
#include <stdio.h>

extern void main(int, char *);
void print_freelist(void);


int testmain(int argc, char **argv)
{
    int i = 0;
    kprintf("Hello XINU World test!\r\n");

    for (i = 0; i < 10; i++)
    {
        kprintf("This is process %d\r\n", currpid);

        user_yield();
    }
    return 0;
}

int infiniteloop(int argc, char **argv)
{
    kprintf("Hello XINU infinite!\r\n");

    int i=0;
    while(i==0)
    {
        user_yield();
    }
    return 0;
}
void testbigargs(int a, int b, int c, int d, int e, int f, int g, int h)
{
    kprintf("Testing bigargs...\r\n");
    kprintf("a = 0x%08X\r\n", a);
    kprintf("b = 0x%08X\r\n", b);
    kprintf("c = 0x%08X\r\n", c);
    kprintf("d = 0x%08X\r\n", d);
    kprintf("e = 0x%08X\r\n", e);
    kprintf("f = 0x%08X\r\n", f);
    kprintf("g = 0x%08X\r\n", g);
    kprintf("h = 0x%08X\r\n", h);
}

void printpcb(int pid)
{
    pcb *ppcb = NULL;

    /* Using the process ID, access it in the PCB table. */
    ppcb = &proctab[pid];

    /* Printing PCB */
    kprintf("Process name		  : %s \r\n", ppcb->name);

    switch (ppcb->state)
    {
    case PRFREE:
        kprintf("State of the process	  : FREE \r\n");
        break;
    case PRCURR:
        kprintf("State of the process 	  : CURRENT \r\n");
        break;
    case PRSUSP:
        kprintf("State of the process	  : SUSPENDED \r\n");
        break;
    case PRREADY:
        kprintf("State of the process	  : READY \r\n");
        break;
    default:
        kprintf("ERROR: Process state not correctly set!\r\n");
        break;
    }

    /* Print PCB contents and registers */
    kprintf("Base of run time stack    : 0x%08X \r\n", ppcb->stkbase);
    kprintf("Stack length of process   : %8u \r\n", ppcb->stklen);
}


void print_freelist()
{
    register struct memblock *block;
    block= freelist.head;
    while(block !=NULL){
        kprintf("address: 0x%08x \r\n", block);
		kprintf("length: 0x%08x \r\n", block->length);
		kprintf("next: 0x%08x \r\n", block->next);
		block = block->next; 
    }
}
/**
 * testcases - called after initialization completes to test things.
 */
void testcases(void)
{
    int c;

   
    kprintf("0) Test user_none syscall\r\n");
    kprintf("1) Test user_getc syscall\r\n");
    kprintf("2) Test user_putc syscall\r\n");
    kprintf("3) Create three processes that test user_yield syscall\r\n");
    kprintf("p) Test case that demonstrates preemptive scheduling\r\n");
    kprintf("4) Print out the freelist\r\n");
    kprintf("5) malloc normal, and power of 2\r\n");
    kprintf("6) getMem power of 2, and normal\r\n");
    kprintf("7) freemem Mem and free\r\n");

    kprintf("===TEST BEGIN===\r\n");

    // TODO: Test your operating system!

    c = kgetc();
    switch (c)
    {
    case '0':
        // Test user_none
        kprintf("This is a test of ...");
        user_none();
        kprintf("user_none() syscall\r\n");
        break;

    case '1':
        kprintf("Enter another character through user_getc() syscall :");
        c = user_getc(0);
        kprintf("\r\nCharacter entered was \'%c\'\r\n", c);
        break;

    case '2':
        kprintf("Echo characters until 'X': ");
        while ((c = user_getc(0)) != 'X')
        {
            user_putc(0, c);
        }
        kprintf("\r\n");
        break;

    case '3':
        // Create three copies of a process, and let them play.
        ready(create((void *)testmain, INITSTK, 1, "MAIN1", 2, 0, NULL),
              RESCHED_NO);

        ready(create((void *)testmain, INITSTK, 3, "MAIN2", 2, 0, NULL),
              RESCHED_NO);

        ready(create((void *)testmain, INITSTK, 2, "MAIN3", 2, 0, NULL),
              RESCHED_YES);

        while (numproc > 1)
            resched();
        break;
    case 'p':   //TODO!!!!
        ready(create((void *)testmain, INITSTK, 6, "MAIN1", 2, 0, NULL),
              RESCHED_YES);
        ready(create((void *)infiniteloop, INITSTK, 3, "MAIN1", 2, 0, NULL),
              RESCHED_YES);
        while (numproc > 1)
            resched();
        break;
    case '4': //FREELIST PRINT
            print_freelist();
        break;
    case '5': //malloc
        print_freelist();
		ulong *a = malloc(0x1000);
       	print_freelist();	
        ulong *b = malloc(134217728);
       	print_freelist();		
        /*freemem(a, 0x1000);
        kprintf("free 0x1000\r\n");
        print_freelist();  */  
        break;
    case '6': //Check 64 bits
        print_freelist();
        getmem(134217728);  //check power of 2
        print_freelist();
        getmem(0x0100);     //check normal
        print_freelist();   
        break;
    case '7': //freemem
        print_freelist();
        ulong *c = malloc(134217728);  //check power of 2
        print_freelist();
        ulong *d = malloc(0x0100);  //check normal
        print_freelist();


        kprintf("\r\n");
        freemem(d, 0x0100);
        print_freelist();
        kprintf("\r\n");
        freemem(c, 134217728);
        print_freelist();

        break;

    case '8': //free
        print_freelist();
        ulong *e = malloc(134217728);  //check power of 2
        print_freelist();
        ulong *f = malloc(0x0100);  //check normal
        print_freelist();


        kprintf("\r\n");
        free(e);
        print_freelist();
        kprintf("\r\n");
        free(f);
        print_freelist();
        break;
    default:
        break;
    }

    //TODO: Create a new method to infinitelyl loop
    //TODO: Create and call two or more versions of that method

    kprintf("\r\n===TEST END===\r\n");
    return;
}
