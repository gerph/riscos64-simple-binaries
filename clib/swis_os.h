#ifndef SWIS_OS_H
#define SWIS_OS_H

#include "kernel.h"

#define os_writec __os_writec
#define os_readc __os_readc
#define os_screenmode __os_screenmode
#define colourtrans_setgcol __colourtrans_setgcol
#define draw_fill __draw_fill
#define os_setcolour __os_setcolour
#define os_word __os_word
#define os_inkey __os_inkey
#define os_write0 __os_write0
#define os_write0end __os_write0end
#define os_writen __os_writen
#define os_newline __os_newline
#define os_generateerror __os_generateerror
#define os_readescapestate __os_readescapestate
#define os_module __os_module
#define os_heap __os_heap
#define os_byte_out1 __os_byte_out1
#define os_file2 __os_file2
#define os_file3 __os_file3
#define os_fscontrol2 __os_fscontrol2
#define os_fscontrol3 __os_fscontrol3
#define os_changeenvironment __os_changeenvironment



_kernel_oserror *os_writec(char c);
char os_readc(void);  // -1 for error, -27 for escape
void os_screenmode(int reason, uint32_t modespec);
void colourtrans_setgcol(uint32_t palentry, uint32_t flags, uint32_t gcol);
void draw_fill(int32_t *path, uint32_t style, int32_t *matrix, int32_t flatness);
void os_setcolour(uint32_t flags, uint32_t gcol);
_kernel_oserror *os_word(int32_t op, char reason, char *data);
int os_inkey(int32_t value);
_kernel_oserror *os_write0(const char *str);
_kernel_oserror *os_write0end(const char *str, const char **endp); /* Returns the end pointer as well */
_kernel_oserror *os_writen(const char *str, int n);
_kernel_oserror *os_newline(void);
void os_generateerror(_kernel_oserror *err) __attribute__ ((__noreturn__));
int os_readescapestate(void);
_kernel_oserror *os_file2(int op, const char *filename);
_kernel_oserror *os_file3(int op, const char *filename, int arg1);
_kernel_oserror *os_fscontrol2(int op, const char *filename);
_kernel_oserror *os_fscontrol3(int op, const char *filename, const char *filename2);

_kernel_oserror *os_heap(int heapop, void *heapbase, void *ptr, int size, void **newptr);
_kernel_oserror *os_module(int moduleop, void *ptr, int size, void **newptr);

// OS_Byte with simple semantics
// int os_byte_out1(r0, r1, r2) => r1 value on return
int os_byte_out1(int r0, int r1, int r2);

/* Using OS_WriteI makes no sense really in AArch64 */
#define os_cls() os_writec(12)

_kernel_oserror *os_changeenvironment(int envnumber, intptr_t handler, intptr_t workspace, intptr_t buffer,
                                      intptr_t *old_handler);

#endif
