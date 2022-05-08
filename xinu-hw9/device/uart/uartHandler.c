/**
 * @file uartHandler.c
 */

/* Embedded Xinu, Copyright (C) 2009, 2013.  All rights reserved. */

#include <xinu.h>

/**
 * @ingroup uarthardware
 *
 * Handle an interrupt request from a PL011 UART.
 */

interrupt uartHandler(void)
{
    uint mis = 0, count = 0;
    uchar c = 0;
    volatile struct pl011_uart_csreg *regptr =
        (struct pl011_uart_csreg *)UART_CSREG;

    /* Check the Masked Interrupt Status register to determine which
     * interrupts have occurred, then handle them.  */
    mis = regptr->mis;
    if (mis & PL011_MIS_TXMIS)
    {
        /* Transmit interrupt is asserted.  If FIFOs are enabled, this
         * happens when the amount of data in the transmit FIFO is less than
         * or equal to the programmed trigger level.  If FIFOs are disabled,
         * this happens if the Tx holding register is empty.  */

        /* Explicitly clear the transmit interrupt.  This is necessary
         * because there may not be enough bytes in the output buffer to
         * fill the FIFO greater than the transmit interrupt trigger level.
         * If FIFOs are disabled, this applies if there are 0 bytes to
         * transmit and therefore nothing to fill the Tx holding register
         * with.  */
        regptr->icr = PL011_ICR_TXIC;

        /* If there are bytes pending in the output buffer, write them to
         * the UART until either there are no bytes remaining or there is no
         * space remaining in the transmit FIFO.  (If FIFOs are disabled,
         * the Tx holding register acts like a FIFO of size 1, so the code
         * still works.)  Otherwise, the UART is now idle, so set the
         * "oidle" flag, which will allow the next call to uartWrite() to
         * start transmitting again by writing a byte directly to the
         * hardware.  */
        if (serial_port.ocount > 0)
        {
            count = 0;
            do
            {
                regptr->dr = serial_port.out[serial_port.ostart];
                serial_port.ostart =
                    (serial_port.ostart + 1) % UART_OBLEN;
                serial_port.ocount--;
                count++;
            }
            while (!(regptr->fr & PL011_FR_TXFF)
                   && (serial_port.ocount > 0));

            /* One or more bytes were successfully removed from the output
             * buffer and written to the UART hardware.  Increment the total
             * number of bytes written to this UART and signal up to @count
             * threads waiting in uartWrite() to tell them there is now
             * space in the output buffer.  */

        }
        if (count)
        {
            signaln(serial_port.osema, count);
        }
        else
        {
            serial_port.oidle = 1;
        }
    }
    if (mis & PL011_MIS_RXMIS)
    {
        /* Receive interrupt is asserted.  If FIFOs are enabled, this
         * happens when the amount of data in the receive FIFO is greater
         * than or equal to the programmed trigger level.  If FIFOs are
         * disabled, this happens when the Rx holding register was filled
         * with one byte.  */

        /* Number of bytes successfully buffered so far.  */
        count = 0;

        /* Read bytes from the receive FIFO until it is empty again.  (If
         * FIFOs are disabled, the Rx holding register acts as a FIFO of
         * size 1, so the code still works.)  */
        do
        {
            /* Get a byte from the UART's receive FIFO.  */
            c = regptr->dr;
            if (serial_port.icount < UART_IBLEN)
            {
                /* There is space for the byte in the input buffer, so add
                 * it and tally one character received.  */
                serial_port.in[(serial_port.istart +
                                serial_port.icount) % UART_IBLEN] = c;
                serial_port.icount++;
                count++;
            }
        }
        while (!(regptr->fr & PL011_FR_RXFE));
        /* The receive interrupt will have been automatically cleared
         * because we read bytes from the receive FIFO until it became
         * empty.  */

        /* Signal threads that are currently waiting in
         * uartRead() for buffered data to become available.  */

        signaln(serial_port.isema, count);
    }

}
