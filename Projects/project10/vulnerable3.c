
#include <stdio.h>
#include <stdlib.h>

/* this header exports functions to execute the exploit and read/write
 * to/from it */
#include "comms.h"

void sensitive_function(unsigned int arg)
{
    if (arg == 0xf005ba11) {
        puts("Full points! (Hey wait a minute.. How did you get here?)");
        exit(EXIT_SUCCESS);
    }
}

void buffer_overflow()
{
    char buffer[16];
    read_from_exploit(buffer, 48);
}

static char greeting[128];

int main()
{
    int local = 5;

    exec_exploit("./exploit3.x");

    read_from_exploit(greeting, sizeof(greeting)-1);

    write_to_exploit(greeting);

    puts("Waiting for input...");
    buffer_overflow();
    
    puts("Zero points. (Program terminated successfully; overflow failed.)");

    return EXIT_SUCCESS;
}
