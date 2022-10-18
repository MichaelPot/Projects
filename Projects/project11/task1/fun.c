
#include <stdio.h>
#include<string.h>
#include<stdlib.h>

int fun(char *buf, unsigned len)
{
    char crashme[2] = {0x34, 0x32};
    if(!strncmp(buf, crashme, 2)){
        abort(); //Bug
    }
    printf("Have a nice day!\n");
    return 0;
}
