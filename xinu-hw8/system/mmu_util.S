/**
 * @file mmu_util.S
 * @provides start_mmu stop_mmu invalidate_tlbs
 *
 */
/* Embedded Xinu, Copyright (C) 2013, 2020. All rights reserved */

#include <mmu.h>

/**
 * @fn void start_mmu(unsigned int table_base)
 *
 * Start the MMU with the table specified
 */
.globl start_mmu
start_mmu:
	mov	r2, #0
//	mcr p15, 0, r2, c7, c7, 0	;@ invalidate caches /* P.S. not supported in new architecture	*/
	mcr	p15, 0, r2, c7, c1, 0	;@ invalidate all i caches inner shareable to PoU
	mcr	p15, 0, r2, c7, c5, 0	;@ invalidate all i caches to PoU
	mcr	p15, 0, r2, c7, c6, 1	;@ invalidate d cache line by VA to PoC
	mcr	p15, 0, r2, c7, c6, 2	;@ invalidate d cache line by set/way
	mcr	p15, 0, r2, c8, c7, 0	;@ invalidate tlb	/* invalidate unified TLB	*/
	dsb

	mvn	r2, #0
	mcr	p15, 0, r2, c3, c0, 0	;@ domain

	orr	r0, #0x6A
	
	orr	r0, #0x6A

	mcr	p15, 0, r0, c2, c0, 0	;@ tlb base
	mcr	p15, 0, r0, c2, c0, 1	;@ tlb base

	/* SCTLR configuration*/
	mrc	p15, 0, r2, c1, c0, 0
	mov r1, #0x1
	orr	r1, r1, #0x1000
	orr	r1, r1, #0x4
	orr	r2, r2, r1
	mcr	p15, 0, r2, c1, c0, 0

	bx	lr

/**
 * @fn void stop_mmu(void)
 *
 * Stops the MMU.
 */
.globl stop_mmu
stop_mmu:
	mrc	p15, 0, r2, c1, c0, 0
	bic	r2, #0x1000
	bic	r2, #0x0004
	bic	r2, #0x0001
	mcr	p15, 0, r2, c1, c0, 0

	bx	lr

/**
 * @fn void invalidate_tlbs(void)
 *
 * invalidate the Translation Lookaside Buffer (TLB).
 */
.globl invalidate_tlbs
invalidate_tlbs:
	mov	r2, #0
	mcr	p15, 0, r2, c8, c7, 0
	dsb
	bx	lr
