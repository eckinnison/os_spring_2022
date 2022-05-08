/**
 * @file uartPutc.c
 */
/* Embedded Xinu, Copyright (C) 2018. All rights reserved. */

#include <xinu.h>

extern struct uart serial_port;


/**
 * Asynchronously write a character to the UART.
 *
 * @param c
 *      The character to write.
 *
 * @return OK on success
 */
devcall uartPutc(device *devptr, char c)
{
    irqmask im = disable();

    /* TODO:
     * First, check if the UART transmitter is idle (see include/uart.h for
     * UART control block information).  If it is idle, set its state to
     * busy (hint: not idle), then write the character to the UART control
     * and status register's data register.  If it is not idle, use the
     * appropriate UART semaphore to wait for the UART's buffer space to be
     * free.  Next, place the character into the UART output buffer with
     * respect to the index of the buffer's first byte, amount of bytes in
     * buffer, and total length of the UART output buffer.  Then, increment
     * the counter of bytes in the output buffer. 
     */

    restore(im);
    return OK;
}
