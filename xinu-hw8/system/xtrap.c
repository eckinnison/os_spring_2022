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
        long swi;
        int c=0;
        long* opcode;
    /* TODO: Implement system calls for Xinu.
     * 1) Recognize when cause of hardware exception is SWI opcode*/

	int i;
	long *ocvar; // Holds opcode variable
        if (cause == ARM_EXCEPTION_SWI){
                //for(int i =0; i <= 16; i++){
                       // kprintf("this is the opcode variable of frame[%d]: 0x%08X\r\n", i, frame[i]);
                //}
                opcode= ((long)frame[14]);
               // kprintf("this is ocode of frame[14]: 0x%08X\r\n", *opcode); 
                swi= (*opcode) & (0xFFFFFF);
                int* my_args;
                //for(int j=0; j<4;j++){
                  //      my_args[j]=frame[j];
                //}
               // kprintf("this is ocode of swi: 0x%06X\r\n", swi);
               // kprintf("this is ocode of *swi: 0x%06X\r\n", *swi);
                frame[14]=frame[14]+4;
                frame[0]= syscall_dispatch(swi, *my_args);
     /* 3) Decode what system call was requested by examining opcode,

        //Write a loop to print the requested system call?
        
        if(frame[12] = 0x0000CE74){ //Not sure if this is the correct frame, but need to find the specified call and call syscall_dispatch
                syscall_dispatch(swi,args); //Something else needs to go inside this call
        }

    / * 4) Call syscall_dispatch() with the syscall number and any
     *    passed arguments, and
     * 5) On return from syscall_dispatch(), setup proper return to
     *    instruction after SWI call, with return value in place.
     */
        
        return;
}
   
    

      
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
