/**
 * COSC 3250 - Project 3
 * Explain briefly the functionality of the program.
 * @author Emma Claire Kinnison David Santiago
 * Instructor Dr. Brylow
 * TA-BOT:MAILTO emma.kinnison@marquette.edu david.santiago@marquette.edu
 */
 /**
  * @file kprintf.c
  */

  /* Embedded Xinu, Copyright (C) 2009, 2013.  All rights reserved. */

#include <xinu.h>

#define UNGETMAX 10             /* Can un-get at most 10 characters. */
#define ENTER_ASCII 10          //no magic numbers
#define RETURN_ASCII 13
#define EOT 4

static unsigned char ungetArray[UNGETMAX];
/**
 * Synchronously read a character from a UART.  This blocks until a character is
 * available.  The interrupt handler is not used.
 *
 * @return
 *      The character read from the UART as an <code>unsigned char</code> cast
 *      to an <code>int</code>.
 */
syscall kgetc(void) //*****************HELP*************
{
    volatile struct pl011_uart_csreg* regptr;

    /* Pointer to the UART control and status registers.  */
    regptr = (struct pl011_uart_csreg*)0x3F201000;

    // TODO: First, check the unget buffer for a character.
    //       Otherwise, check UART flags register, and
    //       once the receiver is not empty, get character c.
    unsigned char c = 0;

    if (kcheckc()) {                    //check to see if the vals are there
        for (int k = 0; k < UNGETMAX; k++) {        //loop through the array
            if (ungetArray[k] != NULL) {        //if its null put the char in the array
                c=ungetArray[k];
                ungetArray[k] = NULL;
                if (c == EOT) {
                    c = EOF;
                    return c;
                }
                return(int) c;
            }
        }
    }
    
    while ((regptr->fr) & (PL011_FR_RXFE)) {    //otherwise wait until its not empty 
    }
    
    c = regptr->dr;     //and put the char into the reciever
    return (int)c;
    
}

/**
 * kcheckc - check to see if a character is available.
 * @return true if a character is available, false otherwise.
 */
syscall kcheckc(void)
{
    int j = 0;
    volatile struct pl011_uart_csreg* regptr;
    regptr = (struct pl011_uart_csreg*)0x3F201000;
    while (j < UNGETMAX) {          //loop though the array and if its NULL return a 1
        if (ungetArray[j] != NULL) {
            return 1;
        }
        j++;
    }

    if ((regptr->fr) & (PL011_FR_RXFE)) {       //otherwise if theres a char availble return a o
        return 0;
    }
    // TODO: Check the unget buffer and the UART for characters.

    return 1;
}

//kungetc was not needed and was deleted


/**
 * Synchronously write a character to a UART.  This blocks until the character
 * has been written to the hardware.  The interrupt handler is not used.
 *
 * @param c
 *      The character to write.
 *
 * @return
 *      The character written to the UART as an <code>unsigned char</code> cast
 *      to an <code>int</code>.
 */
syscall kputc(uchar c)
{
    volatile struct pl011_uart_csreg* regptr;

    /* Pointer to the UART control and status registers.  */
    regptr = (struct pl011_uart_csreg*)0x3F201000;

    // TODO: Check UART flags register.
    //       Once the Transmitter FIFO is not full, send character c.

    while ((regptr->fr) & (PL011_FR_TXFF)) {    //wait until the register is not full
    }
   
   // regptr->dr = c;

    if (c == ENTER_ASCII) {         //if its an enter
        regptr->dr = RETURN_ASCII;  //send the /r
        while (((regptr->fr) & (PL011_FR_TXFF))) {  //wait for the register to be full
        }
    }
    regptr->dr = c; //send the char

    return(int)c;
}

/**
 * kernel printf: formatted, synchronous output to SERIAL0.
 *
 * @param format
 *      The format string.  Not all standard format specifiers are supported by
 *      this implementation.  See _doprnt() for a description of supported
 *      conversion specifications.
 * @param ...
 *      Arguments matching those in the format string.
 *
 * @return
 *      The number of characters written.
 */
syscall kprintf(const char* format, ...)    //didnt touch this
{
    int retval;
    va_list ap;
    va_start(ap, format);
    retval = _doprnt(format, ap, (int (*)(int, int))kputc, 0);
    va_end(ap);
    return retval;
}