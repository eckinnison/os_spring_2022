/**
 * COSC 3250 - Project 4
 * Explain briefly the functionality of the program.
 * @author Emma Claire Kinnison Erin Cahil
 * Instructor Dr. Brylow
 * TA-BOT:MAILTO emma.kinnison@marquette.edu erin.cahill@marquette.edu
 * Collaborators: Gabbie Rohde and Jacob Deighton
 */
/**
 * @file syscall_dispatch.c
 * Translate user_* functions to system calls, dispatch to proper sc_*
 * functions, and complete.
 */
/* Embedded Xinu, Copyright (C) 2009, 2020.  All rights reserved. */

#include <xinu.h>

/* for syscall argument parsing */
#define SCARG(type, args)  (type)(*args++)

/* macro to make user->kernel syscalls */
#define SYSCALL(num) int status; \
	asm("swi %0" : : "i"(SYSCALL_##num)); \
	asm("mov %0, r0" : "=r"(status)); \
	return status;


/* syscall wrapper prototypes */
syscall sc_none(int *);
syscall sc_yield(int *);
syscall sc_getc(int *);
syscall sc_putc(int *);
syscall sc_getmem(ulong nbytes);
syscall sc_freemem(void *memptr, ulong nbytes);
syscall pthread_create(pthread_t * thread, pthread_attr_t * attr, void *(*start_routine)(void *), void *arg);
syscall pthread_join(pthread_t thread, void **retval);
syscall pthread_mutex_lock(pthread_mutex_t * mutex);
syscall pthread_mutex_unlock(pthread_mutex_t * mutex);

/* table for determining how to call syscalls */
const struct syscall_info syscall_table[] = {
    { 5, (void *)sc_none },     /* SYSCALL_NONE      = 0  */
    { 0, (void *)sc_yield },    /* SYSCALL_YIELD     = 1  */
    { 1, (void *)sc_none },     /* SYSCALL_SLEEP     = 2  */
    { 1, (void *)sc_none },     /* SYSCALL_KILL      = 3  */
    { 2, (void *)sc_none },     /* SYSCALL_OPEN      = 4  */
    { 1, (void *)sc_none },     /* SYSCALL_CLOSE     = 5  */
    { 3, (void *)sc_none },     /* SYSCALL_READ      = 6  */
    { 3, (void *)sc_none },     /* SYSCALL_WRITE     = 7  */
    { 1, (void *)sc_getc },     /* SYSCALL_GETC      = 8  */
    { 2, (void *)sc_putc },     /* SYSCALL_PUTC      = 9  */
    { 2, (void *)sc_none },     /* SYSCALL_SEEK      = 10 */
    { 4, (void *)sc_none },     /* SYSCALL_CONTROL   = 11 */
    { 1, (void *)sc_none },     /* SYSCALL_GETDEV    = 12 */
    { 1, (void *)pthread_create },
    { 1, (void *)pthread_join },
    { 1, (void *)pthread_mutex_lock },
    { 1, (void *)pthread_mutex_unlock },
    { 1, (void *)sc_getmem },   /* SYSCALL_GETMEM    = 17 */ 
    { 2, (void *)sc_freemem },  /* SYSCALL_FREEMEM   = 18 */
};

int nsyscall = sizeof(syscall_table) / sizeof(struct syscall_info);

/**
 * Syscall dispatch routine.  Given a syscall code and pointer to
 * arguments, change execution to function.  Otherwise, generate error
 * saying no such syscall.
 * @param code syscall code to execute
 * @param args pointer to arguments for syscall
 */
int syscall_dispatch(int code, int *args)
{
    if (0 <= code && code < nsyscall)
    {
        return (*syscall_table[code].handler) (args);
    }
    kprintf("ERROR: unknown syscall %d!\r\n", code);
    return SYSERR;
}

/**
 * syscall wrapper for *no* function, just a test/demo.
 * @param args expands to: none.
 */
syscall sc_none(int *args)
{
    return OK;
}



syscall user_none(void)
{
    SYSCALL(NONE);
}

/**
 * syscall wrapper for yield().
 * @param args expands to: none.
 */
syscall sc_yield(int *args)
{
    /* this may change thread of execution, allow exceptions */
    // exlreset();

    return resched();
}

syscall user_yield(void)
{
    SYSCALL(YIELD);
}

/**
 * syscall wrapper for getc().
 * @param args expands to: int descrp
 */
syscall sc_getc(int *args)
{
    int descrp = SCARG(int, args);
    if (0 == descrp)
    {
        return kgetc();
    }
    return SYSERR;
}

syscall user_getc(int descrp)
{
    SYSCALL(GETC);
}

/**
 * syscall wrapper for putc().
 * @param args expands to: int descrp, char character
 */
syscall sc_putc(int *args)
{
    int descrp = SCARG(int, args);
    char character = SCARG(char, args);

    if (0 == descrp)
        return kputc(character);
    return SYSERR;
}

syscall user_putc(int descrp, char character)
{
    SYSCALL(PUTC);
}

syscall sc_getmem(ulong nbytes)
{

}

syscall sc_freemem(void *memptr, ulong nbytes)
{

}


// -------------TODO-------------
// added based on Brylow feedback -- functions from pthread.h
// need to build each function but currently just returning to ensure we can compile
syscall pthread_create(pthread_t * thread, pthread_attr_t * attr, void *(*start_routine)(void *), void *arg){
    sc_create(arg);
    return 1; 
}


syscall pthread_join(pthread_t thread, void **retval){
    sc_join(thread);
    return 1; 
}


syscall pthread_mutex_lock(pthread_mutex_t * mutex){
   sc_lock(mutex);
    return 1; 
}


syscall pthread_mutex_unlock(pthread_mutex_t * mutex){
   sc_unlock(mutex);
    return 1; 
}