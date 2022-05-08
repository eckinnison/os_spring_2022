/**
 * @file device.h 
 *
 * Contains all definitions relating to the Xinu device subsystem.
 *
 */
/* Embedded Xinu, Copyright (C) 2009.  All rights reserved. */

/* Device table declarations */
#ifndef _DEVICE_H_
#define _DEVICE_H_

/**
 * Check that device id is between 0 and NDEVS. 
 *
 * @param f id number to test
 */
#define isbaddev(f)  ( !(0 <= (f) && (f) < NDEVS) )

/* Standard driver functions */
devcall open(int, ...);
devcall close(int);
devcall read(int, void *, uint);
devcall write(int, const void *, uint);
devcall getc(int);
devcall putc(int, char);
devcall seek(int, uint);
devcall control(int, int, long, long);
syscall getdev(const char *);

/* Device table entry */
typedef struct dentry
{
    int num;
    int minor;
    char *name;
    devcall (*init)(struct dentry *);
    devcall (*open)(struct dentry *, ...);
    devcall (*close)(struct dentry *);
    devcall (*read)(struct dentry *, void *, uint);
    devcall (*write)(struct dentry *, const void *, uint);
    devcall (*seek)(struct dentry *, long);
    devcall (*getc)(struct dentry *);
    devcall (*putc)(struct dentry *, char);
    devcall (*control)(struct dentry *, int, long, long);
    void *csr;
    void (*intr)(void);
    uchar irq;
} device;

extern const device devtab[];   /* one entry per device */

/* Device name definitions */

#define SERIAL0     0           /* type uart     */

/* Control block sizes */
#define NUART 1

#define DEVMAXNAME 20
#define NDEVS 1

#endif                          /* _DEVICE_H_ */
