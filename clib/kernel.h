#ifndef KERNEL_H
#define KERNEL_H

#include <stdint.h>

typedef struct _kernel_oserror_s {
    uint32_t errnum;
    char errmess[252];
} _kernel_oserror;

typedef struct _kernel_swi_regs {
    int32_t r[10];
} _kernel_swi_regs;

_kernel_oserror *_kernel_swi(int swinum, _kernel_swi_regs *in, _kernel_swi_regs *out);

int _kernel_oscli(const char *cli);
_kernel_oserror *_kernel_last_oserror(void);

int _kernel_escape_seen(void);

_kernel_oserror *_kernel_setenv(const char *var, const char *val);
_kernel_oserror *_kernel_getenv(const char *var, char *buf, unsigned size);


/*************************************************** Gerph *********
 Function:      _kernel_backtrace
 Description:   Report the backtrace to VDU
 Parameters:    none
 Returns:       none
 ******************************************************************/
void _kernel_backtrace(void);

typedef struct {
   uint64_t fp; /* current FP */
   uint64_t sp; /* current SP */
   uint64_t lr; /* Where we were */
   uint64_t pc; /* Where we are */
} _kernel_unwindblock;

/*************************************************** Gerph *********
  Function:      _kernel_unwind
  Description:   Unwind the stack; of return the current state
  Parameters:    inout-> the unwind block to step up from
                 language-> where to store the language name pointer
  Returns:       >0 if got a stack entry
                 0 if we reached the end of the backtrace
                 <0 if something went wrong
  ******************************************************************/
int _kernel_unwind(_kernel_unwindblock *inout, char **language);

/*************************************************** Gerph *********
 Function:      _kernel_procname
 Description:   For a given PC, return the procedure name
 Parameters:    pc = the address to search
 Returns:       Pointer to the function name, or NULL if none known
 ******************************************************************/
const char *_kernel_procname(uint64_t pc);

#endif

