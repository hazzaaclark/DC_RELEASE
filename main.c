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

static char* ROM_BUFFER(const char* RELEASE, char* BUFFER)
{
    strncpy(BUFFER, RELEASE + 3, 16);
    BUFFER[16] = '\0';
    return BUFFER;
}

/* AFTER THE INTIAL ROM STACK INSTANTIATION */
/* THE PROGRAM WILL BEGIN TO SCAN THROUGH THE HEADER TO EVALUATE */ 
/* THE RELEASE DATE BASED ON THE BUFFER */

static void ROM_PROC_OPTION(const char* RELEASE) 
{
    char RELEASE_BUFFER[17];
    ROM_BUFFER(RELEASE, RELEASE_BUFFER);
    printf("Domestic Release Date: %s\n", RELEASE_BUFFER);
}

/* A REALLY SCUFFED CHECK TO DETERMINE WHETHER THERE IS ANY AND ALL */
/* LEGIBLE WHITESPACE IN BETWEEN CHARS */

/* THIS IS BY ASSUMING AN ARBITRARY SIZE RESPECTIVE TO THE RELEASE DATE CHAR */
/* THEN EVALUATING THE LENGTH */

static int IS_VALID(const char* VALUE) 
{
    for (size_t i = 0; i < 16; ++i) 
    {
        if (i % 3 != 2 && !(VALUE[i] == ' ' || (VALUE[i] >= '0' && VALUE[i] <= '9'))) 
        {
            return 0; 
        }
    }

    return 1; 
}


int main(int argc, char *argv[]) 
{
    struct ROM_OPTION* ROM_BASE;

    /* ASSUME THAT ALL OF THE CORRECT COMMAND LINE ARGS ARE BEING PROVIDED */

    if (argc != 2) 
    {
        printf("Usage: %s <ROM file path>\n", argv[0]);
        return 1;
    }

    FILE *ROM_FILE = fopen(argv[1], "rb");
    if (ROM_FILE == NULL) 
    {
        printf("Error: Unable to open ROM file.\n");
        return 1;
    }

    /* SEEK INTO THE CONTENTS OF THE PROVIDED FILE */
    /* THIS WILL BE UNDER THE GUISE OF US NOT KNOWING WHAT THE DREAMCAST GDI'S */
    /* OFFSET IS TO BEGIN WITH */

    /* FROM THERE, ALLOCATE THE DESIGNATED MEMORY FROM THE STRUCTURE TO ASSERTAIN THE START AND END OFFSETS */

    fseek(ROM_FILE, 0, SEEK_SET);
    ROM_BASE = malloc(sizeof(ROM_OPTION));

    ROM_BASE->ROM_BYTES = fread(ROM_BASE->ROM_FILE_HEADER, 1, MAX_ROM_HEADER_SIZE, ROM_FILE);

    if (ROM_BASE->ROM_BYTES != MAX_ROM_HEADER_SIZE) 
    {
        printf("Error: Failed to read ROM header.\n");
        fclose(ROM_FILE);
        return 1;
    }

    fclose(ROM_FILE);
    free(ROM_FILE);

    ROM_BASE->ROM_START = 0; 
    ROM_BASE->ROM_END = MAX_ROM_HEADER_SIZE - 16;

    /* ITERATE THROUGH ALL RESPECTIVE ELEMENTS OF THE HEADER */
    /* INITIALLY, THE RELEASE CHAR WILL ACCOUNT FOR A 17 BIT BUFFER TO ACCOMODATE */
    /* INTEGER OVERFLOW */

    for (size_t OFFSET = ROM_BASE->ROM_START; OFFSET <= ROM_BASE->ROM_END; ++OFFSET) 
    {
        char RELEASE[17];
        memcpy(RELEASE, ROM_BASE->ROM_FILE_HEADER + OFFSET, 16);
        RELEASE[16] = '\0';

        if (IS_VALID(RELEASE)) 
        {
            ROM_PROC_OPTION(RELEASE);
            return 0; 
        }
    }

    printf("Error: Unable to find a valid release date in the ROM header.\n");

    return 1;
}
