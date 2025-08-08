#ifndef SWIS_OS_H
#define SWIS_OS_H

#include <stdint.h>
#include "kernel.h"

/* Define this to control whether we use inline SWIs or functions */
//#define __INLINE_SWIS_OS


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
#define os_readmonotonictime __os_readmonotonictime
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
_kernel_oserror *os_write0end(const char *str, const char **endp); /* Returns the end pointer as well */
_kernel_oserror *os_writen(const char *str, int n);
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

/* Inline definitions - probably not worthwhile, but we have the option */
#if defined(__riscos64) && defined(__GNUC__) && defined(__INLINE_SWIS_OS)
static inline uint64_t os_readmonotonictime(void)
{
  register uint64_t ret asm("r0");
  __asm __volatile (
            "mov\tx10, 0x42\n"
            "orr\tx10, x10, 0x20000\n"
            "svc\t0x00000000\n"
            "csel\tx0, x0, xzr, VC\n"
            :   "=r" (ret)
            :
            :   "x10"
            );
    return ret;
}

static inline _kernel_oserror *os_write0(const char *str)
{
  register const char *astr asm("r0") = str;
  register _kernel_oserror *err asm("r0");
  __asm __volatile ("\n"
        "MOV     x10, #0x2                   // OS_Write0\n"
        "ORR     x10, x10, #0x20000\n"
        "SVC     #0\n"
        "CSEL    x0, x0, xzr, VS\n"
        :       "+r" (err)
        :       "r" (astr)
        :       "x10"
    );
  return err;
}

static inline _kernel_oserror *os_newline(void)
{
  register _kernel_oserror *err asm("r0");
  __asm __volatile ("\n"
        "MOV     x10, #0x3                   // OS_NewLine\n"
        "ORR     x10, x10, #0x20000\n"
        "SVC     #0\n"
        "CSEL    x0, x0, xzr, VS\n"
        :       "+r" (err)
        :
        :       "x10"
    );
  return err;
}

#else
uint64_t os_readmonotonictime(void);
_kernel_oserror *os_write0(const char *str);
_kernel_oserror *os_newline(void);
#endif

#endif
