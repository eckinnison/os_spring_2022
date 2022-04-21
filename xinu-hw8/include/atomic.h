/**
 * @file atomic.h
 *
 * This file includes the function prototypes for atomic ARM assembly routines.
 *
 */
/* Embedded Xinu, Copyright (C) 2019. All rights reserved. */

#ifndef _ATOMIC_H_
#define _ATOMIC_H_

/**
 * @fn bool_atomic_compareAndSwap(volatile int *var, int old, int new)
 *
 * Atomically compare and swap old value for new value.
 *
 * @param *var  pointer to variable
 * @param old   expected old value in var
 * @param new   new value for var if old value matches
 * @return true of old value atomically replaced with new, else false
 */
bool _atomic_compareAndSwapStrong(volatile int *var, int old, int new);

/**
 * @fn bool_atomic_compareAndSwapWeak(volatile int *var, int old, int new)
 *
 * Atomically compare and swap old value for new value.
 *
 * @param *var  pointer to variable
 * @param old   expected old value in var
 * @param new   new value for var if old value matches
 * @return true of old value atomically replaced with new, else false
 */
bool _atomic_compareAndSwapWeak(volatile int *var, int old, int new);

#endif                          /* _ATOMIC_H_ */
