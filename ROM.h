/* COPYRIGHT (C) HARRY CLARK 2024 */

/* DREAMCAST ROM TOOLKIT */

/* THIS FILE PERTAINS TOWARDS THE FUNCTIONALTIY REGARDING */
/* ROM FILES AND THEIR UNDERLYING ARCHITECTURE */

/* SUCH IS THE CASE WITH THIS LITTLE TOOL, THIS FILE WILL BE THE */
/* FOR ALL OF THE INFORMATION PERTAINING TOWARDS THE RELEASE DATE ON THE HEADER */

#ifndef ROM
#define ROM

/* SYSTEM INCLUDES */

#include <malloc.h>
#include <stdio.h>
#include <stdlib.h>

#define     MAX_VALUE_LENGTH        128
#define     MAX_ROM_HEADER_SIZE     2048

typedef struct ROM_OPTION 
{
    char* ROM_KEY[MAX_VALUE_LENGTH];
    char* ROM_VALUE[MAX_VALUE_LENGTH];

    const char* RELEASE_DATE;
    char* RELEASE_BUFFER[16];

    size_t ROM_READ_BUFFER;
    size_t ROM_START;
    size_t ROM_END;

} ROM_OPTION;

char(*ROM_BUFFER(const char* RELEASE, char* BUFFER));
void ROM_PROC_OPTION(const char* RELEASE);

#endif
