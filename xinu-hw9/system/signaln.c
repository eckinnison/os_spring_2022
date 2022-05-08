/**
 * @file signaln.c
 *
 */
/* Embedded Xinu, Copyright (C) 2009.  All rights reserved. */

#include <xinu.h>

/**
 * @ingroup semaphores
 *
 * Signal a semaphore @p count times, releasing @p count waiting threads.
 *
 * @param sem
 *      Semaphore to signal.
 * @param count
 *      Number of times to signal, which must be positive.
 *
 * @return
 *      ::OK on success, ::SYSERR on failure.  This function can only fail if @p
 *      sem did not specify a valid semaphore of if @p count was not positive.
 */
syscall signaln(semaphore sem, int count)
{
    register struct semtabent *semptr;
    int c;
    irqmask im;

    im = disable();
    if (isbadsem(sem) || (count <= 0))
    {
        restore(im);
        return SYSERR;
    }

    /**
     * TODO: Increment the semaphore 'count' times.
     * If the count was negative, wake waiting threads.
     * Yield the processor when the work is done.
     */

    restore(im);
    return OK;
}
