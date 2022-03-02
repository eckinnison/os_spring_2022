/**
 * COSC 3250 - Project 4
 * Explain briefly the functionality of the program.
 * @author Emma Claire Kinnison Erin Cahil
 * Instructor Dr. Brylow
 * TA-BOT:MAILTO emma.kinnison@marquette.edu erin.cahill@marquette.edu
 * Collaborators: Gabbie Rohde and Jacob Deighton
 */
 /**
 * @file xtrap.c 
 * @provides xtrap
 *
 */
/* Embedded XINU, Copyright (C) 2007, 2020.  All rights reserved. */

#include <xinu.h>

char *trap_names[] = {
    "Reset",
    "Undefined Instruction",
    "Software Interrupt (SWI)",
    "Prefetch Abort",
    "Data Abort",
    "IRQ Interrupt Request",
    "FIQ Interrupt Request"
};

/**
 * Generic XINU Trap (Interrupt) Handler.
 *
 * @param cause the contents of the cause register used to decode the trap
 * @param frame pointer to the interrupt frame with saved status
 *
 */
void xtrap(long *frame, int cause)
{
    /* Decode and handle IRQ separately. */
    if (cause == ARM_EXCEPTION_IRQ)
    {
        dispatch();
        return;
    }
        float* swi;
        int c=0;
    /* TODO: Implement system calls for Xinu.
     * 1) Recognize when cause of hardware exception is SWI opcode,*/

	int i;
	long ocvar; // Holds opcode variable
        if (cause == ARM_EXCEPTION_SWI){
        kprintf("\nthis is the value of &swi: 0x%08X\r\n\n", &swi);     //this value is now in frame[14]
        kprintf("\nthis is the value of ARM_EXCEPTION_SWI: 0x%08X\r\n\n", ARM_EXCEPTION_SWI);   //this value is now in frame[12]
        //lr:0x3F201000, which matches the opcode variable in frame[13] (or r10 in the given code below)

        // 2) Find the responsible SWI opcode in memory,
                /*for(i = 0; i <23; i++){ // Run through frames 0-15, &ing them to find opcode
                        --frame;                //************************i think we need to increment the stack??
                }*/
                for(i = 0; i < 16; i++){ // Run through frames 0-15, &ing them to find opcode
                        ocvar = ((long)&frame[i] & 0xFFFFFF);
                        kprintf("this is the value of frame[%d]: 0x%08X\r\n", i, frame[i]);
                        kprintf("this is the opcode variable of frame[%d]: 0x%08X\r\n", i, ocvar);
                }
                swi= ((long)frame[14]  & 0xFFFFFF);
                kprintf("this is the value of swi 0x%08X\r\n", swi);

        }

     /*   if (cause == ARM_EXCEPTION_SWI){
                swi=frame[2];
                kprintf("\nthis is frame[15] code 0x%08X\r\n", frame[15]);
                kprintf("this is frame[14] code 0x%08X\r\n", frame[14]);
                kprintf("this is frame[13] code 0x%08X\r\n", frame[13]);
                kprintf("this is frame[12] code 0x%08X\r\n", frame[12]);
                kprintf("this is frame[11] code 0x%08X\r\n", frame[11]);
                kprintf("this is frame[10] code 0x%08X\r\n", frame[10]);
                kprintf("this is frame[9] code 0x%08X\r\n", frame[9]);
                kprintf("this is frame[8] code 0x%08X\r\n", frame[8]);
                kprintf("this is frame[7] code 0x%08X\r\n", frame[7]);
                kprintf("this is frame[6] code 0x%08X\r\n", frame[6]);
                kprintf("this is frame[5] code 0x%08X\r\n", frame[5]);
                kprintf("this is frame[4] code 0x%08X\r\n", frame[4]);
                kprintf("this is frame[3] code 0x%08X\r\n", frame[3]);
                kprintf("this is frame[2] code 0x%08X\r\n", frame[2]);
                kprintf("this is frame[1] code 0x%08X\r\n", frame[1]);
                kprintf("this is frame[0] code 0x%08X\r\n", frame[0]);
                kprintf("\n\nthis is swi version op code 0x%08X\r\n", swi);
                kprintf("\n\nthis is val of swi 0x%08X\r\n", &swi);

               // return;
               // syscall_dispatch(swi,args);
        }*/
     /* 3) Decode what system call was requested by examining opcode,
     * 4) Call syscall_dispatch() with the syscall number and any
     *    passed arguments, and
     * 5) On return from syscall_dispatch(), setup proper return to
     *    instruction after SWI call, with return value in place.
     */

   
    

      
    /* If not an IRQ or SWI, fall through to generic exception handler */
    kprintf("\r\n\r\nXINU Exception [%s]\r\n", trap_names[cause]);

    kprintf("Faulting address: 0x%08X\r\n", frame[14]);
    kprintf("Faulting SPSR:    0x%08X\r\n", frame[15]);

    kprintf("[0x%08X] r12:0x%08X   lr:0x%08X\r\n",
            frame + CTX_IP, frame[CTX_IP], frame[13]);
    kprintf("[0x%08X]  r8:0x%08X   r9:0x%08X  r10:0x%08X  r11:0x%08X\r\n",
            frame + CTX_R8,
            frame[CTX_R8], frame[CTX_R9], frame[CTX_R10], frame[CTX_R11]);
    kprintf("[0x%08X]  r4:0x%08X   r5:0x%08X   r6:0x%08X   r7:0x%08X\r\n",
            frame + CTX_R4,
            frame[CTX_R4], frame[CTX_R5], frame[CTX_R6], frame[CTX_R7]);
    kprintf("[0x%08X]  r0:0x%08X   r1:0x%08X   r2:0x%08X   r3:0x%08X\r\n",
            frame + CTX_R0,
            frame[CTX_R0], frame[CTX_R1], frame[CTX_R2], frame[CTX_R3]);
    
    while (1)
        ;                       /* forever */
}
