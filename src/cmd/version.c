#include <stdio.h>

#include "version.h"
#include "packages.h"

int packx_version(int argc, char **argv)
{
    (void)argv;
    // Si la commande n'a pas d'argument on affiche la version de PACKX
    if (argc == 2)
    {
        printf("%s", PACKX_VERSION);
    }
    else
    {
       if (package_exist(argv[2]))
        {
            printf("Version de %s : \n", argv[2]);
            return 0;
        }
        
        printf("%s est introuvable, vérifiez qu'il soit bien installer\n", argv[2]);
    }
    
    return 0;
}