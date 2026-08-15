#include <stdio.h>
#include <stdlib.h>

// contient la fonction package_existe()
#include "packages.h"

#define PATH_MAX_LEN 256

int packx_search(int argc, char **argv)
{
    if (argc > 2)
    {
        if (db_pkg_reader(1, argv[2]) == 0)
        {
            printf("Le paquet %s à bien été trouvé!\n", argv[2]);
            return 0;
        }
        printf("Le paquet %s n'a pas été trouvé!\n", argv[2]);
        return 0;
    }
    printf("Mauvaise utilisation de la commande! 'packx search <pkg>'\n");
    return 1;
}