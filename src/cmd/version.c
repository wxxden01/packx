#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "version.h"
#include "packages.h"

#define PATH_MAX_LEN 256

int packx_version(int argc, char **argv)
{
    // Case 1 : L'utilisateur tape juste "packx version" (2 arguments : argv[0] et argv[1])
    if (argc == 2)
    {
        printf("PACKX version : %s\n", PACKX_VERSION);
        return 0;
    }
    else
    {
        const char *pkg_target = argv[2];

        // On passe full_path (chemin complet) et le nom du paquet recherché
        if (db_pkg_reader(1, pkg_target) == 1)
        {
            printf("Paquet %s non trouvé!\n", argv[2]);
            return 1;
        }
        return 0;
    }

    return 0;
}