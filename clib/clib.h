/*******************************************************************
 * File:        clib
 * Purpose:     C library maintenance
 * Author:      Gerph
 * Date:        25 May 2025
 ******************************************************************/

#ifndef CLIB_H
#define CLIB_H

/*************************************************** Gerph *********
 Function:      _clib_internalinit
 Description:   Internal initialisation of the C library modules
                We just set up the library initialisations that we
                need, so that each library is in a consistent state.
                Although most variables could be empty, we might
                have some left over data from having been saved out
                of memory. For that reason, and to allow us to be
                restarted cleanly if we do that in the future, we
                try to ensure that each module's initialisation
                is called.
 Parameters:    none
 Returns:       none
 ******************************************************************/
void _clib_internalinit(void);


/*************************************************** Gerph *********
 Function:      _clib_finalise
 Description:   Shut down all our C libraries, triggering atexit if needed.
 Parameters:    none
 Returns:       none
 ******************************************************************/
void _clib_finalise(void);


#endif
