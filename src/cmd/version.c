#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "has_sudo.h"
#include "version.h"
#include "packages.h"
#include "packx_color.h"

int packx_version(char *target_pkg)
{
    if (target_pkg != NULL)
    {
        printf(WARNING"Mauvaise utilisation la commande, aucun argument n'est attendue ici."NORMAL);
        return -1;
    }
    
    printf(SUCCES "PACKX version : %s\n" NORMAL, PACKX_VERSION);
    return 0;
}