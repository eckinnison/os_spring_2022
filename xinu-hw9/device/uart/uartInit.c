#include <xinu.h>

struct uart serial_port;

extern interrupt uartHandler(void);

devcall uartInit(device *devptr)
{

    volatile struct pl011_uart_csreg *regptr =
        (struct pl011_uart_csreg *)devptr->csr;

    serial_port.csr = regptr;
    // Initialize INPUT buffer
    serial_port.isema = semcreate(0);
    serial_port.iflags = 0;
    serial_port.istart = 0;
    serial_port.icount = 0;

    if (isbadsem(serial_port.isema))
        return SYSERR;
    // Initialize OUTPUT buffer
    serial_port.osema = semcreate(UART_OBLEN);
    serial_port.oflags = 0;
    serial_port.ostart = 0;
    serial_port.ocount = 0;
    serial_port.oidle = 1;

    if (isbadsem(serial_port.osema))
        return SYSERR;

    udelay(1500);

    regptr->cr = 0;

    while (regptr->fr & PL011_FR_BUSY)
    {
    }

    regptr->lcrh &= ~PL011_LCRH_FEN;

    // Setup Interrupts
    regptr->icr = (PL011_ICR_OEIC |
                   PL011_ICR_BEIC |
                   PL011_ICR_PEIC |
                   PL011_ICR_FEIC |
                   PL011_ICR_RTIC |
                   PL011_ICR_TXIC | 0 | 0 | PL011_ICR_CTSMIC);
    regptr->lcrh = PL011_LCRH_WLEN_8BIT;
    regptr->imsc = PL011_IMSC_RXIM | PL011_IMSC_TXIM;
    regptr->cr = PL011_CR_RXE | PL011_CR_TXE | PL011_CR_UARTEN;

    interruptVector[IRQ_PL011] = (void *)uartHandler;


    return OK;
}
