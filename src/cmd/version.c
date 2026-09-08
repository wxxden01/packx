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
        printf("PACKX version : %s\n", PACKX_VERSION);
        return 0;
    }
    else if ((sudo(argv[0]) && argc > 4) || (!sudo(argv[0]) && argc > 3))
    {
        printf("Mauvaise utilisation de la commande 'version'\nUtilisation : pack -v <pkg>\n");
        return -1;
    }
    else
    {
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
        // On passe full_path (chemin complet) et le nom du paquet recherché
        if (pkg_finder(1, pkg_selected, &pkg) != 0)
        {
            printf(ERROR "Paquet %s non trouvé!\n"FILE_COLOR"%s"NORMAL" ne semble pas être installé sur votre machine!\n" NORMAL, pkg_selected, pkg_selected);
            return 1;
        }
        printf(SUCCES "%s version : %s\n" NORMAL, pkg_selected, pkg.version);
        return 0;
    }

    return 0;
}