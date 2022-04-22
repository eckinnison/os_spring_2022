/**
 * COSC 3250 - Project 4
 * Explain briefly the functionality of the program.
 * @author Emma Claire Kinnison David Santiago
 * Instructor Dr. Brylow
 * TA-BOT:MAILTO emma.kinnison@marquette.edu david.santiago@marquette.edu
 */
/**
 * @file     main.c
 */
/* Embedded Xinu, Copyright (C) 2009, 2022.  All rights reserved. */

#include <xinu.h>

/**
 * Main process.  You can modify this routine to customize what Embedded Xinu
 * does when it starts up.
 */
process main(void)
{
    kprintf("Hello Xinu World!\r\n");

   // kprintf("Enter your codebreaker text:\r\n");
    //create();
    //testcases();
    //ctxsw();
   
    // TODO: Put your main program for codebreaker here.
    //       Replace any calls to printf() with kprintf().
    //       Replace any calls to getchar() with kgetc().

    while (1)
        ;

    return 0;
}
