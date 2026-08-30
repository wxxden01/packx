#include <stdio.h>

#include "path_builder.h"
#include "mirror.h"
#include "packages.h"

package_t pkg_data;

int packx_install(int argc, char **argv)
{
    // Nombre d'arguments attendue
    if (argc != 3)
    {
        printf("Mauvaise utilisation de la commande! Cette commande doit être suivit d'un nom de paquet.\n");
        return -1;
    }

    // Vérifie que le paquet n'est pas installé
    if (pkg_finder(2, argv[2], &pkg_data) == -1)
    {
        printf("Le paquet %s est déjà installé sur cette machine!\n", argv[2]);
        return -1;
    }
    
    // Vérifie la config du mirroir
    if (mirror_check() != 0)
    {
        return -1;
    }

    // Vérifier si l'archive existe sur le mirroir
    if (pkg_finder(2, argv[2], &pkg_data) == -1)
    {
        printf("Le paquet %s n'est pas disponible sur ce miroir ou n'existe pas!\nVérifier l'hortograhe et réssayer!\n", argv[2]);
        return -1;
    }
    printf("Paquet disponible sur le miroir!\n");

    // Télécharger l'archive
    char *mirror = select_mirror();
    if (mirror == NULL)
    {
        return -1;
    }

    if (download_from_mirror(mirror, pkg_data.full_name) != 0)
    {
        printf("erreur dw repo\n");
        return -1;
    }
    
    return 1;
}