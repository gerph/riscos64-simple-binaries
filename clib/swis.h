#include <stdint.h>
#include "kernel.h"

#include "swi_numbers.h"

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

// OS_Byte with simple semantics
// int os_byte_out1(r0, r1, r2) => r1 value on return
int os_byte_out1(int r0, int r1, int r2);

/* Using OS_WriteI makes no select really in AArch64 */
#define os_cls() os_writec(12)

#define _FLAGS     0x10 /*use with _RETURN() or _OUT()*/
#define _IN(i)     (1U << (i))
#define _INR(i,j)  (~0 << (i) ^ ~0 << (j) + 1)
#define _OUT(i)    ((i) != _FLAGS? 1U << 31 - (i): 1U << 21)
#define _OUTR(i,j) (~0U >> (i) ^ ~0U >> (j) + 1)

_kernel_oserror *_swix (int swi_no, unsigned int, ...);
