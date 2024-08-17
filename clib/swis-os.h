#ifndef SWIS_OS_H
#define SWIS_OS_H

#include "kernel.h"

#define os_writec __os_writec
#define os_readc __os_readc
#define os_screenmode __os_screenmode
#define colourtrans_setgcol __colourtrans_setgcol
#define draw_fill __draw_fill
#define os_setcolour __os_setcolour
#define os_inkey __os_inkey
#define os_write0 __os_write0
#define os_writen __os_writen
#define os_newline __os_newline
#define os_generateerror __os_generateerror
#define os_readescapestate __os_readescapestate
#define os_module __os_module
#define os_heap __os_heap
#define os_byte_out1 __os_byte_out1



void os_writec(char c);
char os_readc(void);
void os_screenmode(int reason, uint32_t modespec);
void colourtrans_setgcol(uint32_t palentry, uint32_t flags, uint32_t gcol);
void draw_fill(int32_t *path, uint32_t style, int32_t *matrix, int32_t flatness);
void os_setcolour(uint32_t flags, uint32_t gcol);
int os_inkey(int32_t value);
void os_write0(const char *str);
void os_writen(const char *str, int n);
void os_newline(void);
void os_generateerror(_kernel_oserror *err);
int os_readescapestate(void);

_kernel_oserror *os_heap(int heapop, void *heapbase, void *ptr, int size, void **newptr);
_kernel_oserror *os_module(int moduleop, void *ptr, int size, void **newptr);

// OS_Byte with simple semantics
// int os_byte_out1(r0, r1, r2) => r1 value on return
int os_byte_out1(int r0, int r1, int r2);

/* Using OS_WriteI makes no select really in AArch64 */
#define os_cls() os_writec(12)

#endif