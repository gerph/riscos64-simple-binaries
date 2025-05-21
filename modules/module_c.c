/*******************************************************************
 * File:     veneer
 * Purpose:  Entries for the C module.
 * Author:   Gerph
 * Date:     21 May 2025
 ******************************************************************/

/* This is PURELY a simple test to show that we can link the module
   and that we have sensible relocations. */

#include <assert.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "swis.h"
#include "swis_os.h"

/* Define this to debug this file */
//#define DEBUG


#ifdef DEBUG
#define dprintf if (1) printf
#else
#define dprintf if (0) printf
#endif


/* Tests for relocations */
int myprint(char *str)
{
    int n = 0;
    os_write0(str);
    os_newline();

    return n;
}

void call_1(void)
{
    myprint("call_1 called");
}

void call_2(void)
{
    myprint("call_2 called");
}

typedef void (*func_f)(void);

func_f funcs[] = {
    call_1,
    call_2,
};

int number = 23;
int *number_p = &number;

void test_reloc(void)
{
    myprint("Starting relocation test...");
    for (int i=0; i<sizeof(funcs) / sizeof(funcs[0]); i++)
    {
        funcs[i]();
    }
    printf("number = %i ; number_p = %p ; *number_p = %i\n", number, number_p, *number_p);
    assert(number == *number_p);
}



/***************************************************************************
 * Function:     Mod_Init
 * Description:  Initialise the module, setting up vectors, callbacks and
 *               any other parts of the system necessary for the module to
 *               function.
 * Parameters:   tail        = pointer to command line (control terminated)
 *               podule_base = address of podule module was started from, or
 *                             NULL if none
 *               pw          = private word for module
 * On exit:      Return NULL for successful initialisation, or a pointer to
 *               an error block if the module could not start properly.
 **************************************************************************/
_kernel_oserror *Mod_Init(const char *tail, int podule_base, void *pw)
{
    printf("Module initialised!\n");
    return NULL;
}


/***************************************************************************
 * Function:     Mod_Final
 * Description:  Finalise the module, shutting down any systems necessary,
 *               freeing vectors and releasing workspace
 * Parameters:   fatal       = fatality indicator; 1 if fatal, 0 if
 *                             reinitialising
 *               podule_base = address of podule module was started from, or
 *                             NULL if none
 *               pw          = private word for module
 * On exit:      Return 0 for successful finalisation, or a pointer to an
 *               error block if module was not shutdown properly.
 **************************************************************************/
_kernel_oserror *Mod_Final(int fatal, int podule_base, void *pw)
{
    printf("Module finalising\n");
    return NULL;
}

/***************************************************************************
 * Description:  Star command and help request handler routines.
 * Parameters:   arg_string = pointer to argument string (control
 *                            terminated), or output buffer
 *               argc       = number of arguments passed
 *               number     = command number (see CMD_* definitions below)
 *               pw         = private word for module
 * On exit:      If number indicates a help entry:
 *                 To output, assemble zero terminated output into
 *                 arg_string, and return help_PRINT_BUFFER to print it.
 *                 To stay silent, return NULL.
 *                 To given an error, return an error pointer.
 *                 [In this case, you need to cast the 'const' away]
 *               If number indicates a configure option:
 *                 If arg_string is arg_STATUS, then print status, otherwise
 *                 use argc and arg_string to set option.
 *                 Return NULL for no error.
 *                 Return one of the four error codes below (configure_*)
 *                 for a generic error message.
 *                 Return an error pointer for a custom error.
 *               If number indicates a command entry:
 *                 Execute the command given by number, and arg_string.
 *                 Return NULL on success,
 *                 Return a pointer to an error block on failure.
 **************************************************************************/
_kernel_oserror *Mod_Command(const char *arg_string, int argc, int number,
                             void *pw)
{
  switch (number)
  {
    case 0:
      printf("* command called\n");
      test_reloc();
      break;
  }
  return NULL;
}

/***************************************************************************
 * Description:  SWI handler routine. All SWIs for this module will be
 *               passed to these routines.
 * Parameters:   number = SWI number within SWI chunk (i.e. 0 to 63)
 *               r      = pointer to register block on entry
 *               pw     = private word for module
 * On exit:      Return NULL if SWI handled sucessfully, setting return
 *               register values (r0-r9) in r.
 *               Return error_BAD_SWI for out of range SWIs.
 *               Return an error block for a custom error.
 **************************************************************************/
_kernel_oserror *SWI_Call(int number, _kernel_swi_regs *r, void *pw)
{
    printf("SWI call\n");
    return NULL;
}

