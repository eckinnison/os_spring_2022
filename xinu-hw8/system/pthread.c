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


//**************DONE******************
    /**
     * TODO: Translate the pthread_create() call into the equivalent
     * call of our existing create() function for spawning new processes.
     * Use defaults INITSTK and INITPRIO for initial stack size and lottery
     * tickets.(done)  Don't forget to use ready() to move the new process into
     * the PRREADY state.(done)
     */        

    *thread = create((void *)start_routine, INITSTK, INITPRIO, "PThread0", 1, arg); //"treat it as a lone argument passed through to create(), and trust the thread main program to work it out on the other end."
    ready(*thread, RESCHED_YES);

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
    irqmask pc;
    pc = disable();
     //this was commented out above is it the answer???
     // I didn't write this, so idk why it was given
    ASSERT(!isbadpid(thread));
    ppcb = &proctab[currpid];
    ppcb->state = PRJOIN;
    enqueue(currpid, PRJOIN);
    resched();
    restore(pc);
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
    while (_atomic_compareAndSwapStrong(mutex, PTHREAD_MUTEX_UNLOCKED, PTHREAD_MUTEX_LOCKED) == FALSE){
		resched();
    };

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
    *mutex = PTHREAD_MUTEX_UNLOCKED;

    return OK;
}
