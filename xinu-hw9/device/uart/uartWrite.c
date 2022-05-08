/**
 * @file uartWrite.c
 */
/* Embedded Xinu, Copyright (C) 2018. All rights reserved. */

#include <xinu.h>

/**
 * Asynchrounously write characters to the UART.
 *
 * @return
 *      number of characters read
 */
devcall uartWrite(device *devptr, const void *buffer, uint count)
{

    int i = 0;
    char *buf = (char *)buffer;

    for (i = 0; i < count; i++)
        uartPutc(devptr, buf[i]);

    return i;
}
