/* COPYRIGHT (C) HARRY CLARK 2024 */

/* DREAMCAST ROM TOOLKIT */

/* THIS FILE PERTAINS TOWARDS THE FUNCTIONALTIY REGARDING */
/* ROM FILES AND THEIR UNDERLYING ARCHITECTURE */

/* SUCH IS THE CASE WITH THIS LITTLE TOOL, THIS FILE WILL BE THE */
/* FOR ALL OF THE INFORMATION PERTAINING TOWARDS THE RELEASE DATE ON THE HEADER */

/* NESTED INCLUDES */

#include "ROM.h"

#undef USE_ROM_PRAGMAS

/* ALLOCATE THE DESIGNATED MEMORY FOR THE ROM BUFFER */
/* ASSUME A STACK SIZE OF 16 BYTES TO DISCERN THE SIZE OF THE BUFFER INITIALLY */

char ROM_BUFFER(const char* RELEASE, char* BUFFER)
{
    struct ROM_OPTION* ROM_BASE;
    strncpy(BUFFER, RELEASE, 16);

    ROM_BASE->RELEASE_BUFFER[16] = sizeof(ROM_BASE->RELEASE_BUFFER) / sizeof(ROM_BASE->RELEASE_BUFFER[0]);
    return BUFFER;
}

/* AFTER THE INTIAL ROM STACK INSTANTIATION */
/* THE PROGRAM WILL BEGIN TO SCAN THROUGH THE HEADER TO EVALUATE */ 
/* THE RELEASE DATE BASED ON THE BUFFER */

void ROM_PROC_OPTION(const char* RELEASE)
{
    struct ROM_OPTION* ROM_BASE;
    ROM_BUFFER(RELEASE, sizeof(ROM_BASE->RELEASE_BUFFER));

    fprintf(stdout, "Domestic Release Date: %s\n", ROM_BASE->RELEASE_BUFFER);
}

int main(int argc, char* argv[])
{
    struct ROM_OPTION* ROM_BASE;

    /* CHECK TO SEE IF THE CORRECT ARGS ARE PRESENT */

    if(argc != 2)
    {
        fprintf("Usage: %s <ROM file path>\n", argv[0]);
        return EXIT_FAILURE;
    }

    ROM_BASE->FILES.ROM_FILE = fopen_s(argv[1], "rb");
    
    if(ROM_BASE->FILES.ROM_FILE == NULL)
    {
        fprintf(stderr, "No Dreamcast ROM file was found\n");
        return EXIT_FAILURE;
    }
}
