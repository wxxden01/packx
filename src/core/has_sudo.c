#include <stdio.h>
#include <string.h>

#include "has_sudo.h"

int sudo(char *first_arg)
{
    printf("%s\n", first_arg);
    if (!strncmp(first_arg, "sudo", 4))
    {
        printf("Pas sudo!\n");   
        return -1;
    }
    printf("Sudo!\n");
    return 0;
}

int is_sudo(int argc, char **argv)
{
    (void)argc;
    if (!strncmp(argv[0], "sudo", 4))
    {
        printf("Pas sudo!\n");   
        return -1;
    }
    printf("Sudo!\n");
    return 0;
}