#include <stdio.h>

#include "mirror.h"
#include "packages.h"

int packx_install(int argc, char **argv)
{
    // Nombre d'arguments attendue
    if (argc != 3)
    {
        printf("Mauvaise utilisation de la commande! Cette commande doit être suivit d'un nom de paquet.\n");
        return -1;
    }

    // Vérifie que le paquet n'est pas installé
    if (!db_pkg_reader(1, argv[2]))
    {
        printf("Le paquet %s est déjà installé sur cette machine!\n", argv[2]);
        return -1;
    }
    
    // Vérifie la config du mirroir
    if (!mirror_check())
    {
        return -1;
    }

    // Vérifier si l'archive existe sur le mirroir
    if (db_pkg_reader(2, argv[2]) == 1)
    {
        printf("Le paquet %s n'est pas disponible sur ce miroir ou n'existe pas!\nVérifier l'hortograhe et réssayer!\n", argv[2]);
        return -1;
    }
    printf("Paquet disponible sur le miroir!\n");

    // Télécharger l'archive
    
    return 1;
}