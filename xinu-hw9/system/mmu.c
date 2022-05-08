/**
 * @file 		mmu.c
 * @provides	mmu_section mmu_init
 *
 */
/* Embedded Xinu, Copyright (C) 2008, 2020. All rights reserved. */

#include <xinu.h>

/**
 * Initializes the mmu to have virtual address == physical addresses,
 * also configures certain memory regions to be cacheable.
 */
void mmu_init()
{
    unsigned int ra;

    for (ra = 0; ra < PERIPHERALS_BASE; ra += 0x00100000)
    {
        mmu_section(ra, ra, 0x15C06);
    }

    // peripherals
    for (; ra; ra += 0x00100000)
    {
        mmu_section(ra, ra, 0x0000);
    }

    start_mmu(MMUTABLEBASE);
}

/**
 * Create mmu section entry in the MMU Table.
 * @param vadd	virtual address
 * 		  padd	physical address
 * 		  flags	flags to mark that section of memory
 * @return always returns 0
 */
unsigned int mmu_section(unsigned int vadd, unsigned int padd,
                         unsigned int flags)
{
    unsigned int *entry;

    entry = (unsigned int *)(MMUTABLEBASE | ((vadd >> 20) << 2));
    *entry = (padd & 0xFFF00000) | 0xC00 | flags | 2;

    return 0;
}
