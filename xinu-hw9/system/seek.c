/**
 * @file seek.c
 *
 */
/* Embedded Xinu, Copyright (C) 2009.  All rights reserved. */

#include <xinu.h>

/**
 * position a device (very common special case of control)
 * @param descrp definition of device on which to seek
 * @param pos requested position to seek
 * @return function to seek on device on success, SYSERR on failure
 */
devcall seek(int descrp, uint pos)
{
    device *devptr;

    if (isbaddev(descrp))
    {
        return SYSERR;
    }
    devptr = (device *)&devtab[descrp];
    return ((*devptr->seek) (devptr, pos));
}
