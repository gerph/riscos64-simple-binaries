/* Internal fopen functions */

#include <stdio.h>
#include <stdbool.h>

#ifndef IO_FILE_FOPEN_H
#define IO_FILE_FOPEN_H

/*************************************************** Gerph *********
 Function:      _fopen
 Description:   Internal file open function
 Parameters:    filename-> the file to open
                mode = the file mode to use
                fh-> the file handle we're opening into (which has been cleared)
 Returns:       true on success, false on failure
 ******************************************************************/
bool _fopen(const char *filename, const char *mode, FILE *fh);

/*************************************************** Gerph *********
 Function:      _fclose
 Description:   Internal close for the file, which does not unlink.
                The file is closed / reset to its original state.
 Parameters:    fh-> the file handle to close
 Returns:       none
 ******************************************************************/
void _fclose(FILE *fh);

#endif
