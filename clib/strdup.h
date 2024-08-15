/*******************************************************************
 * File:     str.h
 * Purpose:  String utilities
 * Author:   Justin Fletcher
 * Date:     30 Jul 1997
 ******************************************************************/

#ifndef STR_H
#define STR_H

/*********************************************** <c> Gerph *********
 Function:     strdup
 Description:  Copy a string into a new block of memory
 Parameters:   x-> string to copy
 Returns:      pointer to new copy of string, or NULL if failed
 ******************************************************************/
char *strdup(const char *x);

/*********************************************** <c> Gerph *********
 Function:     strndup
 Description:  Duplicate a string to a particular length
 Parameters:   str-> string to copy
               n = number of CHARACTERS to copy
 Returns:      pointer to new string
 ******************************************************************/
char *strndup(const char *str,size_t n);

/*********************************************** <c> Gerph *********
 Function:     stricmp
 Description:  Case insensitive comparison
 Parameters:   str1 = one string
               str2 = the other one
 Returns:      <0 if str1 < str2
               >0 if str1 > str2
               =0 if str1 = str2
 ******************************************************************/
int stricmp(const char *str1,const char *str2);


#ifdef FORTIFY
/* Label the callers of these functions */
char *strdup_label(char const *x, const char *file, int line);
char *strndup_label(char const *x, int n, const char *file, int line);
#define strdup(x)       strdup_label((x), __FILE__, __LINE__)
#define strndup(x, y)   strndup_label((x), (y), __FILE__, __LINE__)
#endif

#endif
