#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "has_sudo.h"
#include "packages.h"
#include "packx_color.h"

int packx_search(char *target_pkg)
{
    if (target_pkg == NULL)
    {
        printf(WARNING"Mauvaise utilisation de la commande 'search', Aucun paquet spécifié!\n"BOLD"Utilisation : packx -v <pkg>"NORMAL);
        return -1;
    }
    
    if (pkg_installed(target_pkg) != 0)
    {
        printf("Le paquet %s n'a pas été trouvé!\n",target_pkg);
        return -1;
    }
    printf("Le paquet %s à bien été trouvé!\n",target_pkg);

    return 0;
}