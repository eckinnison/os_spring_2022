/**
 * @file pthread.h
 * Definitions for PThread compatibility.
 *
 */
/* Embedded Xinu, Copyright (C) 2022.  All rights reserved. */

#ifndef _PTHREAD_H_
#define _PTHREAD_H_

#define PTHREAD_MUTEX_UNLOCKED 0
#define PTHREAD_MUTEX_LOCKED 1
#define PTHREAD_MUTEX_INITIALIZER PTHREAD_MUTEX_UNLOCKED

typedef int pthread_mutex_t;
typedef int pthread_t;
typedef int pthread_attr_t;

/* PThread function prototypes - see syscall_dispatch.c */
syscall pthread_create(pthread_t * thread, pthread_attr_t * attr,
                       void *(*start_routine)(void *), void *arg);
syscall pthread_join(pthread_t thread, void **retval);
syscall pthread_mutex_lock(pthread_mutex_t * mutex);
syscall pthread_mutex_unlock(pthread_mutex_t * mutex);

/* Internal Xinu implementations of PThread system calls - see pthread.c */
syscall sc_create(int *);
syscall sc_join(int *);
syscall sc_lock(int *);
syscall sc_unlock(int *);

#endif                          /* _PTHREAD_H_ */
