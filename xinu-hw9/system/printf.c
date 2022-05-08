/**
 * @file printf.c
 */
/* Embedded Xinu, Copyright (C) 2018. All rights reserved. */

#include <xinu.h>

int putc_helper(int c, int skip)
{
    putc(SERIAL0, c);
}

/**
 * printf: formatted, asynchronous output to UART device.
 *
 * @param format
 *      The format string.
 * @param ...
 *      Arguments matching those in the format string.
 *
 * @return
 *      The number of characters written.
 */
syscall printf(const char *format, ...)
{
    int retval;

    va_list ap;
    va_start(ap, format);
    retval = _doprnt(format, ap, (int (*)(int, int))putc_helper, 0);
    va_end(ap);

    return retval;
}
