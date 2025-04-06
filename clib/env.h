/*******************************************************************
 * File:        env
 * Purpose:     Program environment handlers
 * Author:      Gerph
 * Date:        2025-04-06
 ******************************************************************/

#ifndef ENV_H
#define ENV_H

/*************************************************** Gerph *********
 Function:      _env_init
 Description:   Initialise our program environment handlers
 Parameters:    none
 Returns:       none
 ******************************************************************/
void _env_init(void);

/*************************************************** Gerph *********
 Function:      __env_restore
 Description:   Restore parent program environment handlers
 Parameters:    none
 Returns:       none
 ******************************************************************/
void _env_restore(void);

#endif
