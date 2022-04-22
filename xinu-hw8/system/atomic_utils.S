/**
 * @file atomic.S
 *
 * Atomic assembly subroutines.
 *
 * Embedded Xinu, Copyright (C) 2018, 2020. All rights reserved.
 *
 */
.globl _atomic_compareAndSwapStrong
/**
 * The strong compare and swap will retry even if a "spurious failure" (i.e. accessing the same cache line) occurs.
 * function cas(p : pointer to int, old : int, new : int) returns bool {
 *    if *p ≠ old {
 *       return false
 *   }
 *   *p ← new
 *   return true
 * }
 */
_atomic_compareAndSwapStrong:	
	.func _atomic_compareAndSwapStrong
	pldw	[r0]
	ldrex	r3, [r0]
	cmp	r1, r3
	bne	1f
	strex	r3, r2, [r0]
	cmp	r3, #0
	bne	_atomic_compareAndSwapStrong
	moveq	r0, #1
	dmb
	bx	lr
1:
	mov	r0, #0		// return false
	dmb
	bx	lr
	.endfunc


.globl _atomic_compareAndSwapWeak
/**
 * The weak compare and swap (CAS) will not retry on "spurious failures".
 * function cas(p : pointer to int, old : int, new : int) returns bool {
 *    if *p ≠ old {
 *       return false
 *   }
 *   *p ← new
 *   return true
 * }
 */
_atomic_compareAndSwapWeak:	
	.func _atomic_compareAndSwapWeak
	pldw	[r0]
	ldrex	r3, [r0]
	cmp	r1, r3
	bne	1f
	strex	r3, r2, [r0]
	cmp	r3, #0
	bne	1f
	moveq	r0, #1
	dmb
	bx	lr
1:
	mov	r0, #0		// return false
	dmb
	bx	lr
	.endfunc
