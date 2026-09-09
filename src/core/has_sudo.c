#include <string.h>

#include "has_sudo.h"

int sudo(char *first_arg)
{
    if (!strcmp(first_arg, "sudo"))
    {
        return -1;
    }
    
    return 0;
}