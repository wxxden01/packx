#include <stdio.h>
#include <string.h>

#include "path_builder.h"
#include "mirror.h"
#include "packages.h"
#include "check_hash.h"
#include "has_sudo.h"
#include "packx_color.h"

package_t pkg_data;

int packx_install(int argc, char **argv)
{
    if ((sudo(argv[0]) && argc != 4) || (!sudo(argv[0]) && argc != 3))
    {
        printf(WARNING"Mauvaise utilisation de la commande! Cette commande doit être suivit d'un nom de paquet.\n"NORMAL);
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

    // Vérifie que le paquet n'est pas installé
    if (pkg_finder(1, pkg_selected, &pkg_data) != 0)
    {
        printf(WARNING"Le paquet %s est déjà installé sur cette machine!\n"NORMAL, pkg_selected);
        return -1;
    }

    // Vérifie la config du mirroir
    if (mirror_check() != 0)
    {
        return -1;
    }

    // Vérifier si l'archive existe sur le mirroir
    if (pkg_finder(2, pkg_selected, &pkg_data) == 0)
    {
        printf("Le paquet %s n'est pas disponible sur ce miroir ou n'existe pas!\nVérifier l'hortograhe et réssayer!\n", pkg_selected);
        return -1;
    }
    printf(SUCCES"Paquet "FILE_COLOR"%s"SUCCES" disponible sur le miroir!\n"NORMAL, pkg_selected);

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
    
    // Vérifie le hash du paquet
    if (check_SHA256(pkg_data.name))
    {
        return -1;
    }
    
    return 1;
}