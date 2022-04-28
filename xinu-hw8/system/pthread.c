/**
 * @file pthread.c
 * Internal Xinu functions implementing system calls for PThread API.
 */
/* Embedded Xinu, Copyright (C) 2009, 2022.  All rights reserved. */

#include <xinu.h>

/* for syscall argument parsing */
#define SCARG(type, args)  (type)(*args++)

/* 
 * syscall pthread_create(pthread_t *thread, pthread_attr_t *attr,
 *               void *(*start_routine)(void *), void *arg);
 */
syscall sc_create(int *args)
{
    pthread_t    *thread = SCARG(pthread_t *, args);
    pthread_attr_t *attr = SCARG(pthread_attr_t *, args);       /* ignore */
    void  *start_routine = SCARG(void *, args);
    void            *arg = SCARG(void *, args);

    /**
     * TODO: Translate the pthread_create() call into the equivalent
     * call of our existing create() function for spawning new processes.
     * Use defaults INITSTK and INITPRIO for initial stack size and lottery
     * tickets.  Don't forget to use ready() to move the new process into
     * the PRREADY state.
     */

    return OK;
}


/* 
 * syscall pthread_join(pthread_t thread, void **retval);
 */
syscall sc_join(int *args)
{
    pthread_t thread = SCARG(pthread_t, args);
    void    **retval = SCARG(void **, args);       /* ignore */

    int ps;
    register pcb *ppcb;

    /**
     * TODO: Move the calling process into the PRJOIN state,
     * Enqueue it on the JOIN queue of thread's PCB, and
     * yield the processor.
     */

    return OK;
}

/*
 * syscall pthread_mutex_lock(pthread_mutex_t *mutex);
 */
syscall sc_lock(int *args)
{
    pthread_mutex_t *mutex = SCARG(pthread_mutex_t *, args);

    /**
     * TODO: Use the atomic CAS operation to secure the mutex lock.
     */
    
    return OK;
}

/*
 * syscall pthread_mutex_unlock(pthread_mutex_t *mutex);
 */
syscall sc_unlock(int *args)
{
    pthread_mutex_t *mutex = SCARG(pthread_mutex_t *, args);

    /**
     * TODO: Release the mutex lock.
     */

    return OK;
}
