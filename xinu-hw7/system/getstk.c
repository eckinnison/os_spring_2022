/**
 * @file getstk.c
 * @provides getstk
 */
/* Embedded XINU, Copyright (C) 2007.  All rights reserved. */

#include <xinu.h>

extern void *end;

/**
 * Allocate stack memory, returning address of topmost word.
 * @param nbytes amount of memory to allocate, in bytes
 * @return address of the topmost word
 */
void *getstk(ulong nbytes)
{
    /* NOTE: This is a completely broken implementation of getstk(),      */
    /*  intended only for introductory assignments before implementing    */
    /*  proper dynamic heap allocation.                                   */

    ulong newstk;

    if (nbytes == 0)
    {
        return ((void *)SYSERR);
    }

    if (platform.maxaddr > (void *)PERIPHERALS_BASE)
        platform.maxaddr = (void *)PERIPHERALS_BASE;
    nbytes = (nbytes + 15) & ~0x0F;

    if ((long)platform.maxaddr - nbytes < (int)&_end)
    {
        return ((void *)SYSERR);
    }

    newstk = ((ulong)platform.maxaddr - 4) & 0xFFFFFFF0;
    platform.maxaddr = (char *)(((int)platform.maxaddr) - nbytes);

    return ((void *)newstk);
}
