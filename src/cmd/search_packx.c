#include <stdio.h>
#include <stdlib.h>

// contient la fonction package_existe()
#include "packages.h"

#define PATH_MAX_LEN 256

int packx_search(int argc, char **argv)
{
    if (argc > 2)
    {
        const char *home = getenv("HOME");
        if (!home) return -1;

        char db_file[PATH_MAX_LEN];
        snprintf(db_file, sizeof(db_file), "%s/.packx/installed.db", home);

        if (db_pkg_reader(db_file, argv[2]) == 0)
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