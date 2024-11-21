/*******************************************************************
 * File:        sysvars-init
 * Purpose:     System variables initialisation/finalisation
 * Author:      Gerph
 * Date:        10 Aug 2024
 ******************************************************************/

#ifndef SYSVARS_INIT_H
#define SYSVARS_INIT_H

extern char *__envstring;
extern int __envstringlen;

void __getenv_final(void);

#endif
