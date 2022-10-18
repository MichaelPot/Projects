
#include <stdio.h>
#include <stdlib.h>

/* this header exports functions to execute the exploit and read/write
 * to/from it */
#include "comms.h"


void buffer_overflow()
{
    char buffer[16];
    read_from_exploit(buffer, 512);
}

static char greeting[128];

int main()
{
    int local = 5;

    exec_exploit("./exploit4.x");

    read_from_exploit(greeting, sizeof(greeting)-1);

    write_to_exploit(greeting);

    puts("Waiting for input...");
    buffer_overflow();
    
    puts("Zero points. (Program terminated successfully; overflow failed.)");

    return EXIT_SUCCESS;
}
