/**
 * @file uartGetc.c
 */
/* Embedded Xinu, Copyright (C) 2018. All rights reserved. */

#include <xinu.h>

extern struct uart serial_port;


/**
 * Asynchrounously read a character from the UART.
 *
 * @return
 *      The character read from the UART.
 */
devcall uartGetc(device *devptr)
{
    uchar c;
    irqmask im = disable();

    /* TODO:
     * Asynchronously read a character from the UART.
     * Wait for input using the appropriate semaphore.
     * Store the first byte in the input buffer (as a character) to later be returned.
     * Then, decrement the counter of bytes in the input buffer.
     * Increment the index of the input buffer's first byte
     * with respect to the total length of the UART input buffer.
     */

    restore(im);
    return c;
}
