#ifndef _MMU_H_
#define _MMU_H_

#define MMUTABLEBASE	0x00004000

#ifndef __ASSEMBLER__
extern void start_mmu(unsigned int);
extern void stop_mmu(void);
extern void invalidate_tlbs(void);
extern unsigned int mmu_section(unsigned int, unsigned int, unsigned int);
extern void mmu_init(void);
#endif                          /* __ASSEMBLER__ */

#endif                          /* _MMU_H_ */
