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

typedef struct {
   int32_t load, exec;       /* load, exec addresses */
   int32_t start, end;       /* start address/length, end address/attributes */
} _kernel_osfile_block;

typedef struct {
   void * dataptr;       /* memory address of data */
   int32_t nbytes, fileptr;
   int32_t buf_len;
   const char * wild_fld;      /* points to wildcarded filename to match */
} _kernel_osgbpb_block;

#define _KERNEL_NOXBIT (1lu<<31)    /* Always clear the X bit (otherwise always set) */
_kernel_oserror *_kernel_swi(int swinum, _kernel_swi_regs *in, _kernel_swi_regs *out);

int _kernel_oscli(const char *cli);
_kernel_oserror *_kernel_last_oserror(void);

int _kernel_escape_seen(void);

_kernel_oserror *_kernel_setenv(const char *var, const char *val); /* Use NULL to delete */
_kernel_oserror *_kernel_getenv(const char *var, char *buf, unsigned size);

int _kernel_osfind(int op, const char *name);
int _kernel_osfile(int op, const char *name, _kernel_osfile_block *inout);
int _kernel_osgbpb(int op, unsigned handle, _kernel_osgbpb_block *inout);
int _kernel_osargs(int op, unsigned handle, int arg);
int _kernel_osword(int op, int *data);

/* If a function returned a negative error code, and it has also updated the
 * _kernel_last_oserror value, this will be returned:
 */
#define _kernel_ERROR (-2)


#define _kernel_HOST_UNDEFINED    -1
#define _kernel_BBC_MOS1_0         0
#define _kernel_BBC_MOS1_2         1
#define _kernel_BBC_ACW            2
#define _kernel_BBC_MASTER         3
#define _kernel_BBC_MASTER_ET      4
#define _kernel_BBC_MASTER_COMPACT 5
#define _kernel_ARTHUR             6
#define _kernel_RISCOS             6
#define _kernel_SPRINGBOARD        7
#define _kernel_A_UNIX             8

/*************************************************** Gerph *********
 Function:      _kernel_hostos
 Description:   Report the host OS (OS_Byte 0, 1)
 Parameters:    none
 Returns:       6 for RISC OS (https://beebwiki.mdfs.net/OSBYTE_%2600)
 ******************************************************************/
int _kernel_hostos(void);

/*************************************************** Gerph *********
 Function:      _kernel_osrdch
 Description:   OS_ReadC
 Parameters:    none
 Returns:       character, or -1 if error, or -27 if escape
 ******************************************************************/
int _kernel_osrdch(void);

/*************************************************** Gerph *********
 Function:      _kernel_oswrch
 Description:   OS_WriteC
 Parameters:    character
 Returns:       -2 if failure, 0 if success
 ******************************************************************/
int _kernel_oswrch(int c);

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

