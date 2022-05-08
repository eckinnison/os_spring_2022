/* device.c */

#include <xinu.h>

extern devcall ioerr(void);
extern devcall ionull(void);

/* device independent I/O switch */

const device devtab[NDEVS] = {
/**
 * Format of entries is:
 * dev-number, minor-number, dev-name,
 * init, open, close,
 * read, write, seek,
 * getc, putc, control,
 * dev-csr-address, intr-handler, irq
 */

/* SERIAL0 is uart */
    { 0, 0, "SERIAL0",
     (void *)uartInit, (void *)ionull, (void *)ionull,
     (void *)uartRead, (void *)uartWrite, (void *)ioerr,
     (void *)uartGetc, (void *)uartPutc, (void *)ionull,
     (void *)0x3F201000, (void *)uartHandler, 57 }
};
