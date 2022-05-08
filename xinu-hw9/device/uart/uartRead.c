/**
 * @file uartRead.c
 */
/* Embedded Xinu, Copyright (C) 2018. All rights reserved. */

#include <xinu.h>

extern struct uart serial_port;


/**
 * Asynchrounously read characters from the UART.
 *
 * @return
 *      The character read from the UART.
 */
devcall uartRead(device *devptr, void *buffer, uint count)
{

    int i = 0;
    char *buf = (char *)buffer;

    for (i = 0; i < count; i++)
        buf[i] = uartGetc(devptr);

    return OK;
}
