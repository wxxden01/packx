#include <stdio.h>

#include "mirror.h"

int show_config(int argc, char **argv) 
{
    (void)argc;
    (void)argv;
    // afficher le miroir par défault
    char *default_mirror = select_mirror();
    if (default_mirror == NULL)
    {
        return -1;
    }

    printf("Config actuelle de Packx:\n");
    printf("Miroir par défault : %s\n", default_mirror);
    return 0;
}