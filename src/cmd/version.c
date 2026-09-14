#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "has_sudo.h"
#include "version.h"
#include "packages.h"
#include "packx_color.h"

#define PATH_MAX_LEN 256

int packx_version(int argc, char **argv)
{
    // Case 1 : L'utilisateur tape juste "packx version" (2 arguments : argv[0] et argv[1])
    if ((sudo(argv[0]) && argc == 3) || (!sudo(argv[0]) && argc == 2))
    {
        printf(SUCCES "PACKX version : %s\n" NORMAL, PACKX_VERSION);
        return 0;
    }
    else
    {
        printf(WARNING "Mauvaise utilisation de la commande 'version'\nUtilisation : pack -v\n" NORMAL);
        return -1;
    }

    return 0;
}