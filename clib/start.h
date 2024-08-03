/*******************************************************************
 * File:        start.h
 * Purpose:     Entry point for RISC OS code
 * Author:      Gerph
 * Date:        06 Jul 2024
 ******************************************************************/

#ifndef START_H
#define START_H

#include <stdint.h>

int start(const char *cli, uint64_t ramlimit, uint8_t *starttime_quin);

#endif
