#include <stdio.h>

// contient la fonction package_existe()
#include "packages.h"

int packx_search(int argc, char **argv)
{
    if (argc > 2)
    {
        // char pkg_name = argv[2];
        if (package_exist(argv[2]))
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