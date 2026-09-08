#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "has_sudo.h"
#include "packages.h"
#include "packx_color.h"

#define PATH_MAX_LEN 256

int packx_search(int argc, char **argv)
{
    if ((sudo(argv[0]) && argc != 4) || (!sudo(argv[0]) && argc != 3))
    {
        printf(WARNING "Mauvaise utilisation de la commande! 'packx search <pkg>'\n" NORMAL);
        return -1;
    }

    char pkg_selected[256];

    // Check if argc has enough elements before accessing argv
    if (sudo(argv[0])) {
        strncpy(pkg_selected, argv[3], sizeof(pkg_selected) - 1);
        pkg_selected[sizeof(pkg_selected) - 1] = '\0';
    } else {
        strncpy(pkg_selected, argv[2], sizeof(pkg_selected) - 1);
        pkg_selected[sizeof(pkg_selected) - 1] = '\0';
    }

    package_t pkg;
    if (pkg_finder(1, pkg_selected, &pkg) != 0)
    {
        printf("Le paquet %s n'a pas été trouvé!\n", pkg_selected);
        return -1;
    }
    printf("Le paquet %s à bien été trouvé!\n", pkg_selected);

    return 0;
}